//
// Created by Admin on 2020/1/18.
//

#include "MethodArea.h"

JavaClass *MethodArea::findJavaClass(const string& className) {
    auto classPOS = classMap.find(className);
    if(classPOS!=classMap.end()){
        return classPOS->second;
    }
    return nullptr;
}

MethodArea::MethodArea(const vector<string> libPaths) {

}

bool MethodArea::loadClass(const char *className) {
    //auto path =
    return false;
}

string MethodArea::className2Path(const string& name) {
    for (auto path : this->searchPaths) {
        if (path.length() > 0 && path[path.length() - 1] != '/') {
            path += '/';
        }
        path += name + ".class";
        fstream fin;
        fin.open(path, ios::in);
        if (fin) {
            fin.close();
            return path;  // Return only if it's a valid file path
        }
        fin.close();
    }
    return string("");
}
