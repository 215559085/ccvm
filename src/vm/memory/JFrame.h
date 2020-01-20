//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JFRAME_H
#define CCVM_JFRAME_H


//JAVA NATIVE METHOD STACK

#include "../interpreter/ByteCode.h"
#include "../Runtime/JavaTypes/JType.h"
class JType;

class JFrame {
    friend class JNativeMethodStack;

public:
    explicit JFrame(uint32_t maxLocalLen,uint32_t maxExpressionStack);
    ~JFrame();

    bool status(){ return expressionStackTopic == 0;};//Empty: false
    template<typename LoadType>
    void loadIntoExpressionStackFromLcalVariable(u1 index);
    template<typename StoreType>
    void storeVarFromExpressionStackTop(u1 index);

    void pushVarIntoExpressionStack(JType* var);
    //
    template <typename popT>
    popT* popVarFromLocalVarStackTop();

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
class JNativeMethodStack{
    JNativeMethodStack()= default;
    ~JNativeMethodStack()= default;
    void newFrame(uint32_t maxLocalVar,uint32_t maxStack);
    void popFrame();
    JFrame* top(){ return topFrame;};


private:
    vector<JFrame*> stack;
    JFrame *topFrame{};
};



#endif //CCVM_JFRAME_H
