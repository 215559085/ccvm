//
// Created by Admin on 2020/1/21.
//

#include "ByteCodeInterpreter.h"


JType* ByteCodeInterpreter::execCode(const JavaClass *jc, u1 *code, u4 codeLen, u2 exceptionsNum, Exceptions *exceptions) {
    uint32_t codeIndex=0;
    this->op=&codeIndex;
    try{
    for(codeIndex=0;codeIndex<codeLen;codeIndex++) {
        (this->*operations[code[codeIndex]])();
        if(*op<0){ break;}
    }
    }catch(exception){

    }
    return nullptr;
}
bool hasInheritanceRelationship(JavaClass* source,
                                JavaClass* super,
                                JRuntimeEnv* jRuntimeEnv) {
    if (source->getClassName() == super->getClassName()) {
        return true;
    }
    if (source->hasSuperClass()) {
        return hasInheritanceRelationship(
                jRuntimeEnv->methodArea->loadClassIfAbsent(source->getSuperClassName()), super,jRuntimeEnv);
    }
    return false;
}
bool ByteCodeInterpreter::handleException(const JavaClass *jc, u2 exceptLen,
                                  Exceptions *exceptTab,
                                  const JObject *objectref, u4 &op) {
    FOR_EACH(i, exceptLen) {
        const string &catchTypeName =
                jc->getString(dynamic_cast<CONSTANT_Class *>(
                                      jc->file.constantPoolInfo[exceptTab[i].catchType])
                                      ->nameIndex);
        if (hasInheritanceRelationship(
                jRuntimeEnv->methodArea->findJavaClass(objectref->javaClassFile->getClassName()),
                jRuntimeEnv->methodArea->findJavaClass(catchTypeName),
                jRuntimeEnv) &&
            exceptTab[i].startPC <= op && op < exceptTab[i].endPC) {
            // start<=op<end
            // If we found a proper exception handler, set current pc as
            // handlerPC of this exception table item;
            op = exceptTab[i].handlerPC - 1;
            return true;
        }
        if (exceptTab[i].catchType == 0) {
            op = exceptTab[i].handlerPC - 1;
            return true;
        }
    }
    return false;
}
JObject *ByteCodeInterpreter::execNew(const JavaClass *jc, u2 index) {
    jRuntimeEnv->methodArea->linkClassIfAbsent(const_cast<JavaClass *>(jc)->getClassName());
    jRuntimeEnv->methodArea->initClassIfAbsent(*this,
                              const_cast<JavaClass *>(jc)->getClassName());

    if (typeid(*jc->file.constantPoolInfo[index]) != typeid(CONSTANT_Class)) {
        throw runtime_error(
                "operand index of new is not a class or "
                "interface\n");
    }
    string className = jc->getString(
            dynamic_cast<CONSTANT_Class *>(jc->file.constantPoolInfo[index])
                    ->nameIndex);
    JavaClass *newClass = jRuntimeEnv->methodArea->loadClassIfAbsent(className);
    return jRuntimeEnv->heap->JavaNewCreatObj(newClass);
}

bool ByteCodeInterpreter::checkInstanceof(const JavaClass *jc, u2 index,
                                  JType *objectref) {
    string TclassName =
            (char *)dynamic_cast<CONSTANT_Utf8_info *>(
                    jc->file.constantPoolInfo[dynamic_cast<CONSTANT_Class *>(
                            jc->file.constantPoolInfo[index])
                            ->nameIndex])
                    ->bytes;
    constexpr short TYPE_ARRAY = 1;
    constexpr short TYPE_CLASS = 2;
    constexpr short TYPE_INTERFACE = 3;

    short tType = 0;
    if (TclassName.find('[') != string::npos) {
        tType = TYPE_ARRAY;
    } else {
        if (IS_CLASS_INTERFACE(
                jRuntimeEnv->methodArea->findJavaClass(TclassName)->file.accessFlags)) {
            tType = TYPE_INTERFACE;
        } else {
            tType = TYPE_CLASS;
        }
    }

    if (typeid(objectref) == typeid(JObject)) {
        if (!IS_CLASS_INTERFACE(
                dynamic_cast<JObject *>(objectref)->javaClassFile->file.accessFlags)) {
            // If it's an ordinary class
            if (tType == TYPE_CLASS) {
                if (jRuntimeEnv->methodArea->findJavaClass(dynamic_cast<JObject *>(objectref)
                                                  ->javaClassFile->getClassName())
                            ->getClassName() == TclassName ||
                    jRuntimeEnv->methodArea->findJavaClass(dynamic_cast<JObject *>(objectref)
                                                  ->javaClassFile->getSuperClassName())
                            ->getClassName() == TclassName) {
                    return true;
                }
            } else if (tType == TYPE_INTERFACE) {
                auto &&interfaceIdxs = dynamic_cast<JObject *>(objectref)
                        ->javaClassFile->getInterfacesIndex();
                FOR_EACH(i, interfaceIdxs.size()) {
                    string interfaceName =
                            dynamic_cast<JObject *>(objectref)->javaClassFile->getString(
                                    dynamic_cast<CONSTANT_Class *>(
                                            dynamic_cast<JObject *>(objectref)
                                                    ->javaClassFile->file.constantPoolInfo[interfaceIdxs[i]])
                                            ->nameIndex);
                    if (interfaceName == TclassName) {
                        return true;
                    }
                }
            } else {

            }
        } else {
            // Otherwise, it's an interface class
            if (tType == TYPE_CLASS) {
                if (TclassName == "java/lang/Object") {
                    return true;
                }
            } else if (tType == TYPE_INTERFACE) {
                if (TclassName == dynamic_cast<JObject *>(objectref)
                        ->javaClassFile->getClassName() ||
                    TclassName == dynamic_cast<JObject *>(objectref)
                            ->javaClassFile->getSuperClassName()) {
                    return true;
                }
            } else {

            }
        }
    } else if (typeid(objectref) == typeid(JArray)) {
        if (tType == TYPE_CLASS) {
            if (TclassName == "java/lang/Object") {
                return true;
            }
        } else if (tType == TYPE_INTERFACE) {
            auto *firstComponent = dynamic_cast<JObject *>(
                    jRuntimeEnv->heap->getElement(*dynamic_cast<JArray *>(objectref), 0));
            auto &&interfaceIdxs = firstComponent->javaClassFile->getInterfacesIndex();
            FOR_EACH(i, interfaceIdxs.size()) {
                if (firstComponent->javaClassFile->getString(
                        dynamic_cast<CONSTANT_Class *>(
                                firstComponent->javaClassFile->file
                                        .constantPoolInfo[interfaceIdxs[i]])
                                ->nameIndex) == TclassName) {
                    return true;
                }
            }
        } else if (tType == TYPE_ARRAY) {
            throw runtime_error("to be continue\n");
        } else {

        }
    } else {

    }
}

ByteCodeInterpreter::ByteCodeInterpreter() {
    operations[0]=&ByteCodeInterpreter::jop_nop;
    operations[1] = &ByteCodeInterpreter::jop_aconst_null;
    operations[2] = &ByteCodeInterpreter::jop_iconst_m1;
    operations[3] = &ByteCodeInterpreter::jop_iconst_0;
    operations[4] = &ByteCodeInterpreter::jop_iconst_1;
    operations[5] = &ByteCodeInterpreter::jop_iconst_2;
    operations[6] = &ByteCodeInterpreter::jop_iconst_3;
    operations[7] = &ByteCodeInterpreter::jop_iconst_4;
    operations[8] = &ByteCodeInterpreter::jop_iconst_5;
    operations[9] = &ByteCodeInterpreter::jop_lconst_0;
    operations[10] = &ByteCodeInterpreter::jop_lconst_1;
    operations[11] = &ByteCodeInterpreter::jop_fconst_0;
    operations[12] = &ByteCodeInterpreter::jop_fconst_1;
    operations[13] = &ByteCodeInterpreter::jop_fconst_2;
    operations[14] = &ByteCodeInterpreter::jop_dconst_0;
    operations[15] = &ByteCodeInterpreter::jop_dconst_1;
    operations[16] = &ByteCodeInterpreter::jop_bipush;
    operations[17] = &ByteCodeInterpreter::jop_sipush;
    operations[18] = &ByteCodeInterpreter::jop_ldc;
    operations[19] = &ByteCodeInterpreter::jop_ldc_w;
    operations[20] = &ByteCodeInterpreter::jop_ldc2_w;
    operations[21] = &ByteCodeInterpreter::jop_iload;
    operations[22] = &ByteCodeInterpreter::jop_lload;
    operations[23] = &ByteCodeInterpreter::jop_fload;
    operations[24] = &ByteCodeInterpreter::jop_dload;
    operations[25] = &ByteCodeInterpreter::jop_aload;
    operations[26] = &ByteCodeInterpreter::jop_iload_0;
    operations[27] = &ByteCodeInterpreter::jop_iload_1;
    operations[28] = &ByteCodeInterpreter::jop_iload_2;
    operations[29] = &ByteCodeInterpreter::jop_iload_3;
    operations[30] = &ByteCodeInterpreter::jop_lload_0;
    operations[31] = &ByteCodeInterpreter::jop_lload_1;
    operations[32] = &ByteCodeInterpreter::jop_lload_2;
    operations[33] = &ByteCodeInterpreter::jop_lload_3;
    operations[34] = &ByteCodeInterpreter::jop_fload_0;
    operations[35] = &ByteCodeInterpreter::jop_fload_1;
    operations[36] = &ByteCodeInterpreter::jop_fload_2;
    operations[37] = &ByteCodeInterpreter::jop_fload_3;
    operations[38] = &ByteCodeInterpreter::jop_dload_0;
    operations[39] = &ByteCodeInterpreter::jop_dload_1;
    operations[40] = &ByteCodeInterpreter::jop_dload_2;
    operations[41] = &ByteCodeInterpreter::jop_dload_3;
    operations[42] = &ByteCodeInterpreter::jop_aload_0;
    operations[43] = &ByteCodeInterpreter::jop_aload_1;
    operations[44] = &ByteCodeInterpreter::jop_aload_2;
    operations[45] = &ByteCodeInterpreter::jop_aload_3;
    operations[46] = &ByteCodeInterpreter::jop_iaload;
    operations[47] = &ByteCodeInterpreter::jop_laload;
    operations[48] = &ByteCodeInterpreter::jop_faload;
    operations[49] = &ByteCodeInterpreter::jop_daload;
    operations[50] = &ByteCodeInterpreter::jop_aaload;
    operations[51] = &ByteCodeInterpreter::jop_baload;
    operations[52] = &ByteCodeInterpreter::jop_caload;
    operations[53] = &ByteCodeInterpreter::jop_saload;
    operations[54] = &ByteCodeInterpreter::jop_istore;
    operations[55] = &ByteCodeInterpreter::jop_lstore;
    operations[56] = &ByteCodeInterpreter::jop_fstore;
    operations[57] = &ByteCodeInterpreter::jop_dstore;
    operations[58] = &ByteCodeInterpreter::jop_astore;
    operations[59] = &ByteCodeInterpreter::jop_istore_0;
    operations[60] = &ByteCodeInterpreter::jop_istore_1;
    operations[61] = &ByteCodeInterpreter::jop_istore_2;
    operations[62] = &ByteCodeInterpreter::jop_istore_3;
    operations[63] = &ByteCodeInterpreter::jop_lstore_0;
    operations[64] = &ByteCodeInterpreter::jop_lstore_1;
    operations[65] = &ByteCodeInterpreter::jop_lstore_2;
    operations[66] = &ByteCodeInterpreter::jop_lstore_3;
    operations[67] = &ByteCodeInterpreter::jop_fstore_0;
    operations[68] = &ByteCodeInterpreter::jop_fstore_1;
    operations[69] = &ByteCodeInterpreter::jop_fstore_2;
    operations[70] = &ByteCodeInterpreter::jop_fstore_3;
    operations[71] = &ByteCodeInterpreter::jop_dstore_0;
    operations[72] = &ByteCodeInterpreter::jop_dstore_1;
    operations[73] = &ByteCodeInterpreter::jop_dstore_2;
    operations[74] = &ByteCodeInterpreter::jop_dstore_3;
    operations[75] = &ByteCodeInterpreter::jop_astore_0;
    operations[76] = &ByteCodeInterpreter::jop_astore_1;
    operations[77] = &ByteCodeInterpreter::jop_astore_2;
    operations[78] = &ByteCodeInterpreter::jop_astore_3;
    operations[79] = &ByteCodeInterpreter::jop_iastore;
    operations[80] = &ByteCodeInterpreter::jop_lastore;
    operations[81] = &ByteCodeInterpreter::jop_fastore;
    operations[82] = &ByteCodeInterpreter::jop_dastore;
    operations[83] = &ByteCodeInterpreter::jop_aastore;
    operations[84] = &ByteCodeInterpreter::jop_bastore;
    operations[85] = &ByteCodeInterpreter::jop_castore;
    operations[86] = &ByteCodeInterpreter::jop_sastore;
    operations[87] = &ByteCodeInterpreter::jop_pop;
    operations[88] = &ByteCodeInterpreter::jop_pop2;
    operations[89] = &ByteCodeInterpreter::jop_dup;
    operations[90] = &ByteCodeInterpreter::jop_dup_x1;
    operations[91] = &ByteCodeInterpreter::jop_dup_x2;
    operations[92] = &ByteCodeInterpreter::jop_dup2;
    operations[93] = &ByteCodeInterpreter::jop_dup2_x1;
    operations[94] = &ByteCodeInterpreter::jop_dup2_x2;
    operations[95] = &ByteCodeInterpreter::jop_swap;
    operations[96] = &ByteCodeInterpreter::jop_iadd;
    operations[97] = &ByteCodeInterpreter::jop_ladd;
    operations[98] = &ByteCodeInterpreter::jop_fadd;
    operations[99] = &ByteCodeInterpreter::jop_dadd;
    operations[100] = &ByteCodeInterpreter::jop_isub;
    operations[101] = &ByteCodeInterpreter::jop_lsub;
    operations[102] = &ByteCodeInterpreter::jop_fsub;
    operations[103] = &ByteCodeInterpreter::jop_dsub;
    operations[104] = &ByteCodeInterpreter::jop_imul;
    operations[105] = &ByteCodeInterpreter::jop_lmul;
    operations[106] = &ByteCodeInterpreter::jop_fmul;
    operations[107] = &ByteCodeInterpreter::jop_dmul;
    operations[108] = &ByteCodeInterpreter::jop_idiv;
    operations[109] = &ByteCodeInterpreter::jop_ldiv;
    operations[110] = &ByteCodeInterpreter::jop_fdiv;
    operations[111] = &ByteCodeInterpreter::jop_ddiv;
    operations[112] = &ByteCodeInterpreter::jop_irem;
    operations[113] = &ByteCodeInterpreter::jop_lrem;
    operations[114] = &ByteCodeInterpreter::jop_frem;
    operations[115] = &ByteCodeInterpreter::jop_drem;
    operations[116] = &ByteCodeInterpreter::jop_ineg;
    operations[117] = &ByteCodeInterpreter::jop_lneg;
    operations[118] = &ByteCodeInterpreter::jop_fneg;
    operations[119] = &ByteCodeInterpreter::jop_dneg;
    operations[120] = &ByteCodeInterpreter::jop_ishl;
    operations[121] = &ByteCodeInterpreter::jop_lshl;
    operations[122] = &ByteCodeInterpreter::jop_ishr;
    operations[123] = &ByteCodeInterpreter::jop_lshr;
    operations[124] = &ByteCodeInterpreter::jop_iushr;
    operations[125] = &ByteCodeInterpreter::jop_lushr;
    operations[126] = &ByteCodeInterpreter::jop_iand;
    operations[127] = &ByteCodeInterpreter::jop_land;
    operations[128] = &ByteCodeInterpreter::jop_ior;
    operations[129] = &ByteCodeInterpreter::jop_lor;
    operations[130] = &ByteCodeInterpreter::jop_ixor;
    operations[131] = &ByteCodeInterpreter::jop_lxor;
    operations[132] = &ByteCodeInterpreter::jop_iinc;
    operations[133] = &ByteCodeInterpreter::jop_i2l;
    operations[134] = &ByteCodeInterpreter::jop_i2f;
    operations[135] = &ByteCodeInterpreter::jop_i2d;
    operations[136] = &ByteCodeInterpreter::jop_l2i;
    operations[137] = &ByteCodeInterpreter::jop_l2f;
    operations[138] = &ByteCodeInterpreter::jop_l2d;
    operations[139] = &ByteCodeInterpreter::jop_f2i;
    operations[140] = &ByteCodeInterpreter::jop_f2l;
    operations[141] = &ByteCodeInterpreter::jop_f2d;
    operations[142] = &ByteCodeInterpreter::jop_d2i;
    operations[143] = &ByteCodeInterpreter::jop_d2l;
    operations[144] = &ByteCodeInterpreter::jop_d2f;
    operations[145] = &ByteCodeInterpreter::jop_i2b;
    operations[146] = &ByteCodeInterpreter::jop_i2c;
    operations[147] = &ByteCodeInterpreter::jop_i2s;
    operations[148] = &ByteCodeInterpreter::jop_lcmp;
    operations[149] = &ByteCodeInterpreter::jop_fcmpl;
    operations[150] = &ByteCodeInterpreter::jop_fcmpg;
    operations[151] = &ByteCodeInterpreter::jop_dcmpl;
    operations[152] = &ByteCodeInterpreter::jop_dcmpg;
    operations[153] = &ByteCodeInterpreter::jop_ifeq;
    operations[154] = &ByteCodeInterpreter::jop_ifne;
    operations[155] = &ByteCodeInterpreter::jop_iflt;
    operations[156] = &ByteCodeInterpreter::jop_ifge;
    operations[157] = &ByteCodeInterpreter::jop_ifgt;
    operations[158] = &ByteCodeInterpreter::jop_ifle;
    operations[159] = &ByteCodeInterpreter::jop_if_icmpeq;
    operations[160] = &ByteCodeInterpreter::jop_if_icmpne;
    operations[161] = &ByteCodeInterpreter::jop_if_icmplt;
    operations[162] = &ByteCodeInterpreter::jop_if_icmpge;
    operations[163] = &ByteCodeInterpreter::jop_if_icmpgt;
    operations[164] = &ByteCodeInterpreter::jop_if_icmple;
    operations[165] = &ByteCodeInterpreter::jop_if_acmpeq;
    operations[166] = &ByteCodeInterpreter::jop_if_acmpne;
    operations[167] = &ByteCodeInterpreter::jop_goto;
    operations[168] = &ByteCodeInterpreter::jop_jsr;
    operations[169] = &ByteCodeInterpreter::jop_ret;
    operations[170] = &ByteCodeInterpreter::jop_tableswitch;
    operations[171] = &ByteCodeInterpreter::jop_lookupswitch;
    operations[172] = &ByteCodeInterpreter::jop_ireturn;
    operations[173] = &ByteCodeInterpreter::jop_lreturn;
    operations[174] = &ByteCodeInterpreter::jop_freturn;
    operations[175] = &ByteCodeInterpreter::jop_dreturn;
    operations[176] = &ByteCodeInterpreter::jop_areturn;
    operations[177] = &ByteCodeInterpreter::jop_return;
    operations[178] = &ByteCodeInterpreter::jop_getstatic;
    operations[179] = &ByteCodeInterpreter::jop_putstatic;
    operations[180] = &ByteCodeInterpreter::jop_getfield;
    operations[181] = &ByteCodeInterpreter::jop_putfield;
    operations[182] = &ByteCodeInterpreter::jop_invokevirtual;
    operations[183] = &ByteCodeInterpreter::jop_invokespecial;
    operations[184] = &ByteCodeInterpreter::jop_invokestatic;
    operations[185] = &ByteCodeInterpreter::jop_invokeinterface;
    operations[186] = &ByteCodeInterpreter::jop_invokedynamic;
    operations[187] = &ByteCodeInterpreter::jop_new;
    operations[188] = &ByteCodeInterpreter::jop_newarray;
    operations[189] = &ByteCodeInterpreter::jop_anewarray;
    operations[190] = &ByteCodeInterpreter::jop_arraylength;
    operations[191] = &ByteCodeInterpreter::jop_athrow;
    operations[192] = &ByteCodeInterpreter::jop_checkcast;
    operations[193] = &ByteCodeInterpreter::jop_instanceof;
    operations[194] = nullptr;//&ByteCodeInterpreter::jop_monitorenter;
    operations[195] = nullptr;//&ByteCodeInterpreter::jop_monitorexit;
    operations[196] = &ByteCodeInterpreter::jop_wide;
    operations[197] = &ByteCodeInterpreter::jop_multianewarray;
    operations[198] = &ByteCodeInterpreter::jop_ifnull;
    operations[199] = &ByteCodeInterpreter::jop_ifnonnull;
    operations[200] = &ByteCodeInterpreter::jop_goto_w;
    operations[201] = &ByteCodeInterpreter::jop_jsr_w;
    operations[202] = &ByteCodeInterpreter::jop_breakpoint;
    operations[254] = &ByteCodeInterpreter::jop_impdep1;
    operations[255] = &ByteCodeInterpreter::jop_impdep2;
}

void ByteCodeInterpreter::loadConstantPoolItem2Stack(const JavaClass *jc, u2 index) {
    if (typeid(*jc->file.constantPoolInfo[index]) == typeid(CONSTANT_Integer)) {
        auto val =
                dynamic_cast<CONSTANT_Integer *>(jc->file.constantPoolInfo[index])->val;
        JInt *ival = new JInt;
        ival->i = val;
        jNativeMethodStack->top()->pushVarIntoExpressionStack(ival);
    } else if (typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_Float)) {
        auto val = dynamic_cast<CONSTANT_Float *>(jc->file.constantPoolInfo[index])->val;
        JFloat *fval = new JFloat;
        fval->i = val;
        jNativeMethodStack->top()->pushVarIntoExpressionStack(fval);
    } else if (typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_String)) {
        auto val = jc->getString(
                dynamic_cast<CONSTANT_String *>(jc->file.constantPoolInfo[index])
                        ->stringIndex);
        JObject *str = jRuntimeEnv->heap->JavaNewCreatObj(
                jRuntimeEnv->methodArea->loadClassIfAbsent("java/lang/String"));
        JArray *value = jRuntimeEnv->heap->JavaNewCreatCharArray(val, val.length());
        // Put string  into str's field; according the source file of
        // java.lang.Object, we know that its first field was used to store
        // chars
        jRuntimeEnv->heap->putFieldByOffset(*str, 0, value);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(str);
    } else if (typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_Class)) {
        throw runtime_error("nonsupport region");
    } else if (typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_MethodType)) {
        throw runtime_error("nonsupport region");
    } else if (typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_MethodHandle)) {
        throw runtime_error("nonsupport region");
    } else {
        throw runtime_error(
                "invalid symbolic reference index on constant "
                "pool");
    }
}

void ByteCodeInterpreter::invokeVirtual(string basicString, string basicString1) {

}

void ByteCodeInterpreter::invokeStatic(JavaClass *pClass, string basicString, string basicString1) {

}

void ByteCodeInterpreter::invokeSpecial(JavaClass *pClass, string basicString, string basicString1) {

}

void ByteCodeInterpreter::invokeInterface(JavaClass *pClass, string basicString, string basicString1) {

}
void ByteCodeInterpreter::invokeByName(JavaClass *jc, const string &name,
                               const string &descriptor){

}