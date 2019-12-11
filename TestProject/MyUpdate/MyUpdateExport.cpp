#include "MyUpdateExport.h"
#include <stdarg.h>
#include "MyUpdateInstance.h"


namespace MyUpdateExport
{
	int MYUPDATE_DLL createUpdate()
	{
		return g_instance.createUpdate();
	}
	void MYUPDATE_DLL setUpdateParam(int ctx, int type, ...)
	{
		va_list argp;
		va_start(argp, type);
		g_instance.setUpdateParam(ctx, type, argp);
		va_end(argp);
	}
	void MYUPDATE_DLL startUpdate(int ctx)
	{
		return g_instance.startUpdate(ctx);
	}
	void MYUPDATE_DLL cancelUpdate(int ctx)
	{
		return g_instance.cancelUpdate(ctx);
	}
	void MYUPDATE_DLL destroyUpdate(int ctx)
	{
		return g_instance.destroyUpdate(ctx);
	}
}
