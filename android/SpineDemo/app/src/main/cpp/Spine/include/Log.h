//
// Created by chenyue on 2020/7/20.
//

#ifndef TESTMEDIA_LOG_H
#define TESTMEDIA_LOG_H
#include <string>
#include <mutex>

//日志
namespace Log {
    int d(const char* fmt, ...);
    int i(const char* fmt, ...);
    int w(const char* fmt, ...);
    int e(const char* fmt, ...);

    int log(int prio, const char* tag, const char* fmt, ...);
    int log(int prio, const char* tag, const char* fmt, va_list ap);
};


#endif //TESTMEDIA_LOG_H
