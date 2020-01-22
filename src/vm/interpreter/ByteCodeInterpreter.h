//
// Created by Admin on 2020/1/21.
//

#ifndef CCVM_BYTECODEINTERPRETER_H
#define CCVM_BYTECODEINTERPRETER_H


#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"
#include "../memory/JNativeMethodStack.h"
#include "../memory/JFrame.h"
#include "../misc/Utils.h"
#include "SymbloicRef.h"
#include "../ClassFile/AccessFlag.h"
#include <typeinfo>
#include <cmath>
#include <cassert>
#include "../Runtime/JavaTypes/JType.h"

#define IS_COMPUTATIONAL_TYPE_1(value) \
    (typeid(*value) != typeid(JDouble) && typeid(*value) != typeid(JLong))
#define IS_COMPUTATIONAL_TYPE_2(value) \
    (typeid(*value) == typeid(JDouble) || typeid(*value) == typeid(JLong))
#define IS_JINT(x) (typeid(*x) == typeid(JInt))
#define IS_JLong(x) (typeid(*x) == typeid(JLong))
#define IS_JDouble(x) (typeid(*x) == typeid(JDouble))
#define IS_JFloat(x) (typeid(*x) == typeid(JFloat))
#define IS_JObject(x) (typeid(*x) == typeid(JObject))
#define IS_JArray(x) (typeid(*x) == typeid(JArray))
class JRuntimeEnv;
class JFrame;

class ByteCodeInterpreter {
    //Operations* operations;
    ByteCodeInterpreter();
    JType* returning;
    void (ByteCodeInterpreter::* operations[256])();
    u4* op;


    JType* execCode(const JavaClass* jc,u1* code,u4 codeLen,u2 exceptionsNum,Exceptions* exceptions);
    JNativeMethodStack* jNativeMethodStack;
    JRuntimeEnv* jRuntimeEnv;
    u1* code;
    const JavaClass* jc;
    u4 codeLen;
    u2 exceptionsNum;
    Exceptions* exceptions;

    template <typename ResultType, typename CallableObjectType>
    void binaryArithmetic(CallableObjectType op) {
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<ResultType>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<ResultType>();
        auto* result = new ResultType;
        result->i = op(value1->i, value2->i);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
    }

    template <typename ResultType, typename CallableObjectType>
    void unaryArithmetic(CallableObjectType op) {
        auto* ival = jNativeMethodStack->top()->popVarFromLocalVarStackTop<ResultType>();
        ival->i = op(ival->i);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(ival);
    }

    template <typename Type1, typename Type2>
    void typeCast() const {
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<Type1>();
        auto* result = new Type2;
        result->i = value->i;
        jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
    }
    void loadConstantPoolItem2Stack(const JavaClass *jc, u2 index);

public:
    void jop_nop(){
        // DO NOTHING :->
    }
    void jop_aconst_null(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(nullptr);
    }
    void jop_iconst_m1(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(-1));
    }
    void jop_iconst_0(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(0));
    }
    void jop_iconst_1(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(1));
    }
    void jop_iconst_2(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(2));
    }
    void jop_iconst_3(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(3));
    }
    void jop_iconst_4(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(4));
    }
    void jop_iconst_5(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(5));
    }
    void jop_lconst_0(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JLong(0));
    }
    void jop_lconst_1(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JLong(1));
    }
    void jop_fconst_0(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JFloat(0.0f));
    }
    void jop_fconst_1(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JFloat(1.0f));
    }
    void jop_fconst_2(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JFloat(2.0f));
    }
    void jop_dconst_0(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JDouble(0.0));
    }
    void jop_dconst_1(){
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JDouble(1.0));
    }
    void jop_bipush(){
        const u1 byte = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(byte));
    }
    void jop_sipush(){
        const u2 byte = consumeU2(code, (u4*)op);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(byte));
    }
    void jop_ldc(){
        const u1 index = consumeU1(code,(u4*)op);
        loadConstantPoolItem2Stack(jc, static_cast<u2>(index));
    }
    void jop_ldc_w(){
        const u2 index = consumeU2(code, (u4*)op);
        loadConstantPoolItem2Stack(jc, index);
    }
    void jop_ldc2_w(){
        const u2 index = consumeU2(code, (u4*)op);
        if (typeid(*jc->file.constantPoolInfo[index]) ==
            typeid(CONSTANT_Double)) {
            auto val = dynamic_cast<CONSTANT_Double*>(
                    jc->file.constantPoolInfo[index])
                    ->val;
            JDouble* dval = new JDouble;
            dval->i = val;
            jNativeMethodStack->top()->pushVarIntoExpressionStack(dval);
        }
        else if (typeid(*jc->file.constantPoolInfo[index]) ==
                 typeid(CONSTANT_Long)) {
            auto val = dynamic_cast<CONSTANT_Long*>(
                    jc->file.constantPoolInfo[index])
                    ->val;
            JLong* lval = new JLong;
            lval->i = val;
            jNativeMethodStack->top()->pushVarIntoExpressionStack(lval);
        }
        else {
            throw runtime_error(
                    "invalid symbolic reference index on "
                    "constant pool");
        }
    }
    void jop_iload(){
        const u1 index = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JInt>(index);
    }
    void jop_lload(){
        const u1 index = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JLong>(index);
    }
    void jop_fload(){
        const u1 index = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JFloat>(index);
    }
    void jop_dload(){
        const u1 index = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JDouble>(index);
    }
    void jop_aload(){
        const u1 index = consumeU1(code, (u4*)op);
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JRef>(index);
    }
    void jop_iload_0(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JInt>(0);
    }
    void jop_iload_1(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JInt>(1);
    }
    void jop_iload_2(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JInt>(2);
    }
    void jop_iload_3(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JInt>(3);
    }
    void jop_lload_0(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JLong>(0);
    }
    void jop_lload_1(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JLong>(1);
    }
    void jop_lload_2(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JLong>(2);
    }
    void jop_lload_3(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JLong>(3);
    }
    void jop_fload_0(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JFloat>(0);
    }
    void jop_fload_1(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JFloat>(1);
    }
    void jop_fload_2(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JFloat>(2);
    }
    void jop_fload_3(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JFloat>(3);
    }
    void jop_dload_0(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JDouble>(0);
    }
    void jop_dload_1(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JDouble>(1);
    }
    void jop_dload_2(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JDouble>(2);
    }
    void jop_dload_3(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JDouble>(3);
    }
    void jop_aload_0(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JRef>(0);
    }
    void jop_aload_1(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JRef>(1);
    }
    void jop_aload_2(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JRef>(2);
    }
    void jop_aload_3(){
        jNativeMethodStack->top()->loadIntoExpressionStackFromLocalVariable<JRef>(3);
    }
    void jop_iaload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JInt*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_laload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JLong*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_faload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JFloat*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_daload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JDouble*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_aaload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JRef*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_baload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JInt*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_caload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JInt*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_saload(){
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        const auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (!arrref) {
            throw runtime_error("nullpointerexception");
        }
        auto* elem = dynamic_cast<JInt*>(
                jRuntimeEnv->heap->getElement(*arrref, index->i));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(elem);
    }
    void jop_istore(){
        const u1 index = consumeU1(code, op);
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JInt>(index);
    }
    void jop_lstore(){
        const u1 index = consumeU1(code, op);
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JLong>(index);
    }
    void jop_fstore(){
        const u1 index = consumeU1(code, op);
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JFloat>(index);
    }
    void jop_dstore(){
        const u1 index = consumeU1(code, op);
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JDouble>(index);
    }
    void jop_astore(){
        const u1 index = consumeU1(code, op);
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JRef>(index);
    }
    void jop_istore_0(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JInt>(0);
    }
    void jop_istore_1(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JInt>(1);
    }
    void jop_istore_2(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JInt>(2);
    }
    void jop_istore_3(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JInt>(3);
    }
    void jop_lstore_0(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JLong>(0);
    }
    void jop_lstore_1(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JLong>(1);
    }
    void jop_lstore_2(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JLong>(2);
    }
    void jop_lstore_3(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JLong>(3);
    }
    void jop_fstore_0(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JFloat>(0);
    }
    void jop_fstore_1(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JFloat>(1);
    }
    void jop_fstore_2(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JFloat>(2);
    }
    void jop_fstore_3(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JFloat>(3);
    }
    void jop_dstore_0(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JDouble>(0);
    }
    void jop_dstore_1(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JDouble>(1);
    }
    void jop_dstore_2(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JDouble>(2);
    }
    void jop_dstore_3(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JDouble>(3);
    }
    void jop_astore_0(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JRef>(0);
    }
    void jop_astore_1(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JRef>(1);
    }
    void jop_astore_2(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JRef>(2);
    }
    void jop_astore_3(){
        jNativeMethodStack->top()->storeVarFromExpressionStackTop<JRef>(3);
    }
    void jop_iastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i> arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_lastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JLong>();
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_fastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>();
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_dastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>();
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_aastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_bastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        value->i = static_cast<int8_t>(value->i);
        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();

        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_castore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        value->i = static_cast<int16_t>(value->i);

        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_sastore(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        value->i = static_cast<int16_t>(value->i);

        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* arrref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();
        if (arrref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (index->i > arrref->len || index->i < 0) {
            throw runtime_error("array index out of bounds");
        }
        jRuntimeEnv->heap->putElement(*arrref, index->i, value);
    }
    void jop_pop(){
        jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
    }
    void jop_pop2(){
        jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
    }
    void jop_dup(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        jNativeMethodStack->top()->pushVarIntoExpressionStack(value);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value));
    }


    void jop_dup_x1(){
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
    }
    void jop_dup_x2(){
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        auto* value3 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (IS_COMPUTATIONAL_TYPE_1(value1) &&
            IS_COMPUTATIONAL_TYPE_1(value2) &&
            IS_COMPUTATIONAL_TYPE_1(value3)) {
            // use structure 1
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value3);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
        else if (IS_COMPUTATIONAL_TYPE_1(value1) &&
                 IS_COMPUTATIONAL_TYPE_2(value2)) {
            // use structure 2
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value3);

            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }

    }
    void jop_dup2(){
        JType* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (IS_COMPUTATIONAL_TYPE_1(value1) &&
            IS_COMPUTATIONAL_TYPE_1(value2)) {
            // use structure 1
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value2));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
        else if (IS_COMPUTATIONAL_TYPE_2(value1)) {
            // use structure 2
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);

            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
    }
    void jop_dup2_x1(){
        JType* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value3 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (IS_COMPUTATIONAL_TYPE_1(value1) &&
            IS_COMPUTATIONAL_TYPE_1(value2) &&
            IS_COMPUTATIONAL_TYPE_1(value3)) {
            // use structure 1
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value2));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value3);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
        else if (IS_COMPUTATIONAL_TYPE_2(value1) &&
                 IS_COMPUTATIONAL_TYPE_1(value2)) {
            // use structure 2
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value3);

            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
    }
    void jop_dup2_x2(){
        JType* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value3 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value4 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        if (IS_COMPUTATIONAL_TYPE_1(value1) &&
            IS_COMPUTATIONAL_TYPE_1(value2) &&
            IS_COMPUTATIONAL_TYPE_1(value3) &&
            IS_COMPUTATIONAL_TYPE_1(value4)) {
            // use structure 1
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value2));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value4);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value3);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
        else if (IS_COMPUTATIONAL_TYPE_2(value1) &&
                 IS_COMPUTATIONAL_TYPE_1(value2) &&
                 IS_COMPUTATIONAL_TYPE_1(value3)) {
            // use structure 2
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value4);

            jNativeMethodStack->top()->pushVarIntoExpressionStack(cloneValue(value1));
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value4);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value2);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(value1);
        }
    }
    void jop_swap(){
        JType* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JType* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (typeid(*value1) == typeid(JInt) &&
            typeid(*value2) == typeid(JInt)) {
            swap(value1, value2);
        }
        else if (typeid(*value1) == typeid(JInt) &&
                 typeid(*value2) == typeid(JFloat)) {
            const int32_t temp = dynamic_cast<JInt*>(value1)->i;
            dynamic_cast<JInt*>(value1)->i = static_cast<int32_t>(
                    dynamic_cast<JFloat*>(value2)->i);
            dynamic_cast<JFloat*>(value2)->i =
                    static_cast<float>(temp);
        }
        else if (typeid(*value1) == typeid(JFloat) &&
                 typeid(*value2) == typeid(JInt)) {
            const float temp = dynamic_cast<JFloat*>(value1)->i;
            dynamic_cast<JFloat*>(value1)->i =
                    static_cast<int32_t>(dynamic_cast<JInt*>(value2)->i);
            dynamic_cast<JInt*>(value2)->i =
                    static_cast<int32_t>(temp);
        }
        else if (typeid(*value1) == typeid(JFloat) &&
                 typeid(*value2) == typeid(JFloat)) {
            swap(value1, value2);
        }
    }
    void jop_iadd(){
        binaryArithmetic<JInt>(plus<>());
    }
    void jop_ladd(){
        binaryArithmetic<JLong>(plus<>());
    }
    void jop_fadd(){
        binaryArithmetic<JFloat>(plus<>());
    }
    void jop_dadd(){
        binaryArithmetic<JDouble>(plus<>());
    }
    void jop_isub(){
        binaryArithmetic<JInt>(minus<>());
    }
    void jop_lsub(){
        binaryArithmetic<JLong>(minus<>());
    }
    void jop_fsub(){
        binaryArithmetic<JFloat>(minus<>());
    }
    void jop_dsub(){
        binaryArithmetic<JDouble>(minus<>());
    }
    void jop_imul(){
        binaryArithmetic<JInt>(multiplies<>());
    }
    void jop_lmul(){
        binaryArithmetic<JLong>(multiplies<>());
    }
    void jop_fmul(){
        binaryArithmetic<JFloat>(multiplies<>());
    }
    void jop_dmul(){
        binaryArithmetic<JDouble>(multiplies<>());
    }
    void jop_idiv(){
        //binaryArithmetic<JInt>(divides<>());
    }
    void jop_ldiv(){
        //binaryArithmetic<JLong>(divides<>());
    }
    void jop_fdiv(){
        //binaryArithmetic<JFloat>(divides<>());
    }
    void jop_ddiv(){
        //binaryArithmetic<JDouble>(divides<>());
    }
    void jop_irem(){
        //binaryArithmetic<JInt>(modulus<>());
    }
    void jop_lrem(){
        //binaryArithmetic<JLong>(modulus<>());
    }
    void jop_frem(){
        binaryArithmetic<JFloat>(std::fmod<float, float>);
    }
    void jop_drem(){
        binaryArithmetic<JFloat>(std::fmod<double, double>);
    }
    void jop_ineg(){
        //unaryArithmetic<JInt>(negate<>());
    }
    void jop_lneg(){
        //unaryArithmetic<JLong>(negate<>());
    }
    void jop_fneg(){
        //unaryArithmetic<JFloat>(negate<>());
    }
    void jop_dneg(){
        //unaryArithmetic<JDouble>(negate<>());
    }
    void jop_ishl(){
        binaryArithmetic<JInt>([](int32_t a, int32_t b) -> int32_t {
            return a * pow(2, b & 0x1f);
        });
    }
    void jop_lshl(){
        binaryArithmetic<JLong>([](int64_t a, int64_t b) -> int64_t {
            return a * pow(2, b & 0x3f);
        });
    }
    void jop_ishr(){
        binaryArithmetic<JInt>([](int32_t a, int32_t b) -> int32_t {
            return floor(a / pow(2, b & 0x1f));
        });
    }
    void jop_lshr(){
        binaryArithmetic<JLong>([](int64_t a, int64_t b) -> int64_t {
            return floor(a / pow(2, b & 0x3f));
        });
    }
    void jop_iushr(){
        binaryArithmetic<JInt>([](int32_t a, int32_t b) -> int32_t {
            if (a > 0) {
                return a >> (b & 0x1f);
            }
            else if (a < 0) {
                return (a >> (b & 0x1f)) + (2 << ~(b & 0x1f));
            }
            else {
                throw runtime_error("0 is not handled");
            }
        });
    }
    void jop_lushr(){
        binaryArithmetic<JLong>([](int64_t a, int64_t b) -> int64_t {
            if (a > 0) {
                return a >> (b & 0x3f);
            }
            else if (a < 0) {
                return (a >> (b & 0x1f)) + (2L << ~(b & 0x3f));
            }
            else {
                throw runtime_error("0 is not handled");
            }
        });
    }
    void jop_iand(){
        //binaryArithmetic<JInt>(bit_and<>());
    }
    void jop_land(){
        //binaryArithmetic<JLong>(bit_and<>());
    }
    void jop_ior(){
        //binaryArithmetic<JInt>(bit_or<>());
    }
    void jop_lor(){
        //binaryArithmetic<JLong>(bit_or<>());
    }
    void jop_ixor(){
        //binaryArithmetic<JInt>(bit_xor<>());
    }
    void jop_lxor(){
        //binaryArithmetic<JLong>(bit_xor<>());
    }
    void jop_iinc(){
        const u1 index = code[++(*op)];
        const int8_t count = code[++(*op)];
        const int32_t extendedCount = count;
        if (IS_JINT(jNativeMethodStack->top()->getLocalVar(index))) {
            dynamic_cast<JInt*>(jNativeMethodStack->top()->getLocalVar(index))
                    ->i += extendedCount;
        }
        else if (IS_JLong(jNativeMethodStack->top()->getLocalVar(index))) {
            dynamic_cast<JLong*>(
                    jNativeMethodStack->top()->getLocalVar(index))
                    ->i += extendedCount;
        }
        else if (IS_JFloat(jNativeMethodStack->top()->getLocalVar(index))) {
            dynamic_cast<JFloat*>(
                    jNativeMethodStack->top()->getLocalVar(index))
                    ->i += extendedCount;
        }
        else if (IS_JDouble(jNativeMethodStack->top()->getLocalVar(index))) {
            dynamic_cast<JDouble*>(
                    jNativeMethodStack->top()->getLocalVar(index))
                    ->i += extendedCount;
        }
    }
    void jop_i2l(){
        typeCast<JInt, JLong>();
    }
    void jop_i2f(){
        typeCast<JInt, JFloat>();
    }
    void jop_i2d(){
        typeCast<JInt, JDouble>();
    }
    void jop_l2i(){
        typeCast<JLong, JInt>();
    }
    void jop_l2f(){
        typeCast<JLong, JFloat>();
    }
    void jop_l2d(){
        typeCast<JLong, JDouble>();
    }
    void jop_f2i(){
        typeCast<JFloat, JInt>();
    }
    void jop_f2l(){
        typeCast<JFloat, JLong>();
    }
    void jop_f2d(){
        typeCast<JFloat, JDouble>();
    }
    void jop_d2i(){
        typeCast<JDouble, JInt>();
    }
    void jop_d2l(){
        typeCast<JDouble, JLong>();
    }
    void jop_d2f(){
        typeCast<JDouble, JFloat>();
    }
    void jop_i2b(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* result = new JInt;
        result->i = (int8_t)(value->i);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
    }
    void jop_i2c(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* result = new JInt;
        result->i = (int8_t)(value->i);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
    }
    void jop_i2s(){
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* result = new JInt;
        result->i = (int16_t)(value->i);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
    }
    void jop_lcmp(){
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JLong>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JLong>();
        if (value1->i > value2->i) {
            auto* result = new JInt(1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else if (value1->i == value2->i) {
            auto* result = new JInt(0);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else {
            auto* result = new JInt(-1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
    }
    void jop_fcmpl(){
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>();
        if (value1->i > value2->i) {
            auto* result = new JInt(1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else if (abs(value1->i - value2->i) < 0.000001) {
            auto* result = new JInt(0);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else {
            auto* result = new JInt(-1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
    }
    void jop_fcmpg(){
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>();
        if (value1->i > value2->i) {
            auto* result = new JInt(1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else if (abs(value1->i - value2->i) < 0.000001) {
            auto* result = new JInt(0);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else {
            auto* result = new JInt(-1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
    }
    void jop_dcmpl(){
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>();
        if (value1->i > value2->i) {
            auto* result = new JInt(1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else if (abs(value1->i - value2->i) < 0.000000000001) {
            auto* result = new JInt(0);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else {
            auto* result = new JInt(-1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
    }
    void jop_dcmpg(){
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>();
        if (value1->i > value2->i) {
            auto* result = new JInt(1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else if (abs(value1->i - value2->i) < 0.000000000001) {
            auto* result = new JInt(0);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
        else {
            auto* result = new JInt(-1);
            jNativeMethodStack->top()->pushVarIntoExpressionStack(result);
        }
    }
    void jop_ifeq(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i == 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_ifne(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i != 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_iflt(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i < 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_ifge(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i >= 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_ifgt(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i > 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_ifle(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value->i <= 0) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmpeq(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i == value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmpne(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i != value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmplt(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i < value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmpge(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i >= value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmpgt(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i > value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_icmple(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (value1->i <= value2->i) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_acmpeq(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (value1->offset == value2->offset &&
            value1->javaClassFile == value2->javaClassFile) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_if_acmpne(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        auto* value2 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        auto* value1 = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (value1->offset != value2->offset ||
            value1->javaClassFile != value2->javaClassFile) {
            *op = currentOffset + branchindex;
        }
    }
    void jop_goto(){
        u4 currentOffset = *op - 1;
        int16_t branchindex = consumeU2(code, (u4*)op);
        *op = currentOffset + branchindex;
    }
    void jop_jsr(){
        throw runtime_error("unsupported opcode [jsr]");
    }
    void jop_ret(){
        throw runtime_error("unsupported opcode [ret]");
    }
    void jop_tableswitch(){
        u4 currentOffset = *op - 1;
        (*op)++;
        (*op)++;
        (*op)++;  // 3 bytes padding
        int32_t defaultIndex = consumeU4(code, (u4*)op);
        int32_t low = consumeU4(code, (u4*)op);
        int32_t high = consumeU4(code, (u4*)op);
        vector<int32_t> jumpOffset;
        FOR_EACH(i, high - low + 1) {
            jumpOffset.push_back(consumeU4(code, (u4*)op));
        }

        auto* index = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        if (index->i < low || index->i > high) {
            *op = currentOffset + defaultIndex;
        }
        else {
            *op = currentOffset + jumpOffset[index->i - low];
        }
    }
    void jop_lookupswitch(){
        u4 currentOffset = *op - 1;
        (*op)++;
        (*op)++;
        (*op)++;  // 3 bytes padding
        int32_t defaultIndex = consumeU4(code, (u4*)op);
        int32_t npair = consumeU4(code, (u4*)op);
        map<int32_t, int32_t> matchOffset;
        FOR_EACH(i, npair) {
            matchOffset.insert(
                    make_pair(consumeU4(code, (u4*)op), consumeU4(code, (u4*)op)));
        }
        auto* key = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();
        auto res = matchOffset.find(key->i);
        if (res != matchOffset.end()) {
            *op = currentOffset + (*res).second;
        }
        else {
            *op = currentOffset + defaultIndex;
        }
    }
    void jop_ireturn(){
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>());
    }
    void jop_lreturn(){
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JLong>());
    }
    void jop_freturn(){
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JFloat>());
    }
    void jop_dreturn(){
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JDouble>());
    }
    void jop_areturn(){
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>());
    }
    void jop_return(){
        *op = -1;
        this->returning=cloneValue(jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>());
    }
    void jop_getstatic(){
        const u2 index = consumeU2(code, (u4*)op);
        auto symbolicRef = parseFieldSymbolicReference(jc, index);
        jRuntimeEnv->methodArea->linkClassIfAbsent(symbolicRef.jc->getClassName());
        jRuntimeEnv->methodArea->initClassIfAbsent(*this,
                                                   symbolicRef.jc->getClassName());
        JType* field = symbolicRef.jc->getStaticVar(
                symbolicRef.name, symbolicRef.descriptor);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(field);
    }
    void jop_putstatic(){
        u2 index = consumeU2(code, (u4*)op);
        JType* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        auto symbolicRef = parseFieldSymbolicReference(jc, index);

        jRuntimeEnv->methodArea->linkClassIfAbsent(symbolicRef.jc->getClassName());
        jRuntimeEnv->methodArea->initClassIfAbsent(*this,
                                                   symbolicRef.jc->getClassName());
        symbolicRef.jc->setStaticVar(symbolicRef.name,
                                     symbolicRef.descriptor, value);
    }
    void jop_getfield(){
        u2 index = consumeU2(code, (u4*)op);
        JObject* objectref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        auto symbolicRef = parseFieldSymbolicReference(jc, index);
        JType* field = cloneValue(jRuntimeEnv->heap->getFieldByName(
                symbolicRef.jc, symbolicRef.name, symbolicRef.descriptor,
                objectref));
        jNativeMethodStack->top()->pushVarIntoExpressionStack(field);
    }
    void jop_putfield(){
        const u2 index = consumeU2(code, (u4*)op);
        JType* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
        JObject* objectref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        auto symbolicRef = parseFieldSymbolicReference(jc, index);
        jRuntimeEnv->heap->putFieldByName(symbolicRef.jc, symbolicRef.name,
                                          symbolicRef.descriptor, objectref,
                                          value);
    }

    void invokeVirtual(string basicString, string basicString1);

    void jop_invokevirtual(){
        const u2 index = consumeU2(code, (u4*)op);
        assert(typeid(*jc->file.constantPoolInfo[index]) ==
               typeid(CONSTANT_Methodref));

        auto symbolicRef = parseMethodSymbolicReference(jc, index);

        if (symbolicRef.name == "<init>") {
            runtime_error(
                    "invoking method should not be instance "
                    "initialization method\n");
        }
        if (!IS_SIGNATURE_POLYMORPHIC_METHOD(
                symbolicRef.jc->getClassName(), symbolicRef.name)) {
            invokeVirtual(symbolicRef.name, symbolicRef.descriptor);
        }
        else {
            // TODO:TO BE IMPLEMENTED
        }
    }

    void invokeSpecial(JavaClass *pClass, string basicString, string basicString1);

    void jop_invokespecial(){
        const u2 index = consumeU2(code, (u4*)op);
        SymbolicRef symbolicRef;

        if (typeid(*jc->file.constantPoolInfo[index]) ==
            typeid(CONSTANT_InterfaceMethodref)) {
            symbolicRef =
                    parseInterfaceMethodSymbolicReference(jc, index);
        }
        else if (typeid(*jc->file.constantPoolInfo[index]) ==
                 typeid(CONSTANT_Methodref)) {
            symbolicRef = parseMethodSymbolicReference(jc, index);
        }

        // If all of the following are true, let C be the direct
        // superclass of the current class :
        JavaClass* symbolicRefClass = symbolicRef.jc;
        if ("<init>" != symbolicRef.name) {
            if (!IS_CLASS_INTERFACE(
                    symbolicRefClass->file.accessFlags)) {
                if (symbolicRefClass->getClassName() ==
                    jc->getSuperClassName()) {
                    if (IS_CLASS_SUPER(jc->file.accessFlags)) {
                        invokeSpecial(jRuntimeEnv->methodArea->findJavaClass(
                                jc->getSuperClassName()),
                                      symbolicRef.name,
                                      symbolicRef.descriptor);
                        *op=-1;
                    }
                }
            }
        }
        // Otherwise let C be the symbolic reference class
        invokeSpecial(symbolicRef.jc, symbolicRef.name,
                      symbolicRef.descriptor);
    }

    void invokeStatic(JavaClass *pClass, string basicString, string basicString1);

    void jop_invokestatic(){
        // Invoke a class (static) method
        const u2 index = consumeU2(code, (u4*)op);

        if (typeid(*jc->file.constantPoolInfo[index]) ==
            typeid(CONSTANT_InterfaceMethodref)) {
            auto symbolicRef =
                    parseInterfaceMethodSymbolicReference(jc, index);
            invokeStatic(symbolicRef.jc, symbolicRef.name,
                         symbolicRef.descriptor);
        }
        else if (typeid(*jc->file.constantPoolInfo[index]) ==
                 typeid(CONSTANT_Methodref)) {
            auto symbolicRef = parseMethodSymbolicReference(jc, index);
            invokeStatic(symbolicRef.jc, symbolicRef.name,
                         symbolicRef.descriptor);
        }
    }

    void invokeInterface(JavaClass *pClass, string basicString, string basicString1);

    void jop_invokeinterface(){
        const u2 index = consumeU2(code, op);
        ++op;  // read count and discard
        ++op;  // opcode padding 0;

        if (typeid(*jc->file.constantPoolInfo[index]) ==
            typeid(CONSTANT_InterfaceMethodref)) {
            auto symbolicRef =
                    parseInterfaceMethodSymbolicReference(jc, index);
            invokeInterface(symbolicRef.jc, symbolicRef.name,
                            symbolicRef.descriptor);
        }
    }
    void jop_invokedynamic(){
        throw runtime_error("unsupported opcode [invokedynamic]");
    }
    void jop_new(){
        const u2 index = consumeU2(code, (u4*)op);
        JObject* objectref = execNew(jc, index);
        jNativeMethodStack->top()->pushVarIntoExpressionStack(objectref);
    }
    void jop_newarray(){
        const u1 atype = code[++*op];
        JInt* count = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();

        if (count->i < 0) {
            throw runtime_error("negative array size");
        }
        JArray* arrayref = jRuntimeEnv->heap->JavaNewCreatPODArray(atype, count->i);

        jNativeMethodStack->top()->pushVarIntoExpressionStack(arrayref);
    }
    void jop_anewarray(){
        const u2 index = consumeU2(code, (u4*)op);
        auto symbolicRef = parseClassSymbolicReference(jc, index);
        JInt* count = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JInt>();

        if (count->i < 0) {
            throw runtime_error("negative array size");
        }
        JArray* arrayref =
                jRuntimeEnv->heap->JavaNewCreatObjArray(*symbolicRef.jc, count->i);

        jNativeMethodStack->top()->pushVarIntoExpressionStack(arrayref);
    }
    void jop_arraylength(){
        JArray* arrayref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JArray>();

        if (arrayref == nullptr) {
            throw runtime_error("null pointer\n");
        }
        JInt* length = new JInt;
        length->i = arrayref->len;
        jNativeMethodStack->top()->pushVarIntoExpressionStack(length);
    }
    bool hasInheritanceRelationship_1(const JavaClass* source,
                                    JavaClass* super) {
        if (source->getClassName() == super->getClassName()) {
            return true;
        }
        if (source->hasSuperClass()) {
            return hasInheritanceRelationship_1(
                    jRuntimeEnv->methodArea->loadClassIfAbsent(source->getSuperClassName()), super);
        }
        return false;
    }
    void jop_athrow(){
        auto* throwobj = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (throwobj == nullptr) {
            throw runtime_error("null pointer");
        }
        if (!hasInheritanceRelationship_1(
                throwobj->javaClassFile,
                jRuntimeEnv->methodArea->loadClassIfAbsent("java/lang/Throwable"))) {
            throw runtime_error("it's not a throwable object");
        }

        if (handleException(jc, exceptionsNum, exceptions, throwobj, *op)) {
            while (!jNativeMethodStack->top()->status()) {
                jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();
            }
            jNativeMethodStack->top()->pushVarIntoExpressionStack(throwobj);
        }
        else /* Exception can not handled within method handlers */ {
            //exception.markException();
            //exception.setThrowExceptionInfo(throwobj);
            this->returning=throwobj;
            *op=-1;
        }
    }
    void jop_checkcast(){
        throw runtime_error("unsupported opcode [checkcast]");
    }
    //unsupported part multipart thread

    void jop_instanceof(){
        const u2 index = consumeU2(code, (u4*)op);
        auto* objectref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (objectref == nullptr) {
            jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(0));
        }
        if (checkInstanceof(jc, index, objectref)) {
            jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(1));
        }
        else {
            jNativeMethodStack->top()->pushVarIntoExpressionStack(new JInt(0));
        }
    }
    /*
    void jop_monitorenter(){
        JType* ref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (ref == nullptr) {
            throw runtime_error("null pointer");
        }

        if (!jRuntimeEnv->heap->hasMonitor(ref)) {
            dynamic_cast<JObject*>(ref)->offset =
                    jRuntimeEnv->heap->createMonitor();
        }
        jRuntimeEnv->heap->findMonitor(ref)->enter(this_thread::get_id());
    }
    void jop_monitorexit(){
        JType* ref = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JType>();

        if (ref == nullptr) {
            throw runtime_error("null pointer");
        }
        if (!jRuntimeEnv->heap->hasMonitor(ref)) {
            dynamic_cast<JObject*>(ref)->offset =
                    jRuntimeEnv->heap->createMonitor();
        }
        jRuntimeEnv->heap->findMonitor(ref)->exit();
    }
     */
    void jop_wide(){
        throw runtime_error("unsupported opcode [wide]");
    }
    void jop_multianewarray(){
        throw runtime_error("unsupported opcode [multianewarray]");
    }
    void jop_ifnull(){
        u4 currentOffset = *op - 1;
        int16_t branchIndex = consumeU2(code, (u4*)op);
        JObject* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (value == nullptr) {
            *op = currentOffset + branchIndex;
        }
    }
    void jop_ifnonnull(){
        u4 currentOffset = *op - 1;
        int16_t branchIndex = consumeU2(code, (u4*)op);
        JObject* value = jNativeMethodStack->top()->popVarFromLocalVarStackTop<JObject>();
        if (value != nullptr) {
            *op = currentOffset + branchIndex;
        }
    }
    void jop_goto_w(){
        u4 currentOffset = *op - 1;
        int32_t branchIndex = consumeU4(code, (u4*)op);
        *op = currentOffset + branchIndex;
    }
    void jop_jsr_w(){
        throw runtime_error("unsupported opcode [jsr_w]");
    }
    void jop_breakpoint(){
        // Reserved opcodde
        exit(EXIT_FAILURE);
    }
    void jop_impdep1(){
        // Reserved opcodde
        exit(EXIT_FAILURE);
    }
    void jop_impdep2(){
        exit(EXIT_FAILURE);
    }

    bool handleException(const JavaClass *jc, u2 exceptLen, Exceptions *exceptTab, const JObject *objectref, u4 &op);

    JObject *execNew(const JavaClass *jc, u2 index);

    bool checkInstanceof(const JavaClass *jc, u2 index, JType *objectref);
};


#endif //CCVM_BYTECODEINTERPRETER_H
