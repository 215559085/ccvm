#include <iostream>
#include "vm/ClassFile/JavaClass.h"
#include "vm/memory/MethodArea.h"


using namespace std;
int add(int* nums,int a,int length){
    int result=0;
    if(a<length){result += nums[a] + add(nums,a+1,length);}
    return result;
}
int main(){
    map<uint64_t ,JavaClass*> map;
    std::cout << "Hello, World!" << std::endl;
    string filepath = R"(H:\GITs\JByteCode\out\production\JByteCode\Main.class)";
    //auto* javaClass = new JavaClass(filepath);
    //javaClass->parseClassFile();
    //javaClass->showJavaClassMsg();
    //map.insert(make_pair(20,javaClass));
    //auto p = map.find(20);
    //cout<<"outermap: "<<p->second->getClassName()<<endl;
    MethodArea* methodArea = new MethodArea();
    methodArea->loadClassFromPath(R"(H:\GITs\JVMlearning\yvm\bytecode\java\lang\Object.class)");
    methodArea->loadClassFromPath(filepath);
    auto* object=methodArea->jHeap->JavaNewCreatObj(methodArea->findJavaClass("Main"));
    object->javaClassFile->showJavaClassMsg();
    return 0;
}

