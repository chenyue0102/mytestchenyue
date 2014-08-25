#pragma once
#include "Serialization.h"
#include <vector>
#include <map>

template<typename classtype>
void RegisterVectorClass(lua_State *luaVM, const char *pstrName)
{
	typedef std::vector<classtype> InnerVectorType;
	typedef InnerVectorType::const_iterator InnerConstIterator;
	typedef InnerVectorType::iterator InnerIterator;
	luabind::module(luaVM)
	[ 
		class_<InnerVectorType >(pstrName). 
		def(constructor<>()). 
		def("PushBack", (void (InnerVectorType::*)(const InnerVectorType::value_type&))&InnerVectorType::push_back). 
		def("Begin", (InnerIterator(InnerVectorType::*)())&InnerVectorType::begin, dependency(result, _1)). 
		def("End", (InnerIterator(InnerVectorType::*)())&InnerVectorType::end, dependency(result, _1)). 
		def("ConstBegin", (InnerConstIterator(InnerVectorType::*)()const)&InnerVectorType::begin, dependency(result, _1)). 
		def("ConstEnd", (InnerConstIterator(InnerVectorType::*)()const)&InnerVectorType::end, dependency(result, _1)). 
		def("Clear", &InnerVectorType::clear). 
		def("Size", &InnerVectorType::size). 
#if _MSC_VER >= 1400		//MS VC++ 8.0
		def("Erase", (InnerIterator (InnerVectorType::*)(InnerConstIterator))&InnerVectorType::erase, dependency(result, _1))
#else
		def("Erase", (InnerIterator (InnerVectorType::*)(InnerIterator))&InnerVectorType::erase, dependency(result, _1))
#endif
	]; 
}

template<typename classtype>
void RegisterVectorIterator(lua_State *luaVM, const char *pstrConstIteratorName, const char *pstrIteratorName)
{
	typedef std::vector<classtype> InnerVectorType;
	typedef InnerVectorType::const_iterator InnerConstIterator;
	typedef InnerVectorType::iterator InnerIterator;

	luabind::module(luaVM)
	[
		class_<InnerConstIterator >(pstrConstIteratorName).
		def(constructor<>()).
		def(self == other<InnerConstIterator>()).
		def("Increment", (InnerConstIterator&(InnerConstIterator::*)())&(InnerConstIterator::operator++), discard_result).
		def("Decrement", (InnerConstIterator&(InnerConstIterator::*)())&(InnerConstIterator::operator--), discard_result).
		def("GetValue", &(InnerConstIterator::operator *), dependency(result, _1))
	];

	luabind::module(luaVM)
	[
		class_<InnerIterator, InnerConstIterator>(pstrIteratorName).
		def(constructor<>()).
		def(self == other<InnerIterator>()).
		def("Increment", (InnerIterator&(InnerIterator::*)())&(InnerIterator::operator++), discard_result).
		def("Decrement", (InnerIterator&(InnerIterator::*)())&(InnerIterator::operator--), discard_result).
		def("GetValue", (InnerIterator::reference(InnerIterator::*)())&(InnerIterator::operator *), dependency(result, _1))
	];
}

#define REGISTER_VECTOR_ITERATOR(classtype, luaVM)\
	RegisterVectorIterator<classtype>(luaVM, #classtype##"VectorConstIterator", #classtype##"VectorIterator");\
	\

#define REGISTER_VECTOR_CLASS(classtype, luaVM)\
	RegisterVectorClass<classtype>(luaVM, #classtype##"Vector");\
	\

template<typename Key, typename Value>
void RegisterMapClass(lua_State *luaVM, const char *pstrName, const char *pstrPairName)
{
	typedef std::map<Key, Value> InnerMapType;
	typedef InnerMapType::value_type InnerPair;
	typedef InnerMapType::const_iterator InnerConstIterator;
	typedef InnerMapType::iterator InnerIterator;

	luabind::module(luaVM)
	[
		class_<InnerPair >(pstrPairName). 
		def(constructor<>()).
		def(constructor<Key,Value>()).
		def_readonly("First", &InnerPair::first).
		def_readwrite("Second", &InnerPair::second)
	];
	luabind::module(luaVM)
	[
		class_<InnerMapType >(pstrName). 
		def(constructor<>()). 
		def("Insert", (InnerMapType::_Pairib (InnerMapType::*)(const InnerMapType::value_type&))&InnerMapType::insert, discard_result).
#if _MSC_VER >= 1400		//MS VC++ 8.0
		def("Erase", (InnerIterator (InnerMapType::*)(InnerConstIterator))&InnerMapType::erase, dependency(result, _1)).
#else
		def("Erase", (InnerIterator (InnerMapType::*)(InnerIterator))&InnerMapType::erase, dependency(result, _1)).
#endif
		def("EraseKey", (InnerMapType::size_type (InnerMapType::*)(const Key&))&InnerMapType::erase).
		def("Find", (InnerIterator (InnerMapType::*)(const Key&))&InnerMapType::find, dependency(result, _1)).
		def("ConstFind", (InnerConstIterator (InnerMapType::*)(const Key&)const)&InnerMapType::find, dependency(result, _1)).
		def("Clear", &InnerMapType::clear).
		def("Begin", (InnerIterator(InnerMapType::*)())&InnerMapType::begin, dependency(result, _1)).
		def("ConstBegin", (InnerConstIterator(InnerMapType::*)()const)&InnerMapType::begin, dependency(result, _1)).
		def("End", (InnerIterator(InnerMapType::*)())&InnerMapType::end, dependency(result, _1)).
		def("ConstEnd", (InnerConstIterator(InnerMapType::*)()const)&InnerMapType::end, dependency(result, _1)).
		def("Size", &InnerMapType::size)
	];
}

template<typename KeyType, typename ValueType>
void RegisterMapIterator(lua_State *luaVM, const char *pstrConstIteratorName, const char *pstrIteratorName)
{
	typedef std::map<KeyType, ValueType> InnerMapType;
	typedef InnerMapType::const_iterator InnerConstIterator;
	typedef InnerMapType::iterator InnerIterator;
	luabind::module(luaVM)
	[
		class_<InnerConstIterator >(pstrConstIteratorName).
		def(constructor<>()).
		def(self == other<InnerConstIterator>()).
		def("Increment", (InnerConstIterator& (InnerConstIterator::*)())&(InnerConstIterator::operator ++), discard_result).
		def("Decrement", (InnerConstIterator& (InnerConstIterator::*)())&(InnerConstIterator::operator --), discard_result).
		def("GetValue", &(InnerConstIterator::operator *), dependency(result, _1))
	];

	luabind::module(luaVM)
	[
		class_<InnerIterator, InnerConstIterator>(pstrIteratorName).
		def(constructor<>()).
		def(self == other<InnerIterator>()).
		def("Increment", (InnerIterator&(InnerIterator::*)())&(InnerIterator::operator++), discard_result).
		def("Decrement", (InnerIterator&(InnerIterator::*)())&(InnerIterator::operator--), discard_result).
		def("GetValue", &(InnerIterator::operator *), dependency(result, _1))
	];
}

#define REGISTER_MAP_ITERATOR(keytype, valuetype, luaVM)\
	RegisterMapIterator<keytype, valuetype>(luaVM, #keytype###valuetype##"MapConstIterator", #keytype###valuetype##"MapIterator"); \
	\

#define REGISTER_MAP_CLASS(keytype, valuetype, luaVM) \
	RegisterMapClass<keytype, valuetype>(luaVM, #keytype###valuetype##"Map", #keytype###valuetype##"MapPair"); \
	\


extern void RegisterTestLuaClass(lua_State *luaVM);

class CTestNode
{
public:
	CTestNode();
	CTestNode(const CTestNode &other);
	virtual ~CTestNode();
public:
	long		GetIndex()const;
	void		SetIndex(long lIndex);
	static	long GetCount();
private:
	long		m_lIndex;
	static volatile long		m_lCount;
};

class CTestNodeManager
{
public:
	CTestNodeManager();
	CTestNodeManager(const CTestNodeManager &other);
	virtual ~CTestNodeManager();
public:
	void InitNode(int nCount);
	CTestNode* GetNode(int nIndex);
	CTestNode& GetRefNode(int nIndex);
	BOOL	IsNodeExist(CTestNode *pNode);
	BOOL	GetNodeValue(int nIndex, CTestNode *pNode);
	BOOL	GetRefNodeValue(int nIndex, CTestNode &Node);
private:
	CTestNode *m_pNodeArray;
	int			m_nNodeCount;
};

class CTestContainer
{
public:
	CTestContainer();
	CTestContainer(const CTestContainer &other);
	virtual ~CTestContainer();
public:
	CTestNodeManager* GetNodeManager();
private:
	CTestNodeManager m_NodeManager;
};

class CTestContainer_wrapper 
	: public CTestContainer
	, public luabind::wrap_base
{
public:
	CTestContainer_wrapper();
	CTestContainer_wrapper(const CTestContainer_wrapper& other);
	~CTestContainer_wrapper();
};

enum eDicGlobalSnsMebMarkT
{
	TK_SNSSRV_ENUM_MARKRESERVE = 0, // 保留
	TK_SNSSRV_ENUM_MARKBYTE    = 1, // BYTE
	TK_SNSSRV_ENUM_MARKWORD    = 2, // WORD
	TK_SNSSRV_ENUM_MARKSTR     = 3, // STR
	TK_SNSSRV_ENUM_MARKDWORD   = 4, // DWORD
	TK_SNSSRV_ENUM_MARKERROR   = 0XFF,//错误
};

struct TKSnsClientTLV
{
	DWORD	dwID;			// 属性ID
	DWORD	dwType;			// 属性类型(见eDicGlobalSnsMebMarkT)
	std::string	strValue;		// 属性值

	TKSnsClientTLV();
	~TKSnsClientTLV();
	void SetDword(DWORD dwPropertyID, DWORD dwPropertyValue);
	void SetString(DWORD dwPropertyID, const char* pPropertyValue);

	BOOL	ToDword(DWORD &dwValue)const;
	BOOL	ToString(std::string &strOutValue)const;


	BOOL Serialization(CSerialization& aSerialization);
};

// 关系索引
struct TKSnsClientSnsIndex
{
	WORD	wSnsCID;			// 关系类别ID：表示关系大类
	// 如 “私人关系”“组织关系”……
	// 参见：eDicGlobalSnsClass

	WORD	wSnsTID;			// 关系类型ID：表示具体是哪种关系
	// 属于“私人关系”时， 表示“好友”、“关注用户”、“黑名单”……
	// 属于“组织关系”时， 表示“公社”、“家族”……
	// 参见：SnsC 获得的关系定义字典表

	DWORD	dwPID;				// 关系拥有者ID：
	// 属于“私人关系”时为 UserID
	// 属于“组织关系”时为 OrgID

	TKSnsClientSnsIndex();
	BOOL Serialization(CSerialization& aSerialization);
};

// 关系时间戳
struct TKSnsClientSnsTimeStamp
{
	TKSnsClientSnsIndex	stSnsClientSnsIndex;	// 关系索引
	DWORD				dwTimeStamp;			// 时间戳

	TKSnsClientSnsTimeStamp();
	BOOL Serialization(CSerialization& aSerialization);
};

// 客户端协议头
struct TKSnsClientHeader
{
	// 消息ID,见TK_SNS_MESSAGE_ID
	DWORD	dwMessageID;

	// 消息的类型,见TK_SNS_MESSAGE_TYPE
	DWORD	dwMessageType;

	// 客户端协议版本号,见"客户端协议版本号定义"部分
	DWORD	dwProtocolVersion;

	// 成功或失败
	BOOL	bSuccess;

	// 错误码(根据具体协议的不同,对错误码的解释不同,不是所有失败都有错误码,dwErrorCode默认值为0)
	DWORD	dwErrorCode;

	TKSnsClientHeader();
	BOOL Serialization(CSerialization& aSerialization);
};

// 从服务器获取关系时间戳列表
struct TKSnsClientGetSnsTimeStampListFromServer
{
	TKSnsClientHeader				stSnsClientHeader;			// 客户端协议头
	DWORD							dwUserID;					// 用户ID
	WORD							wSnsCID;					// 获取的关系类别(0代表所有)
	DWORD							dwSnsTypeCount;				// 获取的关系类型数量(0代表所有,>0时采用后缀指定列表,而wSnsCID则无意义)
	vector<WORD>					SnsTypeArray;				// 指定的关系类型数组
	DWORD							dwSnsTimeStampCount;		// 返回的关系时间戳数量(请求时不需要填写)
	vector<TKSnsClientSnsTimeStamp>	SnsClientSnsTimeStampArray;	// 返回的关系时间戳数组(请求时不需要填写)

	TKSnsClientGetSnsTimeStampListFromServer();
	BOOL Serialization(CSerialization& aSerialization);
};

// 关系属性
struct TKSnsClientSnsProperty
{
	DWORD					dwSnsPropertyCount;		// 关系属性个数
	std::vector<TKSnsClientTLV>	SnsClientTLVArray;		// 关系属性数组

	TKSnsClientSnsProperty();
	BOOL Serialization(CSerialization& aSerialization);
};

void TestSerializeIn(std::string &strBuffer);

void ToBuffer(CSerialization &cs, std::string &strBuffer);


enum TK_SNS_MESSAGE_ID
{
	TK_SNS_MESSAGE_ID_NONE = 0,															// 保留

	TK_SNS_MESSAGE_ID_COMMON_MIN = 1,													// 通用最小消息ID
	TK_SNS_MESSAGE_ID_COMMON_SOCKET_CLOSE = 2,											// 网络关闭
	TK_SNS_MESSAGE_ID_COMMON_LOGIN = 3,													// 登录
	TK_SNS_MESSAGE_ID_COMMON_LOGOUT = 4,												// 注销
	TK_SNS_MESSAGE_ID_COMMON_MAX = 200,													// 通用最大消息ID

	TK_SNS_MESSAGE_ID_SNS_MIN = 201,													// 关系最小消息ID
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_SVR_SETTING = 202,									// 获取关系服务器设置
	TK_SNS_MESSAGE_ID_SNS_GET_SNSTIMESTAMP_LIST_FROM_SERVER = 203,						// 从服务器获取关系时间戳列表
	TK_SNS_MESSAGE_ID_SNS_CREATE_SNS = 204,												// 创建关系
	TK_SNS_MESSAGE_ID_SNS_JOIN_SNS = 205,												// 加入关系
	TK_SNS_MESSAGE_ID_SNS_DELETE_SNS = 206,												// 删除关系
	TK_SNS_MESSAGE_ID_SNS_EXIT_SNS = 207,												// 退出关系

	TK_SNS_MESSAGE_ID_SNS_GET_SNS_PROPERTY_FROM_SERVER = 208,							// 从服务器获取关系属性
	TK_SNS_MESSAGE_ID_SNS_MODIFY_SNS_PROPERTY_FROM_SERVER = 209,						// 从服务器修改关系属性

	TK_SNS_MESSAGE_ID_SNS_ADD_SNS_MEMBER = 210,											// 增加关系成员
	TK_SNS_MESSAGE_ID_SNS_DELETE_SNS_MEMBER = 211,										// 删除关系成员
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_MEMBER_PROPERTY_FROM_SERVER = 212,					// 从服务器获取关系成员属性
	TK_SNS_MESSAGE_ID_SNS_MODIFY_SNS_MEMBER_PROPERTY_FROM_SERVER = 213,					// 从服务器修改关系成员属性

	TK_SNS_MESSAGE_ID_SNS_TRANSLATE_SNS_MEMBER = 214,									// 转移关系成员
	TK_SNS_MESSAGE_ID_SNS_GET_SNSINDEX_BY_SNS_PROPERTY = 215,							// 根据关系属性获得关系索引
	TK_SNS_MESSAGE_ID_SNS_GET_SNSINDEX_LIST_BY_SOME_TYPE = 216,							// 按某些类型获取关系索引列表
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_MEMBER_RANKING = 217,									// 获取关系成员排行榜
	TK_SNS_MESSAGE_ID_SNS_PUSH_SNS_MEMBER_RANKING_CHANGE = 218,							// 推送关系成员排行榜变化
	TK_SNS_MESSAGE_ID_SNS_MAX = 400,													// 关系最大消息ID

	TK_SNS_MESSAGE_ID_USER_MIN = 401,													// 用户最小消息ID
	TK_SNS_MESSAGE_ID_USER_GET_USER_PROPERTY_FROM_SERVER = 402,							// 从服务器获取用户属性
	TK_SNS_MESSAGE_ID_USER_MODIFY_USER_PROPERTY_FROM_SERVER = 403,						// 从服务器修改用户属性
	TK_SNS_MESSAGE_ID_USER_QUIT = 404,													// 其他用户退出
	TK_SNS_MESSAGE_ID_USER_GET_USERID_BY_USER_PROPERTY = 405,							// 通过用户属性获取用户ID
	TK_SNS_MESSAGE_ID_USER_GET_ONLINE_USER_LIST = 406,									// 获取在线人员列表
	TK_SNS_MESSAGE_ID_USER_MONEY = 407,													// 获取用户金币
	TK_SNS_MESSAGE_ID_USER_MAX = 600,													// 用户最大消息ID

	TK_SNS_MESSAGE_ID_COMMUNICATE_MIN = 601,											// 通讯最小消息ID
	TK_SNS_MESSAGE_ID_COMMUNICATE_ALOWSYSBOARD = 602,									// 发送下传通道信息
	TK_SNS_MESSAGE_ID_COMMUNICATE_EVENTAWARD = 603,										// 颁奖消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_GET_OFFLINE_MSG = 604,								// 获取离线消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_ANNOUNCEMENT = 605,									// 公告消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_OFFLINE_ANNOUNCEMENT = 606,							// 离线公告消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_ANNOUNCEMENTEX = 607,									// 公告扩展消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_OFFLINE_ANNOUNCEMENTEX = 608,							// 离线公告扩展消息
	TK_SNS_MESSAGE_ID_COMMUNICATE_ADD_SNS_MEMBER_TRANS = 609,							// 添加关系成员的流转
	TK_SNS_MESSAGE_ID_COMMUNICATE_TRANSLATE_SNS_MEMBER_TRANS = 610,						// 转让关系成员的流转
	TK_SNS_MESSAGE_ID_COMMUNICATE_MSG_TRANS = 611,										// 消息流转
	TK_SNS_MESSAGE_ID_COMMUNICATE_GIVE_GOODS = 612,										// 赠送物品
	TK_SNS_MESSAGE_ID_COMMUNICATE_MAX = 800,											// 通讯最大消息ID

	TK_SNS_MESSAGE_ID_LOCAL_DATA_MIN = 801,												// 本地数据最小消息ID
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNSTIMESTAMP_LIST_FROM_LOCAL = 802,				// 从本地获取关系时间戳列表
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNSTIMESTAMP_LIST_FROM_LOCAL = 803,				// 从本地修改关系时间戳列表
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNSTIMESTAMP_LIST_FROM_LOCAL = 804,				// 从本地删除关系时间戳列表
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_INDEX_LIST_FROM_LOCAL = 805,					// 从本地获取关系索引列表
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_PROPERTY_FROM_LOCAL = 806,						// 从本地获取关系属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNS_PROPERTY_FROM_LOCAL = 807,					// 从本地修改关系属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNS_PROPERTY_FROM_LOCAL = 808,					// 从本地删除关系属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_MEMBER_PROPERTY_FROM_LOCAL = 809,				// 从本地获取关系成员属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNS_MEMBER_PROPERTY_FROM_LOCAL = 810,			// 从本地修改关系成员属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNS_MEMBER_PROPERTY_FROM_LOCAL = 811,			// 从本地删除关系成员属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_RELATIONSHIP = 812,								// 获取某用户和本机用户有何关系
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_USER_PROPERTY_FROM_LOCAL = 813,					// 从本地获取用户属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_USER_PROPERTY_FROM_LOCAL = 814,					// 从本地修改用户属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_USER_PROPERTY_FROM_LOCAL = 815,					// 从本地删除用户属性
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SINGLE_PEOPLE_PROPERTY_LIST = 816,					// 获取单人属性列表
	TK_SNS_MESSAGE_ID_LOCAL_DATA_SNS_MEMBER_FUZZY_FIND = 817,							// 模糊查找关系成员
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD = 818,									// 消息记录
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_SET = 819,								// 消息记录集合
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_SAVE = 820,								// 消息记录保存
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_MODIFY_STATE = 821,						// 修改消息记录状态
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_DELETE = 822,							// 删除消息记录
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION1 = 823,					// 消息记录查询条件1
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION2 = 824,					// 消息记录查询条件2
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION3 = 825,					// 消息记录查询条件3
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION4 = 826,					// 消息记录查询条件4
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION5 = 827,					// 消息记录查询条件5
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION6 = 828,					// 消息记录查询条件6
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION7 = 829,					// 消息记录查询条件7
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MAX = 1000,											// 本地数据最大消息ID

	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_MIN = 1001,									// 进程间通讯最小消息ID
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_SEND_STATISTICS_MSG = 1002,					// 发送统计消息
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_USER_LEVEL = 1003,						// 获取用户等级
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_GOODS_INFO = 1004,						// 获取物品信息
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_GOLD_COUNT = 1005,						// 获取金币数量
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_TICKET = 1006,							// 获取票证
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_OPEN_URL = 1007,							// 打开URL
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_HEAD_IMAGE_FILE_PATH = 1008,			// 获取头像文件路径
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_UPDATE_UNREAD_MSG_COUNT = 1009,				// 更新未读消息数量
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_CHECK_GAME = 1010,							// 检测游戏
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_SEND_SIGN_UP_OFF_MSG = 1011,				// 发送报名结束消息
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_OPEN_COMMUNITY_SUB_DLG = 1012,				// 打开大厅上的社区子对话框
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_MAX = 1200,									// 进程间通讯最大消息ID
};

// 消息的类型
enum TK_SNS_MESSAGE_TYPE
{
	// 保留
	TK_SNS_MESSAGE_TYPE_NONE = 0,
	// 请求操作类型(到服务器请求数据)
	TK_SNS_MESSAGE_TYPE_REQ = 1,
	// 应答操作类型(服务器返回的应答数据)
	TK_SNS_MESSAGE_TYPE_ACK = 2,
	// 推送操作类型(服务器主动推送的数据)
	TK_SNS_MESSAGE_TYPE_PUSH = 3,
	// 本地操作类型(到本地获取/修改数据)
	TK_SNS_MESSAGE_TYPE_LOCAL = 4,
	// 进程间操作类型
	TK_SNS_MESSAGE_TYPE_PROCESS_COMMUNICATION = 5,
};