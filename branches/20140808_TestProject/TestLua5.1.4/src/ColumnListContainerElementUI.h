#pragma once
#include <UIlib.h>


/*
����Ŀ�����Ʊ���ɫ�ͱ���ͼ
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