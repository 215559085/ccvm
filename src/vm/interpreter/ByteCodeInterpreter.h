//
// Created by Admin on 2020/1/21.
//

#ifndef CCVM_BYTECODEINTERPRETER_H
#define CCVM_BYTECODEINTERPRETER_H


#include "Operations.h"

class ByteCodeInterpreter {

    Operations* operations;
    JType* execCode(const JavaClass* jc,u1* code,u4 codeLen,u2 exceptionsNum,Exceptions* exceptions);
    JNativeMethodStack* jNativeMethodStack;
    JRuntimeEnv* jRuntimeEnv;
};


#endif //CCVM_BYTECODEINTERPRETER_H
