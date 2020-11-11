//
// Created by chenyue on 2020/7/20.
//

#ifndef TESTMEDIA_LOG_H
#define TESTMEDIA_LOG_H

#include <stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif
//日志
int mylog_d(const char *fmt, ...);
int mylog_i(const char *fmt, ...);
int mylog_w(const char *fmt, ...);
int mylog_e(const char *fmt, ...);

int mylog(int prio, const char *tag, const char *fmt, ...);
int mylogv(int prio, const char *tag, const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif
#endif //TESTMEDIA_LOG_H
