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
template<typename T> class JHeapContainer{
public:
    JHeapContainer()= default;
    virtual ~JHeapContainer()= default;
    virtual uint64_t place();
    void remove(uint64_t offset);
    T& find(uint64_t offset);
    bool exist(uint64_t offset);
    auto* getContainer(){ return data;};
private:
    map<uint64_t ,T,less<>> data; //<offset,type*>
};

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

    JHeap();
    ~JHeap()= default;
    JObject* JavaNewCreatObj(JavaClass& javaClass);
    void creatSuperFields(const JavaClass& super,JObject* thisClass);
    JArray* JavaNewCreatPODArray(int type,int len);
    JArray* JavaNewCreatObjArray(JavaClass& javaClass,int len);
    JArray* JavaNewCreatCharArray(const string& source,uint64_t len);

    JObject* JavaRootNewCreatObj(JavaClass& javaClass);
    JArray* JavaRootNewCreatPODArray(int type,int len);
    JArray* JavaRootNewCreatObjArray(JavaClass& javaClass,int len);
    JArray* JavaRootNewCreatCharArray(const string& source,uint64_t len);

private:
    JHeapContainerSet* data;
    uint64_t now_offset;
    MethodArea* methodArea;
};

#endif //CCVM_JHEAP_H
