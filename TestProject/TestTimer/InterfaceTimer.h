#pragma once
#include <Unknwn.h>
#ifndef interface
#define interface struct
#endif

interface ITimerCallback : public IUnknown
{
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�OnTimer
	// ����������
	//			 dwUserData				[����]	�û���������ʱ����ʱ��������Ĳ���
	// �� �� ֵ��
	// ����˵������ʱ�����˵Ķ�ʱ�ص�����
	// $_FUNCTION_END *********************************************************
	virtual void STDMETHODCALLTYPE OnTimer(DWORD dwUserData) = 0;
};