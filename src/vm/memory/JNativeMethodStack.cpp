//
// Created by Admin on 2020/1/22.
//

#include "JNativeMethodStack.h"

void JNativeMethodStack::newFrame(uint32_t maxLocalVar, uint32_t maxStack) {
    auto* frame = new JFrame(maxLocalVar,maxStack);
    frame->nextFrame = topFrame;
    this->stack.push_back(frame);
    topFrame=frame;
}

void JNativeMethodStack::popFrame() {
    auto* f = topFrame;
    topFrame=topFrame->nextFrame;
    stack.pop_back();
    delete(f);
}
