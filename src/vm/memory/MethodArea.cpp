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
    JavaClass* javaClass = findJavaClass(className);
    FOR_EACH(offset,javaClass->file.fieldsCount){
        const string& des = javaClass->getString(javaClass->file.fields[offset].descriptorIndex);

        if(des[0]=='L'){//FIELD IS CLASS
            if(((javaClass->file.fields[offset].accessFlags) & (int)0x0008) != 0){//IS STATIC
                JObject* fieldObj = nullptr;
                FOR_EACH(attrOffset,javaClass->file.fields[offset].attributeCount){
                    if(typeid(*javaClass->file.fields[offset].attributes[attrOffset])== typeid(ATTR_ConstantValue)){
                        if(des == "Ljava/lang/String;"){
                            const string& constantString
                                    = javaClass
                                    ->getString(((CONSTANT_String*)javaClass
                                                ->file.constantPoolInfo[((ATTR_ConstantValue*)javaClass
                                                            ->file.fields[offset].attributes[attrOffset])
                                                            ->constantValueIndex])
                                                ->stringIndex);
                            size_t strlen = constantString.length();
                            fieldObj=jRuntimeEnv->heap->JavaNewCreatObj(loadClassIfAbsent("java/lang/String"));
                            fieldObj->fields[0] =  jRuntimeEnv->heap->JavaNewCreatCharArray(constantString,strlen);
                        }
                    }
                }
                javaClass->staticVars.insert(make_pair(offset,fieldObj));
            }
        }else if(des[0] == '['){//FIELDS IS ARRAY
            JType* basicField = determineBasicType(des);

            FOR_EACH(fieldAttr,javaClass->file.fields[offset].attributeCount) {
                if (typeid(*javaClass->file.fields[offset]
                        .attributes[fieldAttr]) ==
                    typeid(ATTR_ConstantValue)) {
                    if (typeid(*javaClass->file.constantPoolInfo
                    [((ATTR_ConstantValue*)javaClass->file
                                    .fields[offset]
                                    .attributes[fieldAttr])
                                    ->constantValueIndex]) ==
                        typeid(CONSTANT_Long)) {
                        ((JLong*)basicField)->i =
                                ((CONSTANT_Long*)javaClass->file.constantPoolInfo
                                [((ATTR_ConstantValue*)javaClass->file
                                                .fields[offset]
                                                .attributes[fieldAttr])
                                                ->constantValueIndex])
                                        ->val;
                    } else if (typeid(*javaClass->file.constantPoolInfo
                    [((ATTR_ConstantValue*)javaClass
                                    ->file.fields[offset]
                                    .attributes[fieldAttr])
                                    ->constantValueIndex]) ==
                               typeid(CONSTANT_Double)) {
                        ((JDouble*)basicField)->i =
                                ((CONSTANT_Double*)javaClass->file.constantPoolInfo
                                [((ATTR_ConstantValue*)javaClass->file
                                                .fields[offset]
                                                .attributes[fieldAttr])
                                                ->constantValueIndex])
                                        ->val;
                    } else if (typeid(*javaClass->file.constantPoolInfo
                    [((ATTR_ConstantValue*)javaClass
                                    ->file.fields[offset]
                                    .attributes[fieldAttr])
                                    ->constantValueIndex]) ==
                               typeid(CONSTANT_Float)) {
                        ((JFloat*)basicField)->i =
                                ((CONSTANT_Float*)javaClass->file.constantPoolInfo
                                [((ATTR_ConstantValue*)javaClass->file
                                                .fields[offset]
                                                .attributes[fieldAttr])
                                                ->constantValueIndex])
                                        ->val;
                    } else if (typeid(*javaClass->file.constantPoolInfo
                    [((ATTR_ConstantValue*)javaClass
                                    ->file.fields[offset]
                                    .attributes[fieldAttr])
                                    ->constantValueIndex]) ==
                               typeid(CONSTANT_Integer)) {
                        ((JInt*)basicField)->i =
                                ((CONSTANT_Integer*)javaClass->file.constantPoolInfo
                                [((ATTR_ConstantValue*)javaClass->file
                                                .fields[offset]
                                                .attributes[fieldAttr])
                                                ->constantValueIndex])
                                        ->val;
                    } else{
                        cerr<<"link array class error;"<<endl;
                        return false;
                    }
                }
            }
            javaClass->staticVars.insert(make_pair(offset,basicField));
        }
    }
    linkedClassFiles.insert(javaClass->getClassName());
    return true;
}

bool MethodArea::initClass(ByteCodeInterpreter& exec, const string& jcName) {
    initedClassFiles.insert(jcName);
    auto* jc = findJavaClass(jcName);
    if (jc->findMethod("<clinit>", "()V")) {
        exec.invokeByName(jc, "<clinit>", "()V");
    }
    return false;
}

bool MethodArea::loadClass(const string &jcName) {
    auto path = className2Path(jcName);
    auto* javaClass=new JavaClass(path);
    javaClass->parseClassFile();
    classMap->insert(make_pair(javaClass->getClassName(),javaClass));
    return false;
}
bool MethodArea::loadClass(const string &path,bool fromPath) {
    if(fromPath) {
        auto *javaClass = new JavaClass(path);
        javaClass->parseClassFile();
        classMap->insert(make_pair(javaClass->getClassName(), javaClass));
    }
    return true;
}
JavaClass *MethodArea::loadClassIfAbsent(const string basicString) {
    JavaClass* jc = findJavaClass(basicString);
    if (jc) {
        return jc;
    }
    loadClass(basicString);
    return findJavaClass(basicString);
}

void MethodArea::linkClassIfAbsent(const string &jcName) {
    bool linked = false;
    for (auto p : linkedClassFiles) {
        if (p == jcName) {
            linked = true;
        }
    }
    if (!linked) {
        linkClass(jcName.c_str());
    }
}

void MethodArea::initClassIfAbsent(ByteCodeInterpreter &exec, const string &jcName) {
    bool inited = false;
    for (auto p : initedClassFiles) {
        if (p == jcName) {
            inited = true;
        }
    }
    if (!inited) {
        initClass(exec, jcName);
    }
}

