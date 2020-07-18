//
// Created by chenyue on 2020/7/18.
//

#ifndef TESTMEDIA_MP3PLAYER_H
#define TESTMEDIA_MP3PLAYER_H
#include <stdio.h>
#include "lame.h"

class Mp3Player {
public:
    Mp3Player();
    ~Mp3Player();
public:
    void openFile(const char *filePath);

private:
    FILE *mFile;
    hip_t mHip;
    unsigned char *mBuffer;
};


#endif //TESTMEDIA_MP3PLAYER_H
