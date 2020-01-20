//
// Created by Admin on 2020/1/18.
//


#ifndef CCVM_JTYPE_H
#define CCVM_JTYPE_H
#include <stdint-gcc.h>
#include <vector>
#include "../../ClassFile/JavaClass.h"
using namespace std;

class JavaClass;

class JType {
public:
    uint64_t len = 1;
    char type;
};
class JShort : public JType{
    int64_t i;
};
class JByte : public JType{
    int64_t i;
};
class JChar : public JType{
    int64_t i;
};
class JInt : public JType{
    int64_t i;
};
class JLong : public JType{
    long l;
};
class JDouble : public JType{
    double d = 0;
};
class JFloat : public JType{
    float  f;
};
class JBoolean : public JType{
    bool b;
};
class JArray : public JType{
      explicit JArray()= default;
      int len = 0;
      uint64_t offset=0;
};

class JObject : public JType{
public:
    uint64_t offset=0;
    const JavaClass* javaClassFile{};
    vector<JType*> fields;
    explicit JObject()= default;
    ~JObject()= default;

};
#endif //CCVM_JTYPE_H
