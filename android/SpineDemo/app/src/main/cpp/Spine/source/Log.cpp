//
// Created by EDZ on 2020/7/20.
//

#include "Log.h"
#ifdef _WIN32
#include <stdlib.h>
#include <stdarg.h>
enum {
	/** For internal use only.  */
	LOG_UNKNOWN = 0,
	/** The default priority, for internal use only.  */
	LOG_DEFAULT, /* only for SetMinPriority() */
	/** Verbose logging. Should typically be disabled for a release apk. */
	LOG_VERBOSE,
	/** Debug logging. Should typically be disabled for a release apk. */
	LOG_DEBUG,
	/** Informational logging. Should typically be disabled for a release apk. */
	LOG_INFO,
	/** Warning logging. For use with recoverable failures. */
	LOG_WARN,
	/** Error logging. For use with unrecoverable failures. */
	LOG_ERROR,
	/** Fatal logging. For use when aborting. */
	LOG_FATAL,
	/** For internal use only.  */
	LOG_SILENT, /* only for SetMinPriority(); must be last */
};
#else
extern "C"{
#include <android/log.h>
#define LOG_LOG_UNKNOWN ANDROID_LOG_UNKNOWN
#define LOG_DEFAULT ANDROID_LOG_DEFAULT
#define LOG_VERBOSE ANDROID_LOG_VERBOSE
#define LOG_DEBUG ANDROID_LOG_DEBUG
#define LOG_INFO ANDROID_LOG_INFO
#define LOG_WARN ANDROID_LOG_WARN
#define LOG_ERROR ANDROID_LOG_ERROR
#define LOG_FATAL ANDROID_LOG_FATAL
#define LOG_SILENT ANDROID_LOG_SILENT
}
#endif

#define TAG "spinewrap"

#define LOG_FUN(prio) \
    va_list ap; \
    va_start(ap, fmt); \
    int ret = innerlog(prio, TAG, fmt, ap); \
    va_end(ap); \
    return ret

namespace Log{

#ifdef _WIN32
int innerlog(int prio, const char *tag, const char *fmt, va_list ap) {
	int ret = printf("%d %s ", prio, tag);
	ret += vprintf(fmt, ap);
	ret += printf("\n");
	return ret;
}
#else
int innerlog(int prio, const char *tag, const char *fmt, va_list ap) {
    return __android_log_vprint(prio, tag, fmt, ap);
}
#endif

int d(const char* fmt, ...) {
    LOG_FUN(LOG_DEBUG);
}

int i(const char* fmt, ...) {
    LOG_FUN(LOG_INFO);
}

int w(const char* fmt, ...) {
    LOG_FUN(LOG_WARN);
}

int e(const char *fmt, ...) {
    LOG_FUN(LOG_ERROR);
}

int log(int prio, const char *tag, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = innerlog(LOG_DEBUG, tag, fmt, ap);
    va_end(ap);
    return ret;
}

int log(int prio, const char *tag, const char *fmt, va_list ap){
    return innerlog(prio, tag, fmt, ap);
}

}