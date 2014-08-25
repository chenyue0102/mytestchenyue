#include "StdAfx.h"
#include "TestLuaClass.h"
#include "boost/shared_ptr.hpp"
#include <luabind/out_value_policy.hpp>
#include <luabind/operator.hpp>
#include <luabind/discard_result_policy.hpp>
#include <luabind/dependency_policy.hpp>
#include "LuaSerialize.h"

void InitTestNode()
{
	std::map<int,int> test;
	test.insert(std::make_pair(1,1));
}

std::string GetString()
{
	static char s[1024] = {'a','b','c','\0','d','e'};
	std::string str;
	str.append(s, 6);
	return str;
}

void RegisterTestLuaClass( lua_State *luaVM )
{
	luabind::module(luaVM)
	[
		class_<CLuaSerialize>("CLuaSerialize").
		def(constructor<>()).
		def("SetBuffer", &CLuaSerialize::SetBuffer).
		def("ToBuffer", &CLuaSerialize::ToBuffer, pure_out_value(_2)).
		def("ReadDWORD", &CLuaSerialize::ReadDWORD, pure_out_value(_2)).
		def("WriteDWORD", &CLuaSerialize::WriteDWORD).
		def("ReadWORD", &CLuaSerialize::ReadWORD, pure_out_value(_2)).
		def("WriteWORD", &CLuaSerialize::WriteWORD).
		def("ReadString", &CLuaSerialize::ReadString, pure_out_value(_2)).
		def("WriteString", &CLuaSerialize::WriteString)
	];
	luabind::module(luaVM)
	[
		class_<CTestNode>("CTestNode").
		def(constructor<>()).
		def(constructor<const CTestNode&>()).
		def("GetIndex", &CTestNode::GetIndex).
		def("SetIndex", &CTestNode::SetIndex).
		scope
		[
			def("GetCount", &CTestNode::GetCount)
		]
	];

	luabind::module(luaVM)
	[
		class_<CTestNodeManager>("CTestNodeManager").
		def(constructor<>()).
		def("InitNode", &CTestNodeManager::InitNode).
		def("GetNode", &CTestNodeManager::GetNode, dependency(result, _1)).			//dependency使得GetNode的返回值还有引用的情况下，不销毁Node所在的CTestNodeManager
		def("GetRefNode", &CTestNodeManager::GetRefNode, dependency(result, _1)). //dependency使得GetNode的返回值还有引用的情况下，不销毁Node所在的CTestNodeManager
		def("IsNodeExist", &CTestNodeManager::IsNodeExist).
		def("GetNodeValue", &CTestNodeManager::GetNodeValue).
		def("GetRefNodeValue", &CTestNodeManager::GetRefNodeValue)
	];

	luabind::module(luaVM)
	[
		class_<CTestContainer, CTestContainer_wrapper, boost::shared_ptr<CTestContainer> >("CTestContainer").
		def(constructor<>()).
		def("GetNodeManager", &CTestContainer::GetNodeManager, dependency(result, _1))			//dependency使得GetNode的返回值还有引用的情况下，不销毁Node所在的CTestNodeManager
	];

	module(luaVM)
	[
		def("InitTestNode", &InitTestNode),
		def("GetString", &GetString),
		def("TestSerializeIn", &TestSerializeIn)
		
	];
	luabind::module(luaVM)
	[
		luabind::def("ToBuffer", &ToBuffer)
	];

	luabind::module(luaVM)
	[
		class_<CSerialization>("CSerialization").
		def(constructor<>()).
		def(constructor<std::string&>()).
		def("SetSerializationType", &CSerialization::SetSerializationType).
		def("ToBuffer", &CSerialization::ToBuffer)
	];

	luabind::module(luaVM)
	[
		class_<TKSnsClientTLV>("TKSnsClientTLV").
		def(constructor<>()).
		def(constructor<const TKSnsClientTLV&>()).
		def("SetDword", &TKSnsClientTLV::SetDword).
		def("SetString", &TKSnsClientTLV::SetString).
		def("Serialization", &TKSnsClientTLV::Serialization).
		def("ToDword", &TKSnsClientTLV::ToDword, pure_out_value(_2)).
		def("ToString", &TKSnsClientTLV::ToString, pure_out_value(_2)).
		def_readonly("dwID", &TKSnsClientTLV::dwID).
		def_readonly("dwType", &TKSnsClientTLV::dwType)
	];

	luabind::module(luaVM)
	[
		class_<TKSnsClientSnsIndex>("TKSnsClientSnsIndex").
		def(constructor<>()).
		def(constructor<const TKSnsClientSnsIndex&>()).
		def("Serialization", &TKSnsClientSnsIndex::Serialization).
		def_readwrite("wSnsCID", &TKSnsClientSnsIndex::wSnsCID).
		def_readwrite("wSnsTID", &TKSnsClientSnsIndex::wSnsTID).
		def_readwrite("dwPID", &TKSnsClientSnsIndex::dwPID)
	];

	luabind::module(luaVM)
	[
		class_<TKSnsClientSnsTimeStamp>("TKSnsClientSnsTimeStamp").
		def(constructor<>()).
		def(constructor<const TKSnsClientSnsTimeStamp&>()).
		def("Serialization", &TKSnsClientSnsTimeStamp::Serialization).
		def_readwrite("stSnsClientSnsIndex", &TKSnsClientSnsTimeStamp::stSnsClientSnsIndex).
		def_readwrite("dwTimeStamp", &TKSnsClientSnsTimeStamp::dwTimeStamp)
	];

	luabind::module(luaVM)
	[
		class_<TKSnsClientHeader>("TKSnsClientHeader").
		def(constructor<>()).
		def(constructor<const TKSnsClientHeader&>()).
		def("Serialization", &TKSnsClientHeader::Serialization).
		def_readwrite("dwMessageID", &TKSnsClientHeader::dwMessageID).
		def_readwrite("dwMessageType", &TKSnsClientHeader::dwMessageType).
		def_readwrite("dwProtocolVersion", &TKSnsClientHeader::dwProtocolVersion).
		def_readwrite("bSuccess", &TKSnsClientHeader::bSuccess).
		def_readwrite("dwErrorCode", &TKSnsClientHeader::dwErrorCode)
	];

	luabind::module(luaVM)
	[
		class_<TKSnsClientGetSnsTimeStampListFromServer>("TKSnsClientGetSnsTimeStampListFromServer").
		def(constructor<>()).
		def("Serialization", &TKSnsClientGetSnsTimeStampListFromServer::Serialization).
		def_readwrite("stSnsClientHeader", &TKSnsClientGetSnsTimeStampListFromServer::stSnsClientHeader).
		def_readwrite("dwUserID", &TKSnsClientGetSnsTimeStampListFromServer::dwUserID).
		def_readwrite("wSnsCID", &TKSnsClientGetSnsTimeStampListFromServer::wSnsCID).
		def_readwrite("dwSnsTypeCount", &TKSnsClientGetSnsTimeStampListFromServer::dwSnsTypeCount).
		def_readwrite("SnsTypeArray", &TKSnsClientGetSnsTimeStampListFromServer::SnsTypeArray).
		def_readwrite("dwSnsTimeStampCount", &TKSnsClientGetSnsTimeStampListFromServer::dwSnsTimeStampCount).
		def_readwrite("SnsClientSnsTimeStampArray", &TKSnsClientGetSnsTimeStampListFromServer::SnsClientSnsTimeStampArray)
	];

	REGISTER_VECTOR_ITERATOR(WORD, luaVM);
	REGISTER_VECTOR_CLASS(WORD, luaVM);

	REGISTER_VECTOR_ITERATOR(TKSnsClientSnsTimeStamp, luaVM);
	REGISTER_VECTOR_CLASS(TKSnsClientSnsTimeStamp, luaVM);
	
	REGISTER_VECTOR_ITERATOR(TKSnsClientTLV, luaVM);
	REGISTER_VECTOR_CLASS(TKSnsClientTLV, luaVM);
	
	luabind::module(luaVM)
	[
		class_<TKSnsClientSnsProperty>("TKSnsClientSnsProperty").
		def(constructor<>()).
		def("Serialization", &TKSnsClientTLV::Serialization)
	];
		
	luabind::module(luaVM,"std")
	[
		class_<std::string>("string").
		def(constructor<>())
	];

	typedef std::string STRING;
	REGISTER_MAP_ITERATOR(DWORD, STRING, luaVM);
	REGISTER_MAP_CLASS(DWORD,STRING,luaVM);
}

void TestSerializeIn( std::string &strBuffer )
{
	TKSnsClientTLV Tlv;
	CSerialization s((char *)strBuffer.data(), strBuffer.size());
	s.SetSerializationType(enum_Serialization_Type_Read);
	Tlv.Serialization(s);
}

void ToBuffer( CSerialization &cs, std::string &strBuffer )
{
	strBuffer.clear();
	strBuffer.append(cs.GetData(), cs.GetDataLen());
}

volatile long CTestNode::m_lCount = 0;

CTestNode::CTestNode()
	: m_lIndex(InterlockedIncrement(&CTestNode::m_lCount))
{
	printf("CTestNode\n");
}

CTestNode::CTestNode( const CTestNode &other )
	: m_lIndex(InterlockedIncrement(&CTestNode::m_lCount))
{
	printf("copy CTestNode\n");
}

CTestNode::~CTestNode()
{
	printf("~CTestNode\n");
}

long CTestNode::GetIndex() const
{
	return m_lIndex;
}

long CTestNode::GetCount()
{
	return CTestNode::m_lCount;
}

void CTestNode::SetIndex( long lIndex )
{
	m_lIndex = lIndex;
}

CTestNodeManager::CTestNodeManager()
	: m_pNodeArray(NULL)
	, m_nNodeCount(0)
{
	printf("CTestNodeManager\n");
}

CTestNodeManager::CTestNodeManager( const CTestNodeManager &other )
{
	if (NULL != m_pNodeArray)
	{
		delete []m_pNodeArray;
		m_pNodeArray = NULL;
	}
	m_nNodeCount = other.m_nNodeCount;
	if (0 != m_nNodeCount)
	{
		m_pNodeArray = new CTestNode[m_nNodeCount];
		for (int nIndex = 0;nIndex < m_nNodeCount; nIndex++)
		{
			m_pNodeArray[nIndex] = other.m_pNodeArray[nIndex];
		}
	}
	
	printf("copy CTestNodeManager\n");
}

CTestNodeManager::~CTestNodeManager()
{
	printf("~CTestNodeManager\n");
	if (NULL != m_pNodeArray)
	{
		delete []m_pNodeArray;
		m_pNodeArray = NULL;
	}
	m_nNodeCount = 0;
}

void CTestNodeManager::InitNode( int nCount )
{
	if (NULL != m_pNodeArray)
	{
		delete []m_pNodeArray;
	}
	m_nNodeCount = nCount;
	m_pNodeArray = new CTestNode[nCount];
}

CTestNode* CTestNodeManager::GetNode( int nIndex )
{
	return &m_pNodeArray[nIndex];
}

CTestNode& CTestNodeManager::GetRefNode( int nIndex )
{
	return m_pNodeArray[nIndex];
}

BOOL CTestNodeManager::IsNodeExist( CTestNode *pNode )
{
	for (int nIndex = 0;nIndex < m_nNodeCount; nIndex++)
	{
		if (&m_pNodeArray[nIndex] == pNode)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTestNodeManager::GetNodeValue( int nIndex, CTestNode *pNode )
{
	*pNode = m_pNodeArray[nIndex];
	return TRUE;
}

BOOL CTestNodeManager::GetRefNodeValue( int nIndex, CTestNode &Node )
{
	CTestNode *pNode = &Node;
	Node = m_pNodeArray[nIndex];
	return TRUE;
}

CTestContainer::CTestContainer()
{
	printf("CTestContainer\n");
}

CTestContainer::CTestContainer( const CTestContainer &other )
{
	printf("copy CTestContainer\n");
	m_NodeManager = other.m_NodeManager;
}

CTestContainer::~CTestContainer()
{
	printf("~CTestContainer\n");
}

CTestNodeManager* CTestContainer::GetNodeManager()
{
	return &m_NodeManager;
}

CTestContainer_wrapper::CTestContainer_wrapper()
	: CTestContainer()
{
	printf("CTestContainer_wrapper\n");
}

CTestContainer_wrapper::CTestContainer_wrapper( const CTestContainer_wrapper& other )
	: CTestContainer(other)
{
	printf("copy CTestContainer_wrapper\n");
}

CTestContainer_wrapper::~CTestContainer_wrapper()
{
	printf("~CTestContainer_wrapper\n");
}

TKSnsClientTLV::TKSnsClientTLV()
{
	printf("TKSnsClientTLV\n");
	dwID = 0;
	dwType = 0;
}

void TKSnsClientTLV::SetDword( DWORD dwPropertyID, DWORD dwPropertyValue )
{
	strValue.clear();
	dwID = dwPropertyID;
	dwType = TK_SNSSRV_ENUM_MARKDWORD;
	strValue.append((char*)&dwPropertyValue, sizeof(DWORD));
}

void TKSnsClientTLV::SetString( DWORD dwPropertyID, const char* pPropertyValue )
{
	strValue.clear();
	dwID = dwPropertyID;
	dwType = TK_SNSSRV_ENUM_MARKSTR;
	DWORD dwLen = (DWORD)strlen(pPropertyValue) + 1;
	strValue.append(pPropertyValue, dwLen);
}

BOOL TKSnsClientTLV::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 属性ID
		aSerialization.Serialization(dwID);
		// 属性类型
		aSerialization.Serialization(dwType);
		// 属性值
		aSerialization.Serialization(strValue);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL TKSnsClientTLV::ToDword( DWORD &dwValue )const
{

	if (TK_SNSSRV_ENUM_MARKDWORD == dwType
		&& sizeof(DWORD) == strValue.size())
	{
		memcpy(&dwValue, strValue.data(), sizeof(DWORD));
		return TRUE;
	}
	else
	{
		assert(false);
		return FALSE;
	}
}

BOOL TKSnsClientTLV::ToString( std::string &strOutValue )const
{
	if (TK_SNSSRV_ENUM_MARKSTR == dwType)
	{
		strOutValue = strValue;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

TKSnsClientTLV::~TKSnsClientTLV()
{
	printf("~TKSnsClientTLV\n");
}

TKSnsClientSnsProperty::TKSnsClientSnsProperty()
{
	dwSnsPropertyCount = 0;
}

BOOL TKSnsClientSnsProperty::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 容错
		if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
		{
			DWORD dwCount = (DWORD)SnsClientTLVArray.size();
			if (dwSnsPropertyCount != dwCount)
				dwSnsPropertyCount = dwCount;
		}

		// 关系属性个数
		aSerialization.Serialization(dwSnsPropertyCount);
		// 关系属性数组
		for (DWORD dwIndex = 0; dwIndex < dwSnsPropertyCount; ++dwIndex)
		{
			if (aSerialization.GetSerializationType() == enum_Serialization_Type_Read)	// 读
			{
				TKSnsClientTLV stSnsClientTLV;
				if (!stSnsClientTLV.Serialization(aSerialization))
					return FALSE;

				SnsClientTLVArray.push_back(stSnsClientTLV);
			}
			else if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
			{
				if (!SnsClientTLVArray[dwIndex].Serialization(aSerialization))
					return FALSE;
			}
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

TKSnsClientSnsIndex::TKSnsClientSnsIndex()
{
	wSnsCID = 0;
	wSnsTID = 0;
	dwPID = 0;
}

BOOL TKSnsClientSnsIndex::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 关系类别ID
		aSerialization.Serialization(wSnsCID);
		// 关系类型ID
		aSerialization.Serialization(wSnsTID);
		// 关系拥有者ID
		aSerialization.Serialization(dwPID);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

TKSnsClientSnsTimeStamp::TKSnsClientSnsTimeStamp()
{
	dwTimeStamp = 0;
}

BOOL TKSnsClientSnsTimeStamp::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 关系索引
		if (!stSnsClientSnsIndex.Serialization(aSerialization))
			return FALSE;

		// 时间戳
		aSerialization.Serialization(dwTimeStamp);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

TKSnsClientHeader::TKSnsClientHeader()
{
	dwMessageID = TK_SNS_MESSAGE_ID_NONE;
	dwMessageType = TK_SNS_MESSAGE_TYPE_NONE;
	dwProtocolVersion = 0;
	bSuccess = FALSE;
	dwErrorCode = 0;
}

BOOL TKSnsClientHeader::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 消息ID
		aSerialization.Serialization(dwMessageID);
		// 消息的类型
		aSerialization.Serialization(dwMessageType);
		// 客户端协议版本号
		aSerialization.Serialization(dwProtocolVersion);
		// 成功或失败
		aSerialization.Serialization(bSuccess);
		// 错误码
		aSerialization.Serialization(dwErrorCode);
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

TKSnsClientGetSnsTimeStampListFromServer::TKSnsClientGetSnsTimeStampListFromServer()
{
	stSnsClientHeader.dwMessageID = TK_SNS_MESSAGE_ID_SNS_GET_SNSTIMESTAMP_LIST_FROM_SERVER;
	stSnsClientHeader.dwProtocolVersion = 0;
	dwUserID = 0;
	wSnsCID = 0;
	dwSnsTypeCount = 0;
	dwSnsTimeStampCount = 0;
}

BOOL TKSnsClientGetSnsTimeStampListFromServer::Serialization( CSerialization& aSerialization )
{
	try
	{
		// 容错
		if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
		{
			DWORD dwCount = (DWORD)SnsTypeArray.size();
			if (dwSnsTypeCount != dwCount)
				dwSnsTypeCount = dwCount;

			dwCount = (DWORD)SnsClientSnsTimeStampArray.size();
			if (dwSnsTimeStampCount != dwCount)
				dwSnsTimeStampCount = dwCount;
		}

		// 客户端协议头
		if (!stSnsClientHeader.Serialization(aSerialization))
			return FALSE;

		// 用户ID
		aSerialization.Serialization(dwUserID);
		// 获取的关系类别
		aSerialization.Serialization(wSnsCID);
		// 获取的关系类型数量
		aSerialization.Serialization(dwSnsTypeCount);
		// 指定的关系类型数组
		for (DWORD dwIndex = 0; dwIndex < dwSnsTypeCount; ++dwIndex)
		{
			if (aSerialization.GetSerializationType() == enum_Serialization_Type_Read)	// 读
			{
				WORD wSnsType;
				aSerialization.Serialization(wSnsType);

				SnsTypeArray.push_back(wSnsType);
			}
			else if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
			{
				aSerialization.Serialization(SnsTypeArray[dwIndex]);
			}
		}

		// 返回的关系时间戳数量
		aSerialization.Serialization(dwSnsTimeStampCount);
		// 返回的关系时间戳数组
		for (DWORD dwIndex = 0; dwIndex < dwSnsTimeStampCount; ++dwIndex)
		{
			if (aSerialization.GetSerializationType() == enum_Serialization_Type_Read)	// 读
			{
				TKSnsClientSnsTimeStamp stSnsClientSnsTimeStamp;
				if (!stSnsClientSnsTimeStamp.Serialization(aSerialization))
					return FALSE;

				SnsClientSnsTimeStampArray.push_back(stSnsClientSnsTimeStamp);
			}
			else if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
			{
				if (!SnsClientSnsTimeStampArray[dwIndex].Serialization(aSerialization))
					return FALSE;
			}
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}
