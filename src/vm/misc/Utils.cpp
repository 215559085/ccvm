//
// Created by Admin on 2020/1/20.
//

#include "Utils.h"
#include "../Runtime/JavaTypes/JType.h"
#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"
#include <typeinfo>
JType* cloneValue(JType* value) {
    if (value == nullptr) {
        return nullptr;
    }
    JType* dupvalue{};
    if (typeid(*value) == typeid(JDouble)) {
        dupvalue = new JDouble();
        dynamic_cast<JDouble*>(dupvalue)->i =
                dynamic_cast<JDouble*>(value)->i;
    } else if (typeid(*value) == typeid(JFloat)) {
        dupvalue = new JFloat();
        dynamic_cast<JFloat*>(dupvalue)->i =
                dynamic_cast<JFloat*>(value)->i;
    } else if (typeid(*value) == typeid(JInt)) {
        dupvalue = new JInt();
        dynamic_cast<JInt*>(dupvalue)->i = dynamic_cast<JInt*>(value)->i;
    } else if (typeid(*value) == typeid(JLong)) {
        dupvalue = new JDouble();
        dynamic_cast<JDouble*>(dupvalue)->i =
                dynamic_cast<JDouble*>(value)->i;
    } else if (typeid(*value) == typeid(JObject)) {
        dupvalue = new JObject();
        dynamic_cast<JObject*>(dupvalue)->javaClassFile =
                dynamic_cast<JObject*>(value)->javaClassFile;
        dynamic_cast<JObject*>(dupvalue)->offset =
                dynamic_cast<JObject*>(value)->offset;
    } else if (typeid(*value) == typeid(JArray)) {
        dupvalue = new JArray();
        dynamic_cast<JArray*>(dupvalue)->len =
                dynamic_cast<JArray*>(value)->len;
        dynamic_cast<JArray*>(dupvalue)->offset =
                dynamic_cast<JArray*>(value)->offset;
    } else {

    }
    return dupvalue;
}

JType* determineBasicType(const std::string& type) {
    if (IS_FIELD_INT(type) || IS_FIELD_BYTE(type) || IS_FIELD_CHAR(type) ||
        IS_FIELD_SHORT(type) || IS_FIELD_BOOL(type)) {
        return new JInt;
    }
    if (IS_FIELD_DOUBLE(type)) {
        return new JDouble;
    }
    if (IS_FIELD_FLOAT(type)) {
        return new JFloat;
    }
    if (IS_FIELD_LONG(type)) {
        return new JLong;
    }
    return nullptr;
}