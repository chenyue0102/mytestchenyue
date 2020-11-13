#include "my_mutex.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

#ifdef _WIN32
typedef struct _my_mutex_t {
	CRITICAL_SECTION cs;
}my_mutex_t;

my_mutex_t*  create_my_mutex() {
	my_mutex_t *mtx = malloc(sizeof(my_mutex_t));
	InitializeCriticalSection(&mtx->cs);
}

void lock_my_mutex(my_mutex_t* mtx) {
	EnterCriticalSection(&mtx->cs);
}

void unlock_my_mutex(my_mutex_t* mtx) {
	LeaveCriticalSection(&mtx->cs);
}

void destroy_my_mutex(my_mutex_t* mtx) {
	if (NULL != mtx) {
		DeleteCriticalSection(&mtx->cs);
		free(mtx);
	}
}
#else

#endif