//
// Created by chenyue on 2020/7/23.
//

#ifndef TESTMEDIA_MP3PARSE_H
#define TESTMEDIA_MP3PARSE_H

struct Mp3ParseData;
class Mp3Parse {
public:
    Mp3Parse();
    ~Mp3Parse();

public:
    bool parseFile(const char *filePath);

private:
    Mp3ParseData *mData;
};


#endif //TESTMEDIA_MP3PARSE_H
