//
// Created by Admin on 2020/1/18.
//

#include "JRuntimeEnv.h"

JRuntimeEnv::JRuntimeEnv(const vector<string> paths) {
    this->methodArea = new MethodArea(paths);
    this->heap = new JHeap;

}
