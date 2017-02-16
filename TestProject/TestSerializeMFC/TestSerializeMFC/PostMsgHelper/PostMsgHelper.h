#pragma once
#include "EnumSerialize.h"

namespace PostMsgHelper
{
template<typename ParamType>
inline bool PostNotifyMsg(unsigned long uMsgID, const ParamType &t, 
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface);

inline bool PostNotifyMsg(unsigned long uMsgID, void *pInterface);

template<typename InParamType, typename OutParamType>
inline bool SendQueryMsg(unsigned long uMsgID, const InParamType &in, OutParamType &out, unsigned long *pResult,
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface);

template<typename OutParamType>
inline bool SendQueryMsg(unsigned long uMsgID, OutParamType &out, unsigned long *pResult, 
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface);
}
#include "PostMsgHelper.inl"