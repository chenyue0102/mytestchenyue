#pragma once
namespace MyUpdateExport
{
enum EParam
{
	EParamNone,
	EParamModule,		//char*
	EParamURL,			//char*
	EParamExtractPath,	//char*
	EParamCachePath,	//char*
	EParamConfigPath,	//char*
	EParamUserData,		//void*
	EParamNotifyPercent,//NOTIFYPERCENT
	EParamNotifyResult,	//NOTIFYRESULT
};
enum EAction
{
	EActionNone,
	EActionRestart,
};
enum EResult
{
	EResultOK,
	EResultFailed,
	EResultDownloadFailed,
	EResultMd5Failed,
};
//typedef void(*NOTIFYSTEP)(int step, void *userdata);
typedef void(*NOTIFYPERCENT)(long long now, long long total, void *userdata);
typedef void(*NOTIFYRESULT)(int result, int action, void *userdata);
}
