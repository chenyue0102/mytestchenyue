#ifndef __UIACCORDION_H__
#define __UIACCORDION_H__

#pragma once

namespace DuiLib
{

class CAccordionHeaderUI;

class UILIB_API CAccordionUI : public CVerticalLayoutUI
{
public:
	CAccordionUI();

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	void Expand(bool bExpand);
	void Action();
	void Set(CAccordionHeaderUI* pHeader, CContainerUI* pBody);
	CAccordionHeaderUI* GetHeader() const;
	CContainerUI* GetBody() const;

protected:
	CAccordionHeaderUI*		m_pHeader;
	CContainerUI*			m_pBody;
	bool					m_bExpanded;
};

class UILIB_API CAccordionHeaderUI : public CHorizontalLayoutUI
{
public:
	CAccordionHeaderUI(CAccordionUI* pOwner = NULL);

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintBkColor(HDC hDC);
	void PaintStatusImage(HDC hDC);

	LPCTSTR GetNormalImage();
	void SetNormalImage(LPCTSTR pStrImage);
	LPCTSTR GetSelectedImage();
	void SetSelectedImage(LPCTSTR pStrImage);
	DWORD GetSelectedBkColor();
	void SetSelectedBkColor(DWORD dwBkColor);
	void SetOwner(CAccordionUI* pOwner);

protected:
	CAccordionUI*	m_pOwner;
	CStdString		m_sNormalImage;
	CStdString		m_sSelectedImage;
	DWORD			m_dwSelectedBkColor;
};

}

#endif