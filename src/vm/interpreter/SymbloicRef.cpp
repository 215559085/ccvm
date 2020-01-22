//
// Created by Admin on 2020/1/22.
//

#include "SymbloicRef.h"
#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"


std::string peelArrayComponentTypeFrom(const std::string& descriptor) {
    int i = 0;
    while (descriptor[i] == '[') {
        i++;
    }
    std::string arrayComponentTypeName(descriptor);
    return arrayComponentTypeName.substr(i,
                                         arrayComponentTypeName.length() - i);
}

SymbolicRef parseFieldSymbolicReference(const JavaClass *jc, u2 index) {
    auto *fr = (CONSTANT_Fieldref *)jc->file.constantPoolInfo[index];
    auto *nat =
            (CONSTANT_NameAndType *)jc->file.constantPoolInfo[fr->nameAndTypeIndex];
    auto *cl = (CONSTANT_Class *)jc->file.constantPoolInfo[fr->classIndex];

    auto fieldName = jc->getString(nat->nameAndTypeIndex);
    auto fieldDesc = jc->getString(nat->descriptionIndex);
    auto fieldClass = jRuntimeEnv->methodArea->loadClassIfAbsent(jc->getString(cl->nameIndex));
    jRuntimeEnv->methodArea->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{fieldClass, fieldName, fieldDesc};
}

SymbolicRef parseInterfaceMethodSymbolicReference(const JavaClass *jc,
                                                  u2 index) {
    auto *imr = (CONSTANT_InterfaceMethodref *)jc->file.constantPoolInfo[index];
    auto *nat =
            (CONSTANT_NameAndType *)jc->file.constantPoolInfo[(imr->nameAndTypeIndex)];
    auto *cl = (CONSTANT_Class *)jc->file.constantPoolInfo[imr->interfaceIndex];

    auto interfaceMethodName = jc->getString(nat->nameAndTypeIndex);
    auto interfaceMethodDesc = jc->getString(nat->descriptionIndex);
    auto interfaceMethodClass =
            jRuntimeEnv->methodArea->loadClassIfAbsent(jc->getString(cl->nameIndex));
    jRuntimeEnv->methodArea->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{interfaceMethodClass, interfaceMethodName,
                       interfaceMethodDesc};
}

SymbolicRef parseMethodSymbolicReference(const JavaClass *jc, u2 index) {
    auto *mr = (CONSTANT_Methodref *)jc->file.constantPoolInfo[index];
    auto *nat =
            (CONSTANT_NameAndType *)jc->file.constantPoolInfo[mr->nameAndTypeIndex];
    auto *cl = (CONSTANT_Class *)jc->file.constantPoolInfo[mr->methodIndex];

    auto methodName = jc->getString(nat->nameAndTypeIndex);
    auto methodDesc = jc->getString(nat->descriptionIndex);
    auto methodClass = jRuntimeEnv->methodArea->loadClassIfAbsent(jc->getString(cl->nameIndex));
    jRuntimeEnv->methodArea->linkClassIfAbsent(jc->getString(cl->nameIndex));

    return SymbolicRef{methodClass, methodName, methodDesc};
}

SymbolicRef parseClassSymbolicReference(const JavaClass *jc, u2 index) {
    auto *cl = (CONSTANT_Class *)jc->file.constantPoolInfo[index];
    auto className = jc->getString(cl->nameIndex);
    if (className[0] == '[') {
        className = peelArrayComponentTypeFrom(className);
    }

    auto c = jRuntimeEnv->methodArea->loadClassIfAbsent(className);
    jRuntimeEnv->methodArea->linkClassIfAbsent(className);
    return SymbolicRef{c};
}