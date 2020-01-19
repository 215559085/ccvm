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
#include "../Runtime/JavaTypes/JType.h"
#include <map>

using namespace std;

class JavaClass{
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
    inline string getString(u2 offset) const{
        return reinterpret_cast<const char*>(dynamic_cast<CONSTANT_Utf8_info*>(file.constantPoolInfo[offset])->bytes);
    }
    inline string getClassName(){
        return getString(dynamic_cast<CONSTANT_Class*>(file.constantPoolInfo[file.thisClass])->nameIndex);
    }
    inline const string getSuperClassName() const {
        return file.superClass == 0
               ? ""
               : getString(dynamic_cast<CONSTANT_Class*>(file.constantPoolInfo[file.superClass])->nameIndex);
    }
    inline const string getInterfaceClassName(u2 index) const {
        return getString(dynamic_cast<CONSTANT_Class*>(
                                 file.constantPoolInfo[file.interfaces[index]])
                                 ->nameIndex);
    }
    inline bool hasSuperClass() const { return file.superClass != 0; }
    inline bool hasInterface() const { return file.interfacesCount != 0; }
    inline u2 getInterfaceCount() const { return file.interfacesCount; }
    inline u2 getAccessFlag() const { return file.accessFlags; }
    MethodInfo* findMethod(const string& methodName,
                           const string& methodDescriptor) const;
    bool setStaticVar(const string& name, const string& descriptor,
                      JType* value);
    JType* getStaticVar(const string& name, const string& descriptor);
    VerificationTypeInfo* parseVerificationType(u1 tag);
    ClassFile file{};
private:
    //FileReader

    FileReader reader;
    std::map<size_t, char*> staticVars;
    ElementValue *readToElementValueStructure();
    Annotation readToAnnotationStructure();
    TargetInfo *determineTargetType(u1 tag);
    bool parseMethod(u2 methodCount);
};










#endif //CCVM_JAVACLASS_H
