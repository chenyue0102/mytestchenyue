#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <memory>
#include <atlcomcli.h>
#include "UnknownImp.h"
#include "IOCPBuffer.h"

#define READ_BUFFER_LEN	(1024 * 8)

enum EnumWriteStep
{
	EnumWriteStepNone,
	EnumWriteStepPost,
	EnumWriteStepProcessing,
};
enum EnumIOType
{
	EnumIOTypeNone,
	EnumIOTypeAccept,
	EnumIOTypeRead,
	EnumIOTypeWrite,
	EnumIOTypeWriteComplete,
};
#define DISABLE_COPY(classname)\
	classname(const classname&)=delete;\
	classname& operator=(const classname &)=delete;


struct IOContext
{
	DISABLE_COPY(IOContext);
	IOContext()
		: conSocket(INVALID_SOCKET)
		, overlapped()
		, IOType(EnumIOTypeNone)
	{
		TRACE(L"IOContext\n");
	}
	~IOContext()
	{
		TRACE(L"~IOContext\n");
	}
	volatile SOCKET		conSocket; // The Connection socket. 
	OVERLAPPED	overlapped;
	volatile EnumIOType	IOType;
};


struct IOReadContext : IOContext
{
	DISABLE_COPY(IOReadContext);
	IOReadContext()
		: IOContext()
		, Buffer(READ_BUFFER_LEN, '\0')
	{
		IOType = EnumIOTypeRead;
		TRACE(L"IOReadContext\n");
	}
	~IOReadContext()
	{
		TRACE(L"~IOReadContext\n");
	}
	std::string Buffer;
};

struct IOWriteContext : IOContext
{
	DISABLE_COPY(IOWriteContext);
	IOWriteContext()
		: IOContext()
		, Buffer()
		, bHaveWSASend(false)
	{
		IOType = EnumIOTypeWrite;
		TRACE(L"IOWriteContext\n");
	}
	~IOWriteContext()
	{
		
		TRACE(L"~IOWriteContext\n");
	}
	std::string Buffer;
	volatile bool bHaveWSASend;
};

struct SocketContext
{
	DISABLE_COPY(SocketContext);
	SocketContext()
		: overlapped()
		, conSocket(INVALID_SOCKET)
		, ullKey(0)
		, ClientAddr()
		, ReadContext()
		, WriteContext()
		, cs()
		, WriteStep(EnumWriteStepNone)
		, WriteContextArray()
		, WriteCompleteContextArray()
	{
		WriteContext.IOType = EnumIOTypeWrite;
		InitializeCriticalSection(&cs);
		TRACE(L"SocketContext\n");
	}
	~SocketContext()
	{
		DeleteCriticalSection(&cs);
		assert(INVALID_SOCKET == conSocket);
		assert(0 == WriteContextArray.size());
		TRACE(L"~SocketContext\n");
	}

	OVERLAPPED	overlapped;
	volatile SOCKET		conSocket;	// The Connection socket. 
	unsigned long long	ullKey;
	SOCKADDR_IN ClientAddr;								// 客户端的地址
	IOReadContext ReadContext;
	IOWriteContext WriteContext;

	CRITICAL_SECTION cs;
	volatile EnumWriteStep WriteStep;
	std::vector<std::shared_ptr<IOWriteContext>> WriteContextArray;
	std::vector<std::shared_ptr<IOWriteContext>> WriteCompleteContextArray;
};

