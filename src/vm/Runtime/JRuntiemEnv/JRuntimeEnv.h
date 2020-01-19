//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JRUNTIMEENV_H
#define CCVM_JRUNTIMEENV_H


#include "../../memory/JHeap.h"

class JRuntimeEnv {
    JRuntimeEnv();
    JRuntimeEnv(const vector<string> paths);
    ~JRuntimeEnv()= default;

public:
    JHeap* heap;
    MethodArea* methodArea;

};


#endif //CCVM_JRUNTIMEENV_H
