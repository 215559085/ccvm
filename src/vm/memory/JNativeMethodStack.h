//
// Created by Admin on 2020/1/22.
//

#ifndef CCVM_JNATIVEMETHODSTACK_H
#define CCVM_JNATIVEMETHODSTACK_H


#include "../memory/JFrame.h"

class JFrame;

class JNativeMethodStack{
    ~JNativeMethodStack()= default;

public:
    JNativeMethodStack()= default;
    void popFrame();
    JFrame* top(){ return topFrame;};
    void newFrame(uint32_t maxLocalVar,uint32_t maxStack);

private:
    vector<JFrame*> stack;
    JFrame* topFrame{};

};


#endif //CCVM_JNATIVEMETHODSTACK_H
