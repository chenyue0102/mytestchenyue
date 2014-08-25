#include "stdafx.h"
#include ".\listelementui_wrapper.h"

CListElementUI_wrapper::CListElementUI_wrapper(void)
{
	printf("CListElementUI_wrapper\n");
}

CListElementUI_wrapper::~CListElementUI_wrapper(void)
{
	printf("~CListElementUI_wrapper\n");
}

void CListElementUI_wrapper::DrawItemText( HDC hDC, const RECT& rcItem )
{
	call<void>("DrawItemText", hDC, boost::ref(rcItem));
}

void CListElementUI_wrapper::default_DrawItemText( DuiLib::CListElementUI *ptr, HDC hDC, const RECT& rcItem )
{
	//return ptr->CListElementUI::DrawItemText(hDC, rcItem);
}
