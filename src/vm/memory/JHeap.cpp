//
// Created by Admin on 2020/1/18.
//

#include "JHeap.h"
void typeDetermineControl(const string& des,JObject* obj){
    if(des[0] == 'L'){//class
        JObject* f = nullptr;
        obj->type='L';
        obj->fields.push_back(f);
    }else if(des[0] == '['){
        obj->type='[';
        JArray* u = nullptr;
        obj->fields.push_back(u);
    }else if(des[0] == 'B'){
        obj->type='B';
        JByte* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'S'){
        obj->type='S';
        JShort* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'D'){
        obj->type='D';
        JDouble* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'C'){
        obj->type='C';
        JChar* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'J'){
        obj->type='J';
        JLong* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'S'){
        obj->type='S';
        JShort* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'Z'){
        obj->type='Z';
        JBoolean* f = nullptr;
        obj->fields.push_back(f);
    }else if(des[0] == 'F'){
        obj->type='F';
        JFloat* f = nullptr;
        obj->fields.push_back(f);
    }
}


JObject* JHeap::JavaNewCreatObj(JavaClass& javaClass) {
    auto* obj=new JObject;
    obj->javaClassFile=&javaClass;
    obj->offset=now_offset;
    for(int fieldsOffset=0;fieldsOffset < javaClass.file.fieldsCount;fieldsOffset++){
        const string& des = javaClass.getString(javaClass.file.fields[fieldsOffset].descriptorIndex);
        typeDetermineControl(des,obj);
    }
        creatSuperFields(javaClass,obj);
    return nullptr;
}

void JHeap::creatSuperFields(const JavaClass& jc,JObject* object) {
    if(jc.file.superClass!=0){
      const JavaClass* super = methodArea->findJavaClass(jc.getSuperClassName());
      for(int fieldsOffset;fieldsOffset<super->file.fieldsCount;fieldsOffset++){
          const string& des = super->getString(super->file.fields[fieldsOffset].descriptorIndex);
          typeDetermineControl(des,object);
      }
      if(super->file.superClass != 0){
          creatSuperFields(*super,object);
      }
    }
}



