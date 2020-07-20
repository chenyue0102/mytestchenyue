//
// Created by EDZ on 2020/7/20.
//

#ifndef TESTMEDIA_LAMEHELPER_H
#define TESTMEDIA_LAMEHELPER_H
#include <stddef.h>

struct LameHelperData;
class LameHelper {
public:
    LameHelper();
    ~LameHelper();

public:
    bool open(const char *filePath);
    bool close();
    int decode(void *buffer, size_t bufLen);
    int getStereo()const;
    int getSampleRate()const;

private:
    LameHelperData *mData;
};


#endif //TESTMEDIA_LAMEHELPER_H
