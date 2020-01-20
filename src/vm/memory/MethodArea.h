//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_METHODAREA_H
#define CCVM_METHODAREA_H


#include <vector>
#include <unordered_map>
#include "../ClassFile/JavaClass.h"
#include "JHeap.h"
class JHeap;
class MethodArea {
    ~MethodArea(){classMap.clear();delete[] linkedClassFiles;delete[] initedClassFiles;};
private:
    unordered_map<string,JavaClass*> classMap;
    JavaClass** linkedClassFiles;
    JavaClass** initedClassFiles;
    vector<string> searchPaths;

public:
    explicit MethodArea(const vector<string>& libPaths);
    explicit MethodArea();
    JavaClass* findJavaClass(const string& className);
    bool loadClass(const char* className);
    bool loadClass(const string& path);
    bool removeClass(const char* className);
    bool linkClass(const char* className);
    bool initClass(const char* className);
    JHeap* jHeap;
    string className2Path(const string &name);

    bool loadClassFromPath(const string &path);
};


#endif //CCVM_METHODAREA_H
