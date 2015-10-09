#pragma once
#include <Winsock2.h>
#include <string>
#include "NormalLock.h"
/************************************************************************/
/* 事件模型网络连接适用于一对一通信                                         */
/************************************************************************/

//同步回掉通知接口
interface INetworkCallback
{
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：NotifyConnect
	// 函数参数：
	//			bConnect				[输入]	连接是否成功
	// 返 回 值：
	// 函数说明：通知连接是否成功
	// $_FUNCTION_END *********************************************************
	virtual void	NotifyConnect(BOOL bConnect) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：NotifyClose
	// 函数参数：
	// 返 回 值：
	// 函数说明：通知关闭连接
	// $_FUNCTION_END *********************************************************
	virtual void	NotifyClose() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：NotifyRead
	// 函数参数：
	//			pBuf					[输入]	数据缓冲区
	//			dwBufLen				[输入]	数据长度
	// 返 回 值：
	// 函数说明：通知收到了数据
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
	// 函数名称：Init
	// 函数参数：
	//			pNetworkCallback		[输入]	事件通知回掉
	//			strAddress				[输入]	服务器地址
	//			usPort					[输入]	服务器端口
	// 返 回 值：TRUE or FALSE
	// 函数说明：初始化并设置连接服务器地址
	// $_FUNCTION_END *********************************************************
	virtual BOOL	Init(INetworkCallback *pNetworkCallback, const std::string &strAddress, USHORT usPort);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：StopSocket
	// 函数参数：
	// 返 回 值：TRUE or FALSE
	// 函数说明：关闭socket并关闭监听的线程
	// $_FUNCTION_END *********************************************************
	virtual BOOL	StopSocket();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Init
	// 函数参数：
	// 返 回 值：TRUE or FALSE
	// 函数说明：发起异步连接服务器，连接结果会调用回掉函数通知
	// $_FUNCTION_END *********************************************************
	virtual BOOL	Connect();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SendData
	// 函数参数：
	//			pBuf					[输入]	缓冲区地址
	//			dwBufLen				[输入]	发送长度
	// 返 回 值：TRUE or FALSE
	// 函数说明：同步发送数据
	// $_FUNCTION_END *********************************************************
	virtual BOOL	SendData(const void *pBuf, DWORD dwBufLen);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SocketThread
	// 函数参数：
	//			pArgument				[输入]	CNetworkManager类指针
	// 返 回 值：0
	// 函数说明：监听网络事件线程
	// $_FUNCTION_END *********************************************************
	static unsigned int __stdcall SocketThread(void *pArgument);
protected:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：OnSockEvent
	// 函数参数：
	//			wsaNetworkEvent			[输入]	网络事件信息
	//			bContinue				[输入]	是否继续监听网络事件
	// 返 回 值：
	// 函数说明：网络事件处理函数
	// $_FUNCTION_END *********************************************************
	virtual void	OnSockEvent(const WSANETWORKEVENTS &wsaNetworkEvent, BOOL &bContinue);
protected:
	//网络事件回调接口
	INetworkCallback	*m_pNetworkCallback;
	//服务器IP地址
	std::string	m_strAddress;
	//服务器端口
	USHORT		m_usPort;
	//连接套接字
	SOCKET		m_socket;
	//网络事件
	WSAEVENT	m_hSelectEvent;
	//服务器地址
	sockaddr_in	m_addr;
	//监听线程句柄
	HANDLE		m_hReceiveThread;
	//退出监听事件
	HANDLE		m_hExitThreadEvent;
	//接收数据缓冲区
	std::string	m_strNetworkRecvBuffer;
	//EventSelect的事件
	DWORD		m_dwEventSelect;
	//退出的标记位
	volatile BOOL	m_bExitFlag;
	//SendData的锁
	CNormalLock		m_NormalLock;
};

