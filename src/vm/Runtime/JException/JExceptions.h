//
// Created by Admin on 2020/1/20.
//

#ifndef CCVM_JEXCEPTIONS_H
#define CCVM_JEXCEPTIONS_H


class JExceptions {
    JExceptions()= default;
    ~JExceptions()= default;
};
class StackOverFlowErrorJException :JExceptions{
    const char* exception = "StackOverFlow";
};
class OutOfMemoryErrorJExcetion :JExceptions{
    const char* exception = "OutOfMemoryError";
};


#endif //CCVM_JEXCEPTIONS_H
