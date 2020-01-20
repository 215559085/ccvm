//
// Created by Admin on 2020/1/18.
//

#ifndef CCVM_JHEAP_H
#define CCVM_JHEAP_H


#include "../Runtime/JavaTypes/JType.h"
#include "MethodArea.h"
#include <map>
#include <vector>
//GC ROOT
class MethodArea;
template<typename T> class JHeapContainer{
public:
    JHeapContainer(){data = new map<uint64_t ,T*>;};
    virtual ~JHeapContainer()= default;
    virtual uint64_t place();
    void remove(uint64_t offset);
    T& find(uint64_t offset);
    bool exist(uint64_t offset);
    map<uint64_t ,T*>* getContainer(){ return data;};
private:
    map<uint64_t ,T*>* data; //<offset,type*>
};

template<typename T>
uint64_t JHeapContainer<T>::place() {
    return 0;
}

//GC ROOT's Set
class JHeapContainerSet{
public:
    JHeapContainerSet();
    ~JHeapContainerSet();
private:
    vector<JHeapContainer<JType>> rootSet;
};

class JHeap {

public:
    JHeap(){this->data=new JHeapContainer<JType>();};
    ~JHeap()= default;
    JObject* JavaNewCreatObj(JavaClass* javaClass);
    void creatSuperFields(const JavaClass& super,JObject* thisClass);
    JArray* JavaNewCreatPODArray(int type,int len);
    JArray* JavaNewCreatObjArray(JavaClass& javaClass,int len);
    JArray* JavaNewCreatCharArray(const string& source,uint64_t len);

    JObject* JavaRootNewCreatObj(JavaClass& javaClass);
    JArray* JavaRootNewCreatPODArray(int type,int len);
    JArray* JavaRootNewCreatObjArray(JavaClass& javaClass,int len);
    JArray* JavaRootNewCreatCharArray(const string& source,uint64_t len);
    void setMethodArea(MethodArea* methodArea1){methodArea=methodArea1;}
private:
    static void typeDetermineControl(const string& des,JObject* obj);
    JHeapContainer<JType>* data;
    //JHeapContainerSet* data;
    uint64_t now_offset = 0;
    MethodArea* methodArea;
};

#endif //CCVM_JHEAP_H
