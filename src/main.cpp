#include <iostream>
#include "vm/ClassFile/JavaClass.h"
#include "vm/memory/MethodArea.h"
#include "vm/memory/JFrame.h"


using namespace std;
int add(int* nums,int a,int length){
    int result=0;
    if(a<length){result += nums[a] + add(nums,a+1,length);}
    return result;
}
int main(){
    string filepath = R"(H:\GITs\JByteCode\out\production\JByteCode\Main.class)";
    //auto* javaClass = new JavaClass(filepath);
    //javaClass->parseClassFile();
    //javaClass->showJavaClassMsg();
    //map.insert(make_pair(20,javaClass));
    //auto p = map.find(20);
    //cout<<"outermap: "<<p->second->getClassName()<<endl;
    auto* methodArea = new MethodArea();
    methodArea->loadClassFromPath(R"(H:\GITs\JVMlearning\yvm\bytecode\java\lang\Object.class)");
    methodArea->loadClassFromPath(filepath);
    auto* object=methodArea->jHeap->JavaNewCreatObj(methodArea->findJavaClass("Main"));
    object->javaClassFile->showJavaClassMsg();
    JNativeMethodStack* stack = new JNativeMethodStack{};
    stack->newFrame(20,20);
    stack->newFrame(30,30);
    stack->popFrame();
    stack->popFrame();

    return 0;
}

