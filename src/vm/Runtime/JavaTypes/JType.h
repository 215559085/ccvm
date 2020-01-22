//
// Created by Admin on 2020/1/18.
//


#ifndef CCVM_JTYPE_H
#define CCVM_JTYPE_H
#include <stdint.h>
#include <vector>
#include "../../ClassFile/JavaClass.h"
using namespace std;

class JavaClass;

class JType {
public:
    virtual ~JType()= default;
    char type;
    bool isNext;
};
class JRef : public JType{
public:
    int i;
};
class JShort : public JType{
public:
    JShort()= default;
    explicit JShort(int a){i=a;};
    int16_t i;
};
class JByte : public JType{
public:
    JByte()= default;
    explicit JByte(int a){i=a;};
    uint8_t i;
};
class JChar : public JType{
public:
    JChar()= default;
    explicit JChar(int a){i=a;};
    char i;
};
class JInt : public JType{
public:
    JInt()= default;
    explicit JInt(int i){this->i=i;};
    int64_t i;
};
class JLong : public JType{
public:
    JLong()= default;
    explicit JLong(uint64_t a){i=a;};
    int64_t i;
};
class JDouble : public JType{
public:
    JDouble()= default;
    explicit JDouble(uint64_t a){i=a;};
    double i;
};
class JFloat : public JType{
public:
    JFloat()= default;
    explicit JFloat(uint64_t a){i=a;};
    float  i;
};
class JBoolean : public JType{
public:
    JBoolean()= default;
    explicit JBoolean(uint8_t a){i=a;};
    bool i;
};
class JArray : public JType{
public:
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
