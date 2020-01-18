//
// Created by ChiCex on 2019/9/20.
//
// question how do i know the java class file using big-endian or little endian?


#ifndef CCVM_JAVACLASS_H
#define CCVM_JAVACLASS_H

#define FOR_EACH(iter, var) for (decltype(var) iter = 0; iter < var; iter++)


#include <fstream>
#include "../interpreter/ByteCode.h"
#include "ClassFile.h"
#include "FileReader.h"
#include <map>

using namespace std;

class JavaClass {
public:
    explicit JavaClass(const string& filepath);
    JavaClass(const JavaClass& rhs);
    ~JavaClass();

    void parseClassFile();
    void showJavaClassMsg();
    void parseConstantPool(u2 cp_count);
    void parseInterface(u2 interface_count);
    void parseFields(u2 fields_count);
    void parseAttribute(AttributeInfo** (&attrs),u2 attr_count);
    VerificationTypeInfo* parseVerificationType(u1 tag);



private:
    //FileReader
    ClassFile file{};
    FileReader reader;
    std::map<size_t, char*> staticVars;

    ElementValue *readToElementValueStructure();

    Annotation readToAnnotationStructure();

    TargetInfo *determineTargetType(u1 tag);

    bool parseMethod(u2 methodCount);
};










#endif //CCVM_JAVACLASS_H
