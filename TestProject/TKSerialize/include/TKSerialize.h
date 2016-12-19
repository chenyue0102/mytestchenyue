#pragma once
#include "TKSerializeExport.h"
#include "EnumSerialize.h"
#include "InterfaceSerialize.h"

namespace SerializeExport
{
TKSNSEXTENDUI_API ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat);

TKSNSEXTENDUI_API void DestroySerializeInterface(ISerialize *pInterface);
}
