#pragma once
#include "MyUpdateExportDefine.h"
namespace MyUpdateExport
{
int MYUPDATE_DLL createUpdate();
void MYUPDATE_DLL setUpdateParam(int ctx, int type, ...);
void MYUPDATE_DLL startUpdate(int ctx);
void MYUPDATE_DLL cancelUpdate(int ctx);
void MYUPDATE_DLL destroyUpdate(int ctx);
};
