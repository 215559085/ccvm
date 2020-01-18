//
// Created by Admin on 2019/9/21.
//

#ifndef CCVM_JAVACLASSLOADER_H
#define CCVM_JAVACLASSLOADER_H


#include "JavaClass.h"
#include "ClassFile.h"

class JavaClassLoader {

public:
    JavaClass parseClassFile(ClassFile classFile);



};


#endif //CCVM_JAVACLASSLOADER_H
