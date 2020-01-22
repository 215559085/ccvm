//
// Created by Admin on 2020/1/18.
//
#include <cstring>
#include "JFrame.h"
JFrame::JFrame(uint32_t maxLocalLen, uint32_t maxExpressionStack)
: maxLocalLen(maxLocalLen),
  maxExpressionStackLen(maxExpressionStack),
  nextFrame(nullptr),
  localVars(nullptr),
  expressionStack(nullptr)
  {
    if(maxLocalLen >0){localVars = new JType*[this->maxLocalLen];}
    if(this->maxExpressionStackLen > 0){expressionStack = new JType*[this->maxExpressionStackLen];}
    memset(localVars,0,sizeof(JType*)*maxLocalLen);
    memset(expressionStack,0,sizeof(JType*)*maxExpressionStack);
    this->expressionStackTopic=0;
}

JFrame::~JFrame() {delete[] localVars;delete[] expressionStack;}




void JFrame::pushVarIntoExpressionStack(JType *var) {
    expressionStack[this->expressionStackTopic++] = var;
}


void JFrame::setLocalVar(u1 index, JType *jType) {
    localVars[index] = jType;
}

JType* JFrame::getLocalVar(u1 index) {
    return localVars[index];
}

void JFrame::resize(int size) {
}

/*
void JFrame::resize(int size) {
    JType** newStack = new JType*[size];
    memset(newStack, 0, sizeof(JType*) * (size));
    for (int i = 0; i < maxExpressionStackLen; i++) {
        newStack[i] = expressionStack[i];
    }
    delete[] expressionStack;
    this->expressionStack = newStack;
    this->maxExpressionStackLen = size;
}
*/







