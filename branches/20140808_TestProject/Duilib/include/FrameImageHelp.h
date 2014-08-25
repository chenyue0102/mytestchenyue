#pragma once
#include <vector>
#include <map>
#include <WTypes.h>
#include "TimeQueue.h"

namespace DuiLib{
class CControlUI;
class CFrameImageHelp : public ITimeCallback
{
public:
	CFrameImageHelp(void);
	~CFrameImageHelp(void);
public:
	BOOL	StartTimer(CControlUI *pControlUI, FRAME_TYPE FrameType, const TImageInfo *pImageInfo);
	BOOL	StopTimer(CControlUI *pControlUI, FRAME_TYPE FrameType);
	BOOL	StopAllTimer(CControlUI *pControlUI);
	BOOL	IsTimerExist(CControlUI *pControlUI, FRAME_TYPE FrameType)const;
public:
	virtual void OnTimer(ULONG ulUserData);
private:
	typedef std::vector<HANDLE> HANDLE_ARRAY;
	typedef struct _FRAME_INFO
	{
		TImageInfo	*pImageInfo;
		CControlUI	*pControlUI;
		HANDLE_ARRAY hTimers;
		FRAME_TYPE	FrameType;
	}FRAME_INFO;
	typedef std::map<FRAME_TYPE, FRAME_INFO>	FRAME_INFO_ARRAY;
	typedef std::map<CControlUI*, FRAME_INFO_ARRAY>	CONTROLUI_FRAME_INFO_ARRAY;

	CTimeQueue		m_TimeQueue;
	CONTROLUI_FRAME_INFO_ARRAY	m_ControlUIFrameHandle;
};
}
