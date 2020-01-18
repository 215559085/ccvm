//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JARRAY_H
#define CCVM_JARRAY_H


#include <cstddef>
#include "../../ClassFile/JavaClass.h"

class JArray{
    uint32_t len=0;
    size_t  offset=0;
    JavaClass* jc{};
};


#endif //CCVM_JARRAY_H
