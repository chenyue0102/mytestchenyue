#pragma once


struct AnimationInfo;
namespace AnimationLoader
{
bool parseJson(const char *pData, int length, AnimationInfo &info);
};

