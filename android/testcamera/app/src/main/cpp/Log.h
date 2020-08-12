//
// Created by chenyue on 2020/7/20.
//

#ifndef TESTMEDIA_LOG_H
#define TESTMEDIA_LOG_H
#include <string>

//日志
class Log {
public:
    Log();
    ~Log();

public:
    void setTag(const char *tag);
    const char* getTag();

public:
    int d(const char* fmt, ...);
    int i(const char* fmt, ...);
    int w(const char* fmt, ...);
    int e(const char* fmt, ...);

public:
    int log(int prio, const char* tag, const char* fmt, ...);
    int log(int prio, const char* tag, const char* fmt, va_list ap);

private:
    std::string mTag;
};


#endif //TESTMEDIA_LOG_H
