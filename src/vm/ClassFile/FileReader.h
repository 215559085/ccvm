//
// Created by Admin on 2019/9/21.
//

#ifndef CCVM_FILEREADER_H
#define CCVM_FILEREADER_H

//to big-endian
#define getu8()

#define getu4(buf)                                                           \
    (((*(u4*)buf) & 0x000000FF) << 24) | (((*(u4*)buf) & 0x0000FF00) << 8) | \
        (((*(u4*)buf) & 0x00FF0000) >> 8) | (((*(u4*)buf) & 0xFF000000) >> 24)
#define getu2(buf) \
    (u2)((((*(u2*)buf) & 0x00FF) << 8) | (((*(u2*)buf) & 0xFF00) >> 8))

#include "../interpreter/ByteCode.h"
#include <fstream>

class FileReader{

public:
    FileReader() = default;
    // We must set file stream mode as std::ios::binary instead of default text
    // reading mode
    FileReader(const std::string& filePath) : fin(filePath, std::ios::binary) {
        this->filePath = filePath;
    }
    ~FileReader(){fin.close();}
    u4


    openFile(std::string filePath) {
        if (!fin.is_open()) {
            fin.open(filePath, std::ios::binary);
            return fin.is_open();
        }
        return true;
    }
    bool haveNoExtraBytes() { return fin.peek() == EOF; }
    //my compiler is little-endian integer representation
    u8 readU8(){
        fin.read(u8buf,8);
        return *(u8*)u8buf;
    }
    u4 readU4(){
        fin.read(u4buf,4);
        return getu4(u4buf);
    }
    u2 readU2(){
        fin.read(u2buf,2);
        return getu2(u2buf);
    }
    u1 readU1(){
        fin.read(u1buf,1);
        return *(u1*)u1buf;
    }

private:
    std::string filePath;
    std::ifstream fin;
    char u4buf[4];
    char u2buf[2];
    char u1buf[1];
    char u8buf[8];

};


#endif //CCVM_FILEREADER_H
