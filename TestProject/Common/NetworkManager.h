#pragma once
#include <Winsock2.h>
#include <string>
#include "NormalLock.h"
/************************************************************************/
/* �¼�ģ����������������һ��һͨ��                                         */
/************************************************************************/

//ͬ���ص�֪ͨ�ӿ�
interface INetworkCallback
{
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�NotifyConnect
	// ����������
	//			bConnect				[����]	�����Ƿ�ɹ�
	// �� �� ֵ��
	// ����˵����֪ͨ�����Ƿ�ɹ�
	// $_FUNCTION_END *********************************************************
	virtual void	NotifyConnect(BOOL bConnect) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�NotifyClose
	// ����������
	// �� �� ֵ��
	// ����˵����֪ͨ�ر�����
	// $_FUNCTION_END *********************************************************
	virtual void	NotifyClose() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�NotifyRead
	// ����������
	//			pBuf					[����]	���ݻ�����
	//			dwBufLen				[����]	���ݳ���
	// �� �� ֵ��
	// ����˵����֪ͨ�յ�������
	// $_FUNCTION_END *********************************************************
	virtual void	NotifyRead(const void *pBuf, DWORD dwBufLen) = 0;
};

class CNetworkManager
{
public:
	CNetworkManager(void);
	virtual ~CNetworkManager(void);
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Init
	// ����������
	//			pNetworkCallback		[����]	�¼�֪ͨ�ص�
	//			strAddress				[����]	��������ַ
	//			usPort					[����]	�������˿�
	// �� �� ֵ��TRUE or FALSE
	// ����˵������ʼ�����������ӷ�������ַ
	// $_FUNCTION_END *********************************************************
	virtual BOOL	Init(INetworkCallback *pNetworkCallback, const std::string &strAddress, USHORT usPort);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�StopSocket
	// ����������
	// �� �� ֵ��TRUE or FALSE
	// ����˵�����ر�socket���رռ������߳�
	// $_FUNCTION_END *********************************************************
	virtual BOOL	StopSocket();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Init
	// ����������
	// �� �� ֵ��TRUE or FALSE
	// ����˵���������첽���ӷ����������ӽ������ûص�����֪ͨ
	// $_FUNCTION_END *********************************************************
	virtual BOOL	Connect();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SendData
	// ����������
	//			pBuf					[����]	��������ַ
	//			dwBufLen				[����]	���ͳ���
	// �� �� ֵ��TRUE or FALSE
	// ����˵����ͬ����������
	// $_FUNCTION_END *********************************************************
	virtual BOOL	SendData(const void *pBuf, DWORD dwBufLen);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SocketThread
	// ����������
	//			pArgument				[����]	CNetworkManager��ָ��
	// �� �� ֵ��0
	// ����˵�������������¼��߳�
	// $_FUNCTION_END *********************************************************
	static unsigned int __stdcall SocketThread(void *pArgument);
protected:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�OnSockEvent
	// ����������
	//			wsaNetworkEvent			[����]	�����¼���Ϣ
	//			bContinue				[����]	�Ƿ�������������¼�
	// �� �� ֵ��
	// ����˵���������¼�������
	// $_FUNCTION_END *********************************************************
	virtual void	OnSockEvent(const WSANETWORKEVENTS &wsaNetworkEvent, BOOL &bContinue);
protected:
	//�����¼��ص��ӿ�
	INetworkCallback	*m_pNetworkCallback;
	//������IP��ַ
	std::string	m_strAddress;
	//�������˿�
	USHORT		m_usPort;
	//�����׽���
	SOCKET		m_socket;
	//�����¼�
	WSAEVENT	m_hSelectEvent;
	//��������ַ
	sockaddr_in	m_addr;
	//�����߳̾��
	HANDLE		m_hReceiveThread;
	//�˳������¼�
	HANDLE		m_hExitThreadEvent;
	//�������ݻ�����
	std::string	m_strNetworkRecvBuffer;
	//EventSelect���¼�
	DWORD		m_dwEventSelect;
	//�˳��ı��λ
	volatile BOOL	m_bExitFlag;
	//SendData����
	CNormalLock		m_NormalLock;
};

