//
// Created by Admin on 2020/1/21.
//

#include "ByteCodeInterpreter.h"

JType *
ByteCodeInterpreter::execCode(const JavaClass *jc, u1 *code, u4 codeLen, u2 exceptionsNum, Exceptions *exceptions) {
    for(int i=0;i<codeLen;i++) {
        operations->operations[code[i]](jNativeMethodStack,jRuntimeEnv);
    }
    return nullptr;
}
