//
// Created by Admin on 2020/1/18.
//

#include <iostream>
#include "MethodArea.h"
#include "../interpreter/ByteCodeInterpreter.h"

bool fileExist(const std::string& path){
    std::fstream fs;
    fs.open(path,std::ios::in);
    if(fs){ return true;}
    else{ return false;}
};


JavaClass* MethodArea::findJavaClass(const string& className) {
    cout<<"finding class: "<< className<<endl;
    cout<<"findOBJ: "<<classMap->find("java/lang/Object")->second->getClassName()<<endl;
    const auto classPOS = classMap->find(className);
    if(classPOS != classMap->end()){
        cout<<"finded class: "<< className<<endl;
        return classPOS->second;}
    cout<<"class not find: "<< className<<endl;
    return nullptr;
}
MethodArea::MethodArea() {
    classMap=new unordered_map<string,JavaClass*>;
}

MethodArea::MethodArea(const vector<string>& libPaths) {
    this->searchPaths=libPaths;
}

bool MethodArea::loadClass(const char *className) {
    auto path = className2Path(className);
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    classMap->insert(make_pair(javaClass->getClassName(),javaClass));
    //....interfaces
    return false;
}
bool MethodArea::loadClassFromPath(const string& path) {
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    std::cout<<"Inserting className: "<<javaClass->getClassName()<<endl;
    classMap->insert(make_pair(javaClass->getClassName(),javaClass));
    std::cout<<"Inserted className: "<<javaClass->getClassName()<<"po: "<<javaClass<<endl;
    std::cout<<"Inserted className: "<<classMap->find(javaClass->getClassName())->first<<"po: "<<javaClass<<endl;

    //....interfaces
    return true;
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
    auto p = classMap->find(className);
    if(p!=classMap->end()){classMap->erase(p); return true;}
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
    classMap->insert(make_pair(javaClass->getClassName(),javaClass));
    return false;
}

JavaClass *MethodArea::loadClassIfAbsent(const string basicString) {
    return nullptr;
}

void MethodArea::linkClassIfAbsent(const string &jcName) {

}

void MethodArea::initClassIfAbsent(ByteCodeInterpreter &exec, const string &jcName) {

}

