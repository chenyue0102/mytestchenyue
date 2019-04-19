#include "LoaderExport.h"
#include "LoaderInstance.h"

LOADER_API ILoader * CreateLoader()
{
	return theApp.CreateLoader();
}

LOADER_API void DestroyLoader(ILoader * pLoader)
{
	return theApp.DestroyLoader(pLoader);
}
