//
// Created by chenyue on 2020/7/23.
//

#include "Mp3Parse.h"
#include <stdio.h>
#include <bit>

struct Mp3ParseData{

};
Mp3Parse::Mp3Parse() : mData(new Mp3ParseData()){

}

Mp3Parse::~Mp3Parse() {
    delete mData;
    mData = nullptr;
}

bool Mp3Parse::parseFile(const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    try{

    }catch (...){
        if (nullptr != file){
            fclose(file);
        }
        return false;
    }
    if (nullptr != file){
        fclose(file);
    }
    return true;
}
