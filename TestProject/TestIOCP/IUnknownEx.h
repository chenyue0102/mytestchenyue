#pragma once
#include <wtypes.h>

//
struct IUnknownEx
{
	virtual ULONG PASCAL AddRef(void) = 0;

	virtual ULONG PASCAL Release(void) = 0;
};
