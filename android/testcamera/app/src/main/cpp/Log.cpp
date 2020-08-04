//
// Created by EDZ on 2020/7/20.
//

#include "Log.h"
extern "C"{
#include <android/log.h>
}

#define LOG_FUN(prio) \
    va_list ap; \
    va_start(ap, fmt); \
    int ret = log(ANDROID_LOG_DEBUG, mTag.c_str(), fmt, ap); \
    va_end(ap); \
    return ret

Log::Log(): mTag("Log") {

}

Log::~Log() {

}

void Log::setTag(const char *tag) {
    if (nullptr != tag){
        mTag = tag;
    }
}

const char *Log::getTag() {
    return mTag.c_str();
}

int Log::d(const char* fmt, ...) {
    LOG_FUN(ANDROID_LOG_DEBUG);
}

int Log::i(const char* fmt, ...) {
    LOG_FUN(ANDROID_LOG_INFO);
}

int Log::w(const char* fmt, ...) {
    LOG_FUN(ANDROID_LOG_WARN);
}

int Log::e(const char *fmt, ...) {
    LOG_FUN(ANDROID_LOG_ERROR);
}

int Log::log(int prio, const char *tag, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = log(ANDROID_LOG_DEBUG, tag, fmt, ap);
    va_end(ap);
    return ret;
}

int Log::log(int prio, const char *tag, const char *fmt, va_list ap) {
    return __android_log_vprint(prio, tag, fmt, ap);
}

