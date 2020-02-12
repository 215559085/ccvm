#include <iostream>
#include "vm/ClassFile/JavaClass.h"
#include "vm/memory/MethodArea.h"
#include "vm/memory/JFrame.h"
#include "vm/memory/JNativeMethodStack.h"
#include "vm/Runtime/JRuntiemEnv/JRuntimeEnv.h"

JRuntimeEnv* jRuntimeEnv;

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
    jRuntimeEnv = new JRuntimeEnv();
    jRuntimeEnv->methodArea->loadClassFromPath(R"(H:\GITs\JVMlearning\yvm\bytecode\java\lang\Object.class)");
    jRuntimeEnv->methodArea->loadClassFromPath(filepath);
    JObject* object=jRuntimeEnv->heap->JavaNewCreatObj(jRuntimeEnv->methodArea->findJavaClass("Main"));
    object->javaClassFile->showJavaClassMsg();
    auto* stack = new JNativeMethodStack{};
    stack->newFrame(20,20);
    stack->newFrame(30,30);
    stack->popFrame();
    stack->popFrame();
    uint32_t a=5,b=6,c=7,d=8,m=2,n=2;
    (m=a>b)&&(n=c>d);
    cout<<n<<endl;

    return 0;
}

