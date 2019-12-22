#ifndef _TESTLINUXEXPORT_H_
#define _TESTLINUXEXPORT_H_

#ifdef _WIN32
	#ifdef BUILDING_DLL
		#define TEST_LINUX_EXPORT __attribute__((dllexport))
	#else
		#define TEST_LINUX_EXPORT __attribute__((dllimport))
	#endif
#else
	#ifdef BUILDING_DLL
		#define TEST_LINUX_EXPORT __attribute__ ((visibility("default")))
	#else
		#define TEST_LINUX_EXPORT
	#endif
#endif


#endif