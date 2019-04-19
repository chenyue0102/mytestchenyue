#ifndef _LOADEREXPORT_H_
#define _LOADEREXPORT_H_
#include "LoaderExportDefine.h"

struct ILoader;
extern "C"
{
LOADER_API ILoader* CreateLoader();
LOADER_API void DestroyLoader(ILoader *pLoader);
}

#endif