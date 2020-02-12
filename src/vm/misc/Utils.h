//
// Created by Admin on 2020/1/20.
//

#ifndef CCVM_UTILS_H
#define CCVM_UTILS_H


#include <string>
#include <fstream>
#include "../interpreter/ByteCode.h"
#include "../Runtime/JavaTypes/JType.h"
//#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"

#define IS_SIGNATURE_POLYMORPHIC_METHOD(className, methodName) \
    (className == "java/lang/invoke/MethodHandle" &&           \
     (methodName == "invokeExtract" || methodName == "invoke"))

JType* cloneValue(JType* value);
class Utils {
    Utils();
    };
inline u1 consumeU1(const u1* code, u4* opidx) {
    const u1 byte = code[++*opidx];
    return byte;
}

inline u2 consumeU2(const u1* code, u4* opidx) {
    const u1 indexbyte1 = code[++*opidx];
    const u1 indexbyte2 = code[++*opidx];
    const u2 index = (indexbyte1 << 8) | indexbyte2;
    return index;
}

inline u4 consumeU4(const u1* code, u4* opidx) {
    const u1 byte1 = code[++*opidx];
    const u1 byte2 = code[++*opidx];
    const u1 byte3 = code[++*opidx];
    const u1 byte4 = code[++*opidx];
    const u4 res = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | (byte4);
    return res;
}

#define IS_TYPE(type, strRepresentation)                          \
    inline bool IS_FIELD_##type(const std::string& descriptor) {  \
        return descriptor == strRepresentation;                   \
    }                                                             \
    inline bool IS_METHOD_##type(const std::string& descriptor) { \
        return descriptor == strRepresentation == 0;              \
    }

#define IS_REF_TYPE(type, c)                                          \
    inline bool IS_FIELD_REF_##type(const std::string& descriptor) {  \
        return descriptor[0] == c;                                    \
    }                                                                 \
    inline bool IS_METHOD_REF_##type(const std::string& descriptor) { \
        return descriptor[0] == c;                                    \
    }

IS_TYPE(BYTE, "B")
IS_TYPE(CHAR, "C")
IS_TYPE(DOUBLE, "D")
IS_TYPE(FLOAT, "F")
IS_TYPE(INT, "I")
IS_TYPE(LONG, "J")
IS_TYPE(SHORT, "S")
IS_TYPE(BOOL, "Z")
IS_TYPE(VOID, "V")

IS_REF_TYPE(CLASS, 'L');
IS_REF_TYPE(ARRAY, '[');

JType* determineBasicType(const std::string& type);



#endif //CCVM_UTILS_H
