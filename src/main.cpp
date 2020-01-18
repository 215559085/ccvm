#include <iostream>
#include <fstream>
#include "vm/ClassFile/JavaClass.h"
#include <math.h>


using namespace std;
int add(int* nums,int a,int length){
    int result=0;
    if(a<length){result += nums[a] + add(nums,a+1,length);}
    return result;
}
int main(){
    std::cout << "Hello, World!" << std::endl;
    string filepath = R"(H:\GITs\JByteCode\out\production\JByteCode\Main.class)";
    auto* javaClass = new JavaClass(filepath);
    javaClass->parseClassFile();
    javaClass->showJavaClassMsg();
    return 0;
}

