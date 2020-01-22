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




#endif //CCVM_UTILS_H
