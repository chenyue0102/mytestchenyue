//
// Created by EDZ on 2020/7/20.
//

#include "Log.h"

#ifdef __ANDROID__
extern "C"{
#include <android/log.h>
#define MYLOG_UNKNOWN ANDROID_LOG_UNKNOWN
#define MYLOG_DEFAULT ANDROID_LOG_DEFAULT
#define MYLOG_VERBOSE ANDROID_LOG_VERBOSE
#define MYLOG_DEBUG ANDROID_LOG_DEBUG
#define MYLOG_INFO ANDROID_LOG_INFO
#define MYLOG_WARN ANDROID_LOG_WARN
#define MYLOG_ERROR ANDROID_LOG_ERROR
#define MYLOG_FATAL ANDROID_LOG_FATAL
#define MYLOG_SILENT ANDROID_LOG_SILENT
}
#elif defined __APPLE__
#include <syslog.h>
#define MYLOG_DEBUG LOG_DEBUG
#define MYLOG_INFO LOG_INFO
#define MYLOG_WARN LOG_WARNING
#define MYLOG_ERROR LOG_ERR
#else
#include <stdlib.h>
#include <stdarg.h>
enum {
    /** For internal use only.  */
    MYLOG_UNKNOWN = 0,
    /** The default priority, for internal use only.  */
    MYLOG_DEFAULT, /* only for SetMinPriority() */
    /** Verbose logging. Should typically be disabled for a release apk. */
    MYLOG_VERBOSE,
    /** Debug logging. Should typically be disabled for a release apk. */
    MYLOG_DEBUG,
    /** Informational logging. Should typically be disabled for a release apk. */
    MYLOG_INFO,
    /** Warning logging. For use with recoverable failures. */
    MYLOG_WARN,
    /** Error logging. For use with unrecoverable failures. */
    MYLOG_ERROR,
    /** Fatal logging. For use when aborting. */
    MYLOG_FATAL,
    /** For internal use only.  */
    MYLOG_SILENT, /* only for SetMinPriority(); must be last */
};
#endif

#define TAG "spine"

#define LOG_FUN(prio) \
    va_list ap; \
    va_start(ap, fmt); \
    int ret = innerlog(prio, TAG, fmt, ap); \
    va_end(ap); \
    return ret

namespace Log{

#ifdef __ANDROID__
int innerlog(int prio, const char *tag, const char *fmt, va_list ap) {
    return __android_log_vprint(prio, tag, fmt, ap);
}
#elif defined __APPLE__
int innerlog(int prio, const char *tag, const char *fmt, va_list ap) {
    vsyslog(prio, fmt, ap);
    return 0;
}
#else
int innerlog(int prio, const char *tag, const char *fmt, va_list ap) {
    int ret = printf("%d %s ", prio, tag);
    ret += vprintf(fmt, ap);
    ret += printf("\n");
    return ret;
}
#endif

int d(const char* fmt, ...) {
    LOG_FUN(MYLOG_DEBUG);
}

int i(const char* fmt, ...) {
    LOG_FUN(MYLOG_INFO);
}

int w(const char* fmt, ...) {
    LOG_FUN(MYLOG_WARN);
}

int e(const char *fmt, ...) {
    LOG_FUN(MYLOG_ERROR);
}

int log(int prio, const char *tag, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = innerlog(MYLOG_DEBUG, tag, fmt, ap);
    va_end(ap);
    return ret;
}

int log(int prio, const char *tag, const char *fmt, va_list ap){
    return innerlog(prio, tag, fmt, ap);
}

}
