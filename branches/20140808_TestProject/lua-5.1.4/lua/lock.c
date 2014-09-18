#include <Windows.h>

CRITICAL_SECTION* MyMallocAndInitializeCriticalSection()
{
	CRITICAL_SECTION *lpCriticalSection = malloc(sizeof(CRITICAL_SECTION));
	memset(lpCriticalSection, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(lpCriticalSection);
	return lpCriticalSection;
}

void MyFreeAndDeleteCriticalSection(CRITICAL_SECTION *lpCriticalSection)
{
	DeleteCriticalSection(lpCriticalSection);
	free(lpCriticalSection);
}


void MyEnterCriticalSection(CRITICAL_SECTION *lpCriticalSection)
{
	EnterCriticalSection(lpCriticalSection);
}

void MyLeaveCriticalSection(CRITICAL_SECTION *lpCriticalSection)
{
	LeaveCriticalSection(lpCriticalSection);
}

