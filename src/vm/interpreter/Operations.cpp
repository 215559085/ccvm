//
// Created by Admin on 2020/1/21.
//

#include "Operations.h"
#include "../memory/JFrame.h"

void jop_nop(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aconst_null(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_m1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_4(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iconst_5(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lconst_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lconst_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fconst_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fconst_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fconst_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dconst_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dconst_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_bipush(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_sipush(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ldc(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ldc_w(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ldc2_w(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iload_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iload_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iload_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iload_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lload_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lload_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lload_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lload_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fload_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fload_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fload_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fload_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dload_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dload_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dload_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dload_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aload_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aload_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aload_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aload_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iaload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_laload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_faload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_daload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aaload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_baload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_caload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_saload(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_istore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lstore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fstore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dstore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_astore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_istore_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_istore_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_istore_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_istore_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lstore_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lstore_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lstore_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lstore_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fstore_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fstore_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fstore_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fstore_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dstore_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dstore_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dstore_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dstore_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_astore_0(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_astore_1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_astore_2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_astore_3(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_aastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_bastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_castore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_sastore(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_pop(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_pop2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup_x1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup_x2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup2_x1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dup2_x2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_swap(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iadd(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ladd(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fadd(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dadd(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_isub(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lsub(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fsub(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dsub(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_imul(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lmul(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fmul(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dmul(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_idiv(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ldiv(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fdiv(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ddiv(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_irem(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lrem(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_frem(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_drem(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ineg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lneg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fneg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dneg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ishl(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lshl(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ishr(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lshr(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iushr(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lushr(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iand(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_land(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ior(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lor(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ixor(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lxor(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iinc(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2l(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2f(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2d(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_l2i(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_l2f(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_l2d(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_f2i(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_f2l(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_f2d(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_d2i(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_d2l(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_d2f(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2b(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2c(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_i2s(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lcmp(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fcmpl(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_fcmpg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dcmpl(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dcmpg(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifeq(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifne(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_iflt(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifge(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifgt(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifle(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmpeq(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmpne(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmplt(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmpge(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmpgt(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_icmple(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_acmpeq(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_if_acmpne(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_goto(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_jsr(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ret(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_tableswitch(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lookupswitch(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ireturn(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_lreturn(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_freturn(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_dreturn(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_areturn(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_return(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_getstatic(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_putstatic(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_getfield(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_putfield(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_invokevirtual(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_invokespecial(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_invokestatic(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_invokeinterface(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_invokedynamic(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_new(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_newarray(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_anewarray(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_arraylength(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_athrow(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_checkcast(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_instanceof(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_monitorenter(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_monitorexit(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_wide(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_multianewarray(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifnull(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_ifnonnull(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_goto_w(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_jsr_w(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_breakpoint(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_impdep1(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}
void jop_impdep2(JNativeMethodStack* jNativeMethodStack,JRuntimeEnv* jRuntimeEnv){}

Operations::Operations() {
    operations[0] = jop_nop;
    operations[1] = jop_aconst_null;
    operations[2] = jop_iconst_m1;
    operations[3] = jop_iconst_0;
    operations[4] = jop_iconst_1;
    operations[5] = jop_iconst_2;
    operations[6] = jop_iconst_3;
    operations[7] = jop_iconst_4;
    operations[8] = jop_iconst_5;
    operations[9] = jop_lconst_0;
    operations[10] = jop_lconst_1;
    operations[11] = jop_fconst_0;
    operations[12] = jop_fconst_1;
    operations[13] = jop_fconst_2;
    operations[14] = jop_dconst_0;
    operations[15] = jop_dconst_1;
    operations[16] = jop_bipush;
    operations[17] = jop_sipush;
    operations[18] = jop_ldc;
    operations[19] = jop_ldc_w;
    operations[20] = jop_ldc2_w;
    operations[21] = jop_iload;
    operations[22] = jop_lload;
    operations[23] = jop_fload;
    operations[24] = jop_dload;
    operations[25] = jop_aload;
    operations[26] = jop_iload_0;
    operations[27] = jop_iload_1;
    operations[28] = jop_iload_2;
    operations[29] = jop_iload_3;
    operations[30] = jop_lload_0;
    operations[31] = jop_lload_1;
    operations[32] = jop_lload_2;
    operations[33] = jop_lload_3;
    operations[34] = jop_fload_0;
    operations[35] = jop_fload_1;
    operations[36] = jop_fload_2;
    operations[37] = jop_fload_3;
    operations[38] = jop_dload_0;
    operations[39] = jop_dload_1;
    operations[40] = jop_dload_2;
    operations[41] = jop_dload_3;
    operations[42] = jop_aload_0;
    operations[43] = jop_aload_1;
    operations[44] = jop_aload_2;
    operations[45] = jop_aload_3;
    operations[46] = jop_iaload;
    operations[47] = jop_laload;
    operations[48] = jop_faload;
    operations[49] = jop_daload;
    operations[50] = jop_aaload;
    operations[51] = jop_baload;
    operations[52] = jop_caload;
    operations[53] = jop_saload;
    operations[54] = jop_istore;
    operations[55] = jop_lstore;
    operations[56] = jop_fstore;
    operations[57] = jop_dstore;
    operations[58] = jop_astore;
    operations[59] = jop_istore_0;
    operations[60] = jop_istore_1;
    operations[61] = jop_istore_2;
    operations[62] = jop_istore_3;
    operations[63] = jop_lstore_0;
    operations[64] = jop_lstore_1;
    operations[65] = jop_lstore_2;
    operations[66] = jop_lstore_3;
    operations[67] = jop_fstore_0;
    operations[68] = jop_fstore_1;
    operations[69] = jop_fstore_2;
    operations[70] = jop_fstore_3;
    operations[71] = jop_dstore_0;
    operations[72] = jop_dstore_1;
    operations[73] = jop_dstore_2;
    operations[74] = jop_dstore_3;
    operations[75] = jop_astore_0;
    operations[76] = jop_astore_1;
    operations[77] = jop_astore_2;
    operations[78] = jop_astore_3;
    operations[79] = jop_iastore;
    operations[80] = jop_lastore;
    operations[81] = jop_fastore;
    operations[82] = jop_dastore;
    operations[83] = jop_aastore;
    operations[84] = jop_bastore;
    operations[85] = jop_castore;
    operations[86] = jop_sastore;
    operations[87] = jop_pop;
    operations[88] = jop_pop2;
    operations[89] = jop_dup;
    operations[90] = jop_dup_x1;
    operations[91] = jop_dup_x2;
    operations[92] = jop_dup2;
    operations[93] = jop_dup2_x1;
    operations[94] = jop_dup2_x2;
    operations[95] = jop_swap;
    operations[96] = jop_iadd;
    operations[97] = jop_ladd;
    operations[98] = jop_fadd;
    operations[99] = jop_dadd;
    operations[100] = jop_isub;
    operations[101] = jop_lsub;
    operations[102] = jop_fsub;
    operations[103] = jop_dsub;
    operations[104] = jop_imul;
    operations[105] = jop_lmul;
    operations[106] = jop_fmul;
    operations[107] = jop_dmul;
    operations[108] = jop_idiv;
    operations[109] = jop_ldiv;
    operations[110] = jop_fdiv;
    operations[111] = jop_ddiv;
    operations[112] = jop_irem;
    operations[113] = jop_lrem;
    operations[114] = jop_frem;
    operations[115] = jop_drem;
    operations[116] = jop_ineg;
    operations[117] = jop_lneg;
    operations[118] = jop_fneg;
    operations[119] = jop_dneg;
    operations[120] = jop_ishl;
    operations[121] = jop_lshl;
    operations[122] = jop_ishr;
    operations[123] = jop_lshr;
    operations[124] = jop_iushr;
    operations[125] = jop_lushr;
    operations[126] = jop_iand;
    operations[127] = jop_land;
    operations[128] = jop_ior;
    operations[129] = jop_lor;
    operations[130] = jop_ixor;
    operations[131] = jop_lxor;
    operations[132] = jop_iinc;
    operations[133] = jop_i2l;
    operations[134] = jop_i2f;
    operations[135] = jop_i2d;
    operations[136] = jop_l2i;
    operations[137] = jop_l2f;
    operations[138] = jop_l2d;
    operations[139] = jop_f2i;
    operations[140] = jop_f2l;
    operations[141] = jop_f2d;
    operations[142] = jop_d2i;
    operations[143] = jop_d2l;
    operations[144] = jop_d2f;
    operations[145] = jop_i2b;
    operations[146] = jop_i2c;
    operations[147] = jop_i2s;
    operations[148] = jop_lcmp;
    operations[149] = jop_fcmpl;
    operations[150] = jop_fcmpg;
    operations[151] = jop_dcmpl;
    operations[152] = jop_dcmpg;
    operations[153] = jop_ifeq;
    operations[154] = jop_ifne;
    operations[155] = jop_iflt;
    operations[156] = jop_ifge;
    operations[157] = jop_ifgt;
    operations[158] = jop_ifle;
    operations[159] = jop_if_icmpeq;
    operations[160] = jop_if_icmpne;
    operations[161] = jop_if_icmplt;
    operations[162] = jop_if_icmpge;
    operations[163] = jop_if_icmpgt;
    operations[164] = jop_if_icmple;
    operations[165] = jop_if_acmpeq;
    operations[166] = jop_if_acmpne;
    operations[167] = jop_goto;
    operations[168] = jop_jsr;
    operations[169] = jop_ret;
    operations[170] = jop_tableswitch;
    operations[171] = jop_lookupswitch;
    operations[172] = jop_ireturn;
    operations[173] = jop_lreturn;
    operations[174] = jop_freturn;
    operations[175] = jop_dreturn;
    operations[176] = jop_areturn;
    operations[177] = jop_return;
    operations[178] = jop_getstatic;
    operations[179] = jop_putstatic;
    operations[180] = jop_getfield;
    operations[181] = jop_putfield;
    operations[182] = jop_invokevirtual;
    operations[183] = jop_invokespecial;
    operations[184] = jop_invokestatic;
    operations[185] = jop_invokeinterface;
    operations[186] = jop_invokedynamic;
    operations[187] = jop_new;
    operations[188] = jop_newarray;
    operations[189] = jop_anewarray;
    operations[190] = jop_arraylength;
    operations[191] = jop_athrow;
    operations[192] = jop_checkcast;
    operations[193] = jop_instanceof;
    operations[194] = jop_monitorenter;
    operations[195] = jop_monitorexit;
    operations[196] = jop_wide;
    operations[197] = jop_multianewarray;
    operations[198] = jop_ifnull;
    operations[199] = jop_ifnonnull;
    operations[200] = jop_goto_w;
    operations[201] = jop_jsr_w;
    operations[202] = jop_breakpoint;
    operations[254] = jop_impdep1;
    operations[255] = jop_impdep2;
}
