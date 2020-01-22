//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JRUNTIMEENV_H
#define CCVM_JRUNTIMEENV_H


#include "../../memory/JHeap.h"
#include "../../memory/MethodArea.h"
class JHeap;
class MethodArea;
class JRuntimeEnv {
public:
    JRuntimeEnv(){heap=new JHeap;methodArea=new MethodArea;};
    JRuntimeEnv(const vector<string> paths);
    ~JRuntimeEnv()= default;

    JHeap* heap;
    MethodArea* methodArea;
};

extern JRuntimeEnv* jRuntimeEnv;

#endif //CCVM_JRUNTIMEENV_H
