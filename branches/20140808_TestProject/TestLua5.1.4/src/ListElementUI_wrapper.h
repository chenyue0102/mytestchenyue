#pragma once
#include <UIlib.h>

class CListElementUI_wrapper
	: public DuiLib::CListElementUI
	, public luabind::wrap_base
{
public:
	CListElementUI_wrapper(void);
	virtual ~CListElementUI_wrapper(void);
public:
	virtual void DrawItemText(HDC hDC, const RECT& rcItem);

	static void default_DrawItemText(DuiLib::CListElementUI *ptr, HDC hDC, const RECT& rcItem);
};
