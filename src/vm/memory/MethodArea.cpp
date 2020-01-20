//
// Created by Admin on 2020/1/18.
//

#include <iostream>
#include "MethodArea.h"

bool fileExist(const std::string& path){
    std::fstream fs;
    fs.open(path,std::ios::in);
    if(fs){ return true;}
    else{ return false;}
};


JavaClass* MethodArea::findJavaClass(const string& className) {
    auto classPOS = classMap.find(className);
    if(classPOS!=classMap.end()){return classPOS->second;}
    return nullptr;
}
MethodArea::MethodArea() {
    this->jHeap=new JHeap();
    jHeap->setMethodArea(this);
}

MethodArea::MethodArea(const vector<string>& libPaths) {
    this->searchPaths=libPaths;
    this->jHeap=new JHeap();
    jHeap->setMethodArea(this);
}

bool MethodArea::loadClass(const char *className) {
    auto path = className2Path(className);
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    classMap.insert(make_pair(javaClass->getClassName(),javaClass));
    //....interfaces
    return false;
}
bool MethodArea::loadClassFromPath(const string& path) {
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    classMap.insert(make_pair(javaClass->getClassName(),javaClass));
    std::cout<<"className: "<<javaClass->getClassName()<<endl;
    //....interfaces
    return false;
}

string MethodArea::className2Path(const string& name) {
    for (auto path : this->searchPaths) {
        if (path.length() > 0 && path[path.length() - 1] != '/') {
            path += '/';}
        path += name + ".class";
        if (fileExist(path)) {return path;}
    }
    return string("");
}

bool MethodArea::removeClass(const char *className) {
    auto p = classMap.find(className);
    if(p!=classMap.end()){classMap.erase(p); return true;}
    return false;
}

bool MethodArea::linkClass(const char *className) {

    return false;
}

bool MethodArea::initClass(const char *className) {
    return false;
}

bool MethodArea::loadClass(const string &path) {
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    classMap.insert(make_pair(javaClass->getClassName(),javaClass));
    return false;
}

