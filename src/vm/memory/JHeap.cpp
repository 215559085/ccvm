//
// Created by Admin on 2020/1/18.
//

#include <iostream>
#include "JHeap.h"
#include "../Runtime/JRuntiemEnv/JRuntimeEnv.h"

void JHeap::typeDetermineControl(const string &des, JObject *obj) {
    if(des[0] == 'L'){//class
        JObject* f = nullptr;
        obj->type='L';
        obj->fields.push_back((JType*)f);
    }else if(des[0] == '['){
        obj->type='[';
        JArray* u = nullptr;
        obj->fields.push_back((JType*)u);
    }else if(des[0] == 'B'){
        obj->type='B';
        JByte* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'S'){
        obj->type='S';
        JShort* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'D'){
        obj->type='D';
        JDouble* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'C'){
        obj->type='C';
        JChar* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'J'){
        obj->type='J';
        JLong* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'S'){
        obj->type='S';
        JShort* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'Z'){
        obj->type='Z';
        JBoolean* f = nullptr;
        obj->fields.push_back((JType*)f);
    }else if(des[0] == 'F'){
        obj->type='F';
        JFloat* f = nullptr;
        obj->fields.push_back((JType*)f);
    }
    else if(des[0] == 'I'){
        obj->type='I';
        JInt* f = nullptr;
        obj->fields.push_back((JType*)f);
    }
}


JObject*  JHeap::JavaNewCreatObj(JavaClass* javaClass){
    auto* obj=new JObject;
    obj->javaClassFile = javaClass;
    obj->offset=now_offset;
    for(int fieldsOffset=0;fieldsOffset < javaClass->file.fieldsCount;fieldsOffset++){
        const string& des = javaClass->getString(javaClass->file.fields[fieldsOffset].descriptorIndex);
        //std::cout<<"fields: "<<des[0]<<endl;
        typeDetermineControl(des,obj);
    }
    std::cout<<"startSuper"<<endl;
    creatSuperFields(javaClass,obj);
    std::cout<<"stopSuper"<<endl;
    //std::cout<<"container: "<<data->getContainer()->size()<<endl;
    data->getContainer()->insert(make_pair(now_offset,(JType*)obj));
    //std::cout<<"container: "<<data->getContainer()->size()<<endl;
    auto p=data->getContainer()->find((uint64_t)0);
    //std::cout<<"newFields: "<<((JObject*)p->second)->fields.size()<<endl;
    now_offset+=1;
    return obj;
}

void JHeap::creatSuperFields(JavaClass* jc,JObject* object) {
    if (jc->file.superClass != 0) {
        std::cout<<"needToFind superClassName: "<<jc->getClassName()<<endl;
        JavaClass *super = jRuntimeEnv->methodArea->findJavaClass(jc->getSuperClassName());
        std::cout<<"superClassName: "<<super->getClassName()<<endl;
        //std::cout<<"superFieldsOffset: "<<super->file.fieldsCount<<endl;
        for (int fieldsOffset = 0; fieldsOffset < (super->file.fieldsCount); fieldsOffset++) {
            const string des = super->getString(super->file.fields[fieldsOffset].descriptorIndex);
            //std::cout<<"superFields: "<<des<<endl;
            typeDetermineControl(des, object);
            if (super->file.superClass != 0) {
                creatSuperFields(super, object);
            }
        }
    }
}

JType* JHeap::getElement(JArray array, int64_t i) {
	return nullptr;
}

JType *JHeap::getFieldByName(JavaClass *pClass, string basicString, string basicString1, JObject *pObject) {
    return nullptr;
}

void JHeap::putFieldByName(JavaClass *pClass, string basicString, string basicString1, JObject *pObject, JType *pType) {

}

void JHeap::putFieldByOffset(JObject object, int i, JArray *pArray) {

}

JArray *JHeap::JavaNewCreatCharArray(const string &source, uint64_t len) {
    return nullptr;
}

void JHeap::putElement(JType jType, int index, JType *value) {

}

JArray *JHeap::JavaNewCreatObjArray(JavaClass &javaClass, int len) {
    return nullptr;
}

JArray *JHeap::JavaNewCreatPODArray(int type, int len) {
    return nullptr;
}


