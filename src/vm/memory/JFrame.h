//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JFRAME_H

#define CCVM_JFRAME_H
#include "../interpreter/ByteCode.h"
#include "../Runtime/JavaTypes/JType.h"

class JType;

class JFrame {
    friend class JNativeMethodStack;

public:
    explicit JFrame(uint32_t maxLocalLen,uint32_t maxExpressionStack);
    ~JFrame();

    bool status(){ return expressionStackTopic == 0;};//Empty: false

    template<typename LoadType>void loadIntoExpressionStackFromLocalVariable(u1 index) {
        auto *var = new LoadType;
        var->i = dynamic_cast<LoadType*>(localVars[index])->i;
        expressionStack[expressionStackTopic++] = var;
    };
    template<typename StoreType>void storeVarFromExpressionStackTop(u1 index) {
        if(expressionStackTopic){
            expressionStackTopic--;
            auto* var = dynamic_cast<StoreType*>(expressionStack[expressionStackTopic]);
            expressionStack[expressionStackTopic]= nullptr;
            localVars[index] = var;
        }
    };
    void pushVarIntoExpressionStack(JType* var);
    template <typename popT>popT* popVarFromLocalVarStackTop() {
        if(expressionStackTopic){
            expressionStackTopic--;
            auto* var = dynamic_cast<popT*>(expressionStack[expressionStackTopic]);
            expressionStack[expressionStackTopic]=nullptr;
            return var;
        }
        return nullptr;
    };
    void setLocalVar(u1 index,JType* jType);
    JType* getLocalVar(u1 index);
    void resize(int size);//useless
private:
    JType** localVars;
    JType** expressionStack;
    const int maxLocalLen;
    const int maxExpressionStackLen;
    int expressionStackTopic;
    JFrame* nextFrame;
};




#endif
//CCVM_JFRAME
