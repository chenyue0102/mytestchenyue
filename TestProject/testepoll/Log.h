#ifndef _LOG_H_
#define _LOG_H_
#include <syslog.h>
#include <errno.h>//error

extern int errno;

#define LOG(level, fmt, ...)\
	syslog(level, fmt, __VA_ARGS__)
#endif

