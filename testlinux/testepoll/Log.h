#ifndef _LOG_H_
#define _LOG_H_
#include <syslog.h>
#include <errno.h>//error

extern int errno;

#if 0
#define LOG(level, ...)\
	syslog(level, __VA_ARGS__)
#else
#include <stdlib.h>
#define LOG(level, ...)\
	printf(__VA_ARGS__);\
	printf("\n")
#endif
#endif

