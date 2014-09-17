#include <Windows.h>

void* MyMallocAndInitializeCriticalSection()
{
	CRITICAL_SECTION *lpCriticalSection = malloc(sizeof(CRITICAL_SECTION));
	memset(lpCriticalSection, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(lpCriticalSection);
	return lpCriticalSection;
}

void MyFreeAndDeleteCriticalSection(void *lp)
{
	CRITICAL_SECTION *lpCriticalSection = (CRITICAL_SECTION*)(lp);
	DeleteCriticalSection(lpCriticalSection);
	free(lp);
}


void MyEnterCriticalSection(void *lp)
{
	CRITICAL_SECTION *lpCriticalSection = (CRITICAL_SECTION*)(lp);
	EnterCriticalSection(lpCriticalSection);
}

void MyLeaveCriticalSection(CRITICAL_SECTION *lp)
{
	CRITICAL_SECTION *lpCriticalSection = (CRITICAL_SECTION*)(lp);
	LeaveCriticalSection(lpCriticalSection);
}

