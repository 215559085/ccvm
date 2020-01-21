cmake_minimum_required(VERSION 3.14)
project(ccvm)

set(CMAKE_CXX_STANDARD 14)

add_executable(ccvm
        src/main.cpp
        src/vm/ClassFile/JavaClass.cpp
        src/vm/ClassFile/JavaClass.h
        src/vm/interpreter/ByteCode.h
        src/vm/ClassFile/FileReader.cpp
        src/vm/ClassFile/FileReader.h
        src/vm/ClassFile/ClassFile.cpp
        src/vm/ClassFile/ClassFile.h
        src/vm/memory/JHeap.cpp
        src/vm/memory/JHeap.h
        src/vm/memory/JFrame.cpp
        src/vm/memory/JFrame.h
        src/vm/Runtime/JavaTypes/JType.cpp
        src/vm/Runtime/JavaTypes/JType.h
        src/vm/Runtime/JException.cpp
        src/vm/Runtime/JException.h
        src/vm/Runtime/JRuntiemEnv/JRuntimeEnv.cpp
        src/vm/Runtime/JRuntiemEnv/JRuntimeEnv.h
        src/vm/Runtime/NativeMethods/NativeMethods.cpp
        src/vm/Runtime/NativeMethods/NativeMethods.h
        src/vm/memory/MethodArea.cpp
        src/vm/memory/MethodArea.h
        src/vm/Runtime/JException/JExceptions.cpp
        src/vm/Runtime/JException/JExceptions.h src/vm/misc/Utils.cpp src/vm/misc/Utils.h src/vm/interpreter/ByteCodeInterpreter.cpp src/vm/interpreter/ByteCodeInterpreter.h src/vm/interpreter/Operations.cpp src/vm/interpreter/Operations.h)