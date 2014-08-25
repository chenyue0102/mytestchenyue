#include "StdAfx.h"
#include ".\frameimagehelp.h"

namespace DuiLib{
CFrameImageHelp::CFrameImageHelp(void)
{
}

CFrameImageHelp::~CFrameImageHelp(void)
{
}

BOOL	CFrameImageHelp::StartTimer(CControlUI *pControlUI, FRAME_TYPE FrameType, const TImageInfo *pImageInfo)
{
	DWORD dwAllFrameMilliSecond = 0;
	for (IMAGE_FRAME_INFO_ARRAY::const_iterator itorImageFrame = pImageInfo->FrameInfo.begin();
		itorImageFrame != pImageInfo->FrameInfo.end();
		++itorImageFrame)
	{
		const IMAGE_FRAME_INFO &ImageFrameInfo = *itorImageFrame;
		dwAllFrameMilliSecond += ImageFrameInfo.dwTime;
	}
	FRAME_INFO_ARRAY &FrameHandleArray = m_ControlUIFrameHandle[pControlUI];
	FRAME_INFO &FrameInfo = FrameHandleArray[FrameType];
	FrameInfo.pControlUI = pControlUI;
	FrameInfo.pImageInfo = const_cast<TImageInfo*>(pImageInfo);
	FrameInfo.FrameType = FrameType;

	DWORD dwCurFrame = 0;
	ImagePlayStateInfo &ImageFrameInfo = pControlUI->GetFrameInfo(FrameType);
	dwCurFrame = ImageFrameInfo.dwCurFrame;

	DWORD dwDueTime = 0;
	for (UINT nIndex = dwCurFrame; nIndex < pImageInfo->FrameInfo.size(); nIndex++)
	{
		dwDueTime += pImageInfo->FrameInfo[nIndex].dwTime;
		HANDLE hTimer = m_TimeQueue.CreateTimer(dwDueTime, dwAllFrameMilliSecond, static_cast<ITimeCallback*>(this), reinterpret_cast<DWORD>(&FrameInfo));
		if (NULL == hTimer)
		{
			ASSERT(FALSE);
			continue;
		}
		FrameInfo.hTimers.push_back(hTimer);
	}
	for (UINT nIndex = 0; nIndex < dwCurFrame; nIndex++)
	{
		dwDueTime += pImageInfo->FrameInfo[nIndex].dwTime;
		HANDLE hTimer = m_TimeQueue.CreateTimer(dwDueTime, dwAllFrameMilliSecond, static_cast<ITimeCallback*>(this), reinterpret_cast<DWORD>(&FrameInfo));
		if (NULL == hTimer)
		{
			ASSERT(FALSE);
			continue;
		}
		FrameInfo.hTimers.push_back(hTimer);
	}

	return TRUE;
}

BOOL	CFrameImageHelp::StopTimer(CControlUI *pControlUI, FRAME_TYPE FrameType)
{
	CONTROLUI_FRAME_INFO_ARRAY::iterator itorControl = m_ControlUIFrameHandle.find(pControlUI);
	if (itorControl != m_ControlUIFrameHandle.end())
	{
		FRAME_INFO_ARRAY &FrameHandleArray = itorControl->second;
		FRAME_INFO_ARRAY::iterator itorFrame = FrameHandleArray.find(FrameType);
		if (itorFrame != FrameHandleArray.end())
		{
			for (HANDLE_ARRAY::const_iterator itorHandle = itorFrame->second.hTimers.begin();
				itorHandle != itorFrame->second.hTimers.end();
				++itorHandle)
			{
				BOOL b = m_TimeQueue.RemoveTimer(*itorHandle);
				
				ASSERT(b);
			}
			FrameHandleArray.erase(itorFrame);
		}
		if (0 == FrameHandleArray.size())
		{
			m_ControlUIFrameHandle.erase(itorControl);
		}
	}
	return TRUE;
}

BOOL	CFrameImageHelp::StopAllTimer(CControlUI *pControlUI)
{
	CONTROLUI_FRAME_INFO_ARRAY::iterator itorControl = m_ControlUIFrameHandle.find(pControlUI);
	if (itorControl != m_ControlUIFrameHandle.end())
	{
		FRAME_INFO_ARRAY &FrameHandleArray = itorControl->second;
		for (FRAME_INFO_ARRAY::iterator itorFrame = FrameHandleArray.begin();
				itorFrame != FrameHandleArray.end();
				++itorFrame)
		{
			for(HANDLE_ARRAY::const_iterator itorHandle = itorFrame->second.hTimers.begin();
				itorHandle != itorFrame->second.hTimers.end();
				++itorHandle)
			{
				BOOL b = m_TimeQueue.RemoveTimer(*itorHandle);
				ASSERT(b);
			}
		}
		m_ControlUIFrameHandle.erase(itorControl);
	}
	return TRUE;
}

void CFrameImageHelp::OnTimer(ULONG ulUserData)
{
	try
	{
		FRAME_INFO *pFrameInfo = reinterpret_cast<FRAME_INFO *>(ulUserData);
		if (IsBadWritePtr(pFrameInfo, sizeof(FRAME_INFO)))
		{
			return;
		}
		//通过查map表，检测这个指针的有效性
		CONTROLUI_FRAME_INFO_ARRAY::const_iterator itorControl = m_ControlUIFrameHandle.find(pFrameInfo->pControlUI);
		if (itorControl == m_ControlUIFrameHandle.end())
		{
			return;
		}
		FRAME_INFO_ARRAY::const_iterator itorFrame = itorControl->second.find(pFrameInfo->FrameType);
		if (itorFrame == itorControl->second.end())
		{
			return;
		}
		//如果这个控件不可见，或者在窗口外，则停止定时器
		BOOL bVisible = FALSE;
		if (pFrameInfo->pControlUI->IsVisible())
		{
			RECT rcPos = pFrameInfo->pControlUI->GetPos();
			::RECT rcClient;
			GetClientRect(pFrameInfo->pControlUI->GetManager()->GetPaintWindow(), &rcClient);
			if (!(rcPos.left > rcClient.right || rcPos.right < rcClient.left || rcPos.top > rcClient.bottom || rcPos.bottom < rcClient.top))
			{
				bVisible = TRUE;
			}
		}
		if (!bVisible)
		{
			StopTimer(pFrameInfo->pControlUI, pFrameInfo->FrameType);
		}
		else
		{
			ImagePlayStateInfo &ImageFrameInfo = pFrameInfo->pControlUI->GetFrameInfo(pFrameInfo->FrameType);
			ImageFrameInfo.dwCurFrame++;
			if (ImageFrameInfo.dwCurFrame >= pFrameInfo->pImageInfo->FrameInfo.size())
			{
				ImageFrameInfo.dwCurFrame = 0;
			}
			pFrameInfo->pControlUI->Invalidate();
		}
	}
	catch (...)
	{
		ASSERT(FALSE);
	}
}

BOOL	CFrameImageHelp::IsTimerExist(CControlUI *pControlUI, FRAME_TYPE FrameType)const
{
	CONTROLUI_FRAME_INFO_ARRAY::const_iterator itorControl = m_ControlUIFrameHandle.find(pControlUI);
	if (itorControl == m_ControlUIFrameHandle.end())
	{
		return FALSE;
	}
	else
	{
		const FRAME_INFO_ARRAY &FrameHanleArray = itorControl->second;
		FRAME_INFO_ARRAY::const_iterator itorFrame = FrameHanleArray.find(FrameType);
		if (itorFrame == FrameHanleArray.end())
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}
}