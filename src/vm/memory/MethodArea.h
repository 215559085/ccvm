//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_METHODAREA_H
#define CCVM_METHODAREA_H


#include <vector>
#include <unordered_map>
#include "../ClassFile/JavaClass.h"

class MethodArea {
    ~MethodArea(){classMap.clear();delete[] linkedClassFiles;delete[] initedClassFiles;};
private:
    unordered_map<string,JavaClass*> classMap;
    JavaClass** linkedClassFiles;
    JavaClass** initedClassFiles;
    vector<string> searchPaths;
public:
    JavaClass* findJavaClass(const string& className);
    bool loadClass(const char* className);
    bool removeClass(const char* className);
    bool linkClass(const char* className);
    bool initClass(const char* className);
    MethodArea(const vector<string> libPaths);

    string className2Path(const string &name);
};


#endif //CCVM_METHODAREA_H
