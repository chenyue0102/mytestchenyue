#include "stdafx.h"
#include "UIAccordion.h"

namespace DuiLib
{

CAccordionUI::CAccordionUI()
	: m_pHeader(NULL)
	, m_pBody(NULL)
	, m_bExpanded(false)
{
}

LPCTSTR CAccordionUI::GetClass() const
{
	return _T("AccordionUI");
}

LPVOID CAccordionUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("Accordion")) == 0 ) return static_cast<CAccordionUI*>(this);
	return __super::GetInterface(pstrName);
}

UINT CAccordionUI::GetControlFlags() const
{
	return __super::GetControlFlags();
}

void CAccordionUI::Set(CAccordionHeaderUI* pHeader, CContainerUI* pBody)
{
	if (pHeader != NULL)
	{
		m_pHeader = pHeader;
		m_pHeader->SetOwner(this);
		Add(m_pHeader);

		if (pBody != NULL)
		{
			m_pBody = pBody;
			m_pBody->SetVisible(m_bExpanded);
			Add(m_pBody);
		}
	}
}

CAccordionHeaderUI* CAccordionUI::GetHeader() const
{
	return m_pHeader;
}

CContainerUI* CAccordionUI::GetBody() const
{
	return m_pBody;
}

void CAccordionUI::Expand(bool bExpand)
{
	m_bExpanded = bExpand;
	if (m_pBody) 
	{
		m_pBody->SetVisible(m_bExpanded);
		Invalidate();
		
	}
}

void CAccordionUI::Action()
{
	Expand(!m_bExpanded);
}

//////////////////////////////////////////////////////////////////////////
CAccordionHeaderUI::CAccordionHeaderUI(CAccordionUI* pOwner)
: m_pOwner(pOwner)
, m_dwSelectedBkColor(0)
{

}

LPCTSTR CAccordionHeaderUI::GetClass() const
{
	return _T("AccordionHeaderUI");
}

LPVOID CAccordionHeaderUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("AccordionHeader")) == 0) return static_cast<CAccordionHeaderUI*>(this);
	return __super::GetInterface(pstrName);
}

void CAccordionHeaderUI::DoEvent(TEventUI& event)
{
	if (event.Type == UIEVENT_BUTTONUP)
	{
		if( ::PtInRect(&m_rcItem, event.ptMouse) && m_pOwner) m_pOwner->Action();
		if ((m_uButtonState & UISTATE_SELECTED) != 0)
		{
			m_uButtonState &= ~UISTATE_SELECTED;
		}
		else 
		{
			m_uButtonState |= UISTATE_SELECTED;
		}
		Invalidate();
	}

	__super::DoEvent(event);
}

void CAccordionHeaderUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("normalimage")) == 0) SetNormalImage(pstrValue);
	else if (_tcscmp(pstrName, _T("selectedimage")) == 0) SetSelectedImage(pstrValue);
	else if (_tcscmp(pstrName, _T("selectedbkcolor")) == 0) {
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD dwColor = _tcstoul(pstrValue, &pstr, 16);
		SetSelectedBkColor(dwColor);
	}
	else __super::SetAttribute(pstrName, pstrValue);
}

void CAccordionHeaderUI::PaintBkColor(HDC hDC)
{
	if ((m_uButtonState & UISTATE_SELECTED) != 0) {
		if (m_dwSelectedBkColor != 0) {
			if( m_dwSelectedBkColor >= 0xFF000000 ) CRenderEngine::DrawColor(hDC, m_rcPaint, GetAdjustColor(m_dwSelectedBkColor));
			else CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwSelectedBkColor));
		}
	}
	else {
		__super::PaintBkColor(hDC);
	}
}

void CAccordionHeaderUI::PaintStatusImage(HDC hDC)
{
	if( (m_uButtonState & UISTATE_SELECTED) != 0 ) {
		if( !m_sSelectedImage.IsEmpty() )
		{
			if( !DrawImage(hDC, (LPCTSTR)m_sSelectedImage, NULL, FRAME_TYPE_AccordionHeader_SelectedImage) ) m_sSelectedImage.Empty();
		}
	}
	else if (!m_sNormalImage.IsEmpty())
	{
		if (!DrawImage(hDC, (LPCTSTR)m_sNormalImage, NULL, FRAME_TYPE_AccordionHeader_NormalImage)) m_sNormalImage.Empty();
	}
}

LPCTSTR CAccordionHeaderUI::GetNormalImage()
{
	return m_sNormalImage;
}

void CAccordionHeaderUI::SetNormalImage(LPCTSTR pStrImage)
{
	m_sNormalImage = pStrImage;
	StopImagePlayTimerAndCleanFrameInfo(FRAME_TYPE_AccordionHeader_NormalImage);//如果定时器存在,停止这个图片的定时器
	Invalidate();
}

LPCTSTR CAccordionHeaderUI::GetSelectedImage()
{
	return m_sSelectedImage;
}

void CAccordionHeaderUI::SetSelectedImage(LPCTSTR pStrImage)
{
	m_sSelectedImage = pStrImage;
	StopImagePlayTimerAndCleanFrameInfo(FRAME_TYPE_AccordionHeader_SelectedImage);//如果定时器存在,停止这个图片的定时器
	Invalidate();
}

DWORD CAccordionHeaderUI::GetSelectedBkColor()
{
	return m_dwSelectedBkColor;
}

void CAccordionHeaderUI::SetSelectedBkColor(DWORD dwBkColor)
{
	m_dwSelectedBkColor = dwBkColor;
	Invalidate();
}

void CAccordionHeaderUI::SetOwner(CAccordionUI* pOwner)
{
	m_pOwner = pOwner;
}

}