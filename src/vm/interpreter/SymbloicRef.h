//
// Created by Admin on 2020/1/22.
//

#ifndef CCVM_SYMBLOICREF_H
#define CCVM_SYMBLOICREF_H

#include "../ClassFile/JavaClass.h"

struct SymbolicRef {
    explicit SymbolicRef() : jc(nullptr) {}
    explicit SymbolicRef(JavaClass* jc) : jc(jc) {}
    explicit SymbolicRef(JavaClass* jc, std::string name,
                         std::string descriptor)
            : jc(jc), name(name), descriptor(descriptor) {}

    JavaClass* jc;
    std::string name;
    std::string descriptor;
};

SymbolicRef parseFieldSymbolicReference(const JavaClass* jc, u2 index);

SymbolicRef parseInterfaceMethodSymbolicReference(const JavaClass* jc,
                                                  u2 index);
SymbolicRef parseMethodSymbolicReference(const JavaClass* jc, u2 index);

SymbolicRef parseClassSymbolicReference(const JavaClass* jc, u2 index);


#endif //CCVM_SYMBLOICREF_H
