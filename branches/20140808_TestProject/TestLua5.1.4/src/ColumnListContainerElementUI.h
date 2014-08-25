#pragma once
#include <UIlib.h>


/*
此条目不绘制背景色和背景图
*/
namespace DuiLib{
class CColumnListContainerElementUI
	: public CListContainerElementUI
{
public:
	CColumnListContainerElementUI(void);
	~CColumnListContainerElementUI(void);
public:
	 virtual void DoPaint(HDC hDC, const RECT& rcPaint);
};
}