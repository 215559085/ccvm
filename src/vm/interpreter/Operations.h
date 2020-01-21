//
// Created by Admin on 2020/1/21.
//

#ifndef CCVM_OPERATIONS_H
#define CCVM_OPERATIONS_H


#include "../memory/JFrame.h"
#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"

class Operations {
public:
    void (*operations[256])(JNativeMethodStack*,JRuntimeEnv*);
    Operations();
};




#endif //CCVM_OPERATIONS_H
