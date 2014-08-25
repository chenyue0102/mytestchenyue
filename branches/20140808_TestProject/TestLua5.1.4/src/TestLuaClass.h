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
	TK_SNSSRV_ENUM_MARKRESERVE = 0, // ����
	TK_SNSSRV_ENUM_MARKBYTE    = 1, // BYTE
	TK_SNSSRV_ENUM_MARKWORD    = 2, // WORD
	TK_SNSSRV_ENUM_MARKSTR     = 3, // STR
	TK_SNSSRV_ENUM_MARKDWORD   = 4, // DWORD
	TK_SNSSRV_ENUM_MARKERROR   = 0XFF,//����
};

struct TKSnsClientTLV
{
	DWORD	dwID;			// ����ID
	DWORD	dwType;			// ��������(��eDicGlobalSnsMebMarkT)
	std::string	strValue;		// ����ֵ

	TKSnsClientTLV();
	~TKSnsClientTLV();
	void SetDword(DWORD dwPropertyID, DWORD dwPropertyValue);
	void SetString(DWORD dwPropertyID, const char* pPropertyValue);

	BOOL	ToDword(DWORD &dwValue)const;
	BOOL	ToString(std::string &strOutValue)const;


	BOOL Serialization(CSerialization& aSerialization);
};

// ��ϵ����
struct TKSnsClientSnsIndex
{
	WORD	wSnsCID;			// ��ϵ���ID����ʾ��ϵ����
	// �� ��˽�˹�ϵ������֯��ϵ������
	// �μ���eDicGlobalSnsClass

	WORD	wSnsTID;			// ��ϵ����ID����ʾ���������ֹ�ϵ
	// ���ڡ�˽�˹�ϵ��ʱ�� ��ʾ�����ѡ�������ע�û�������������������
	// ���ڡ���֯��ϵ��ʱ�� ��ʾ�����硱�������塱����
	// �μ���SnsC ��õĹ�ϵ�����ֵ��

	DWORD	dwPID;				// ��ϵӵ����ID��
	// ���ڡ�˽�˹�ϵ��ʱΪ UserID
	// ���ڡ���֯��ϵ��ʱΪ OrgID

	TKSnsClientSnsIndex();
	BOOL Serialization(CSerialization& aSerialization);
};

// ��ϵʱ���
struct TKSnsClientSnsTimeStamp
{
	TKSnsClientSnsIndex	stSnsClientSnsIndex;	// ��ϵ����
	DWORD				dwTimeStamp;			// ʱ���

	TKSnsClientSnsTimeStamp();
	BOOL Serialization(CSerialization& aSerialization);
};

// �ͻ���Э��ͷ
struct TKSnsClientHeader
{
	// ��ϢID,��TK_SNS_MESSAGE_ID
	DWORD	dwMessageID;

	// ��Ϣ������,��TK_SNS_MESSAGE_TYPE
	DWORD	dwMessageType;

	// �ͻ���Э��汾��,��"�ͻ���Э��汾�Ŷ���"����
	DWORD	dwProtocolVersion;

	// �ɹ���ʧ��
	BOOL	bSuccess;

	// ������(���ݾ���Э��Ĳ�ͬ,�Դ�����Ľ��Ͳ�ͬ,��������ʧ�ܶ��д�����,dwErrorCodeĬ��ֵΪ0)
	DWORD	dwErrorCode;

	TKSnsClientHeader();
	BOOL Serialization(CSerialization& aSerialization);
};

// �ӷ�������ȡ��ϵʱ����б�
struct TKSnsClientGetSnsTimeStampListFromServer
{
	TKSnsClientHeader				stSnsClientHeader;			// �ͻ���Э��ͷ
	DWORD							dwUserID;					// �û�ID
	WORD							wSnsCID;					// ��ȡ�Ĺ�ϵ���(0��������)
	DWORD							dwSnsTypeCount;				// ��ȡ�Ĺ�ϵ��������(0��������,>0ʱ���ú�׺ָ���б�,��wSnsCID��������)
	vector<WORD>					SnsTypeArray;				// ָ���Ĺ�ϵ��������
	DWORD							dwSnsTimeStampCount;		// ���صĹ�ϵʱ�������(����ʱ����Ҫ��д)
	vector<TKSnsClientSnsTimeStamp>	SnsClientSnsTimeStampArray;	// ���صĹ�ϵʱ�������(����ʱ����Ҫ��д)

	TKSnsClientGetSnsTimeStampListFromServer();
	BOOL Serialization(CSerialization& aSerialization);
};

// ��ϵ����
struct TKSnsClientSnsProperty
{
	DWORD					dwSnsPropertyCount;		// ��ϵ���Ը���
	std::vector<TKSnsClientTLV>	SnsClientTLVArray;		// ��ϵ��������

	TKSnsClientSnsProperty();
	BOOL Serialization(CSerialization& aSerialization);
};

void TestSerializeIn(std::string &strBuffer);

void ToBuffer(CSerialization &cs, std::string &strBuffer);


enum TK_SNS_MESSAGE_ID
{
	TK_SNS_MESSAGE_ID_NONE = 0,															// ����

	TK_SNS_MESSAGE_ID_COMMON_MIN = 1,													// ͨ����С��ϢID
	TK_SNS_MESSAGE_ID_COMMON_SOCKET_CLOSE = 2,											// ����ر�
	TK_SNS_MESSAGE_ID_COMMON_LOGIN = 3,													// ��¼
	TK_SNS_MESSAGE_ID_COMMON_LOGOUT = 4,												// ע��
	TK_SNS_MESSAGE_ID_COMMON_MAX = 200,													// ͨ�������ϢID

	TK_SNS_MESSAGE_ID_SNS_MIN = 201,													// ��ϵ��С��ϢID
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_SVR_SETTING = 202,									// ��ȡ��ϵ����������
	TK_SNS_MESSAGE_ID_SNS_GET_SNSTIMESTAMP_LIST_FROM_SERVER = 203,						// �ӷ�������ȡ��ϵʱ����б�
	TK_SNS_MESSAGE_ID_SNS_CREATE_SNS = 204,												// ������ϵ
	TK_SNS_MESSAGE_ID_SNS_JOIN_SNS = 205,												// �����ϵ
	TK_SNS_MESSAGE_ID_SNS_DELETE_SNS = 206,												// ɾ����ϵ
	TK_SNS_MESSAGE_ID_SNS_EXIT_SNS = 207,												// �˳���ϵ

	TK_SNS_MESSAGE_ID_SNS_GET_SNS_PROPERTY_FROM_SERVER = 208,							// �ӷ�������ȡ��ϵ����
	TK_SNS_MESSAGE_ID_SNS_MODIFY_SNS_PROPERTY_FROM_SERVER = 209,						// �ӷ������޸Ĺ�ϵ����

	TK_SNS_MESSAGE_ID_SNS_ADD_SNS_MEMBER = 210,											// ���ӹ�ϵ��Ա
	TK_SNS_MESSAGE_ID_SNS_DELETE_SNS_MEMBER = 211,										// ɾ����ϵ��Ա
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_MEMBER_PROPERTY_FROM_SERVER = 212,					// �ӷ�������ȡ��ϵ��Ա����
	TK_SNS_MESSAGE_ID_SNS_MODIFY_SNS_MEMBER_PROPERTY_FROM_SERVER = 213,					// �ӷ������޸Ĺ�ϵ��Ա����

	TK_SNS_MESSAGE_ID_SNS_TRANSLATE_SNS_MEMBER = 214,									// ת�ƹ�ϵ��Ա
	TK_SNS_MESSAGE_ID_SNS_GET_SNSINDEX_BY_SNS_PROPERTY = 215,							// ���ݹ�ϵ���Ի�ù�ϵ����
	TK_SNS_MESSAGE_ID_SNS_GET_SNSINDEX_LIST_BY_SOME_TYPE = 216,							// ��ĳЩ���ͻ�ȡ��ϵ�����б�
	TK_SNS_MESSAGE_ID_SNS_GET_SNS_MEMBER_RANKING = 217,									// ��ȡ��ϵ��Ա���а�
	TK_SNS_MESSAGE_ID_SNS_PUSH_SNS_MEMBER_RANKING_CHANGE = 218,							// ���͹�ϵ��Ա���а�仯
	TK_SNS_MESSAGE_ID_SNS_MAX = 400,													// ��ϵ�����ϢID

	TK_SNS_MESSAGE_ID_USER_MIN = 401,													// �û���С��ϢID
	TK_SNS_MESSAGE_ID_USER_GET_USER_PROPERTY_FROM_SERVER = 402,							// �ӷ�������ȡ�û�����
	TK_SNS_MESSAGE_ID_USER_MODIFY_USER_PROPERTY_FROM_SERVER = 403,						// �ӷ������޸��û�����
	TK_SNS_MESSAGE_ID_USER_QUIT = 404,													// �����û��˳�
	TK_SNS_MESSAGE_ID_USER_GET_USERID_BY_USER_PROPERTY = 405,							// ͨ���û����Ի�ȡ�û�ID
	TK_SNS_MESSAGE_ID_USER_GET_ONLINE_USER_LIST = 406,									// ��ȡ������Ա�б�
	TK_SNS_MESSAGE_ID_USER_MONEY = 407,													// ��ȡ�û����
	TK_SNS_MESSAGE_ID_USER_MAX = 600,													// �û������ϢID

	TK_SNS_MESSAGE_ID_COMMUNICATE_MIN = 601,											// ͨѶ��С��ϢID
	TK_SNS_MESSAGE_ID_COMMUNICATE_ALOWSYSBOARD = 602,									// �����´�ͨ����Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_EVENTAWARD = 603,										// �佱��Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_GET_OFFLINE_MSG = 604,								// ��ȡ������Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_ANNOUNCEMENT = 605,									// ������Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_OFFLINE_ANNOUNCEMENT = 606,							// ���߹�����Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_ANNOUNCEMENTEX = 607,									// ������չ��Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_OFFLINE_ANNOUNCEMENTEX = 608,							// ���߹�����չ��Ϣ
	TK_SNS_MESSAGE_ID_COMMUNICATE_ADD_SNS_MEMBER_TRANS = 609,							// ��ӹ�ϵ��Ա����ת
	TK_SNS_MESSAGE_ID_COMMUNICATE_TRANSLATE_SNS_MEMBER_TRANS = 610,						// ת�ù�ϵ��Ա����ת
	TK_SNS_MESSAGE_ID_COMMUNICATE_MSG_TRANS = 611,										// ��Ϣ��ת
	TK_SNS_MESSAGE_ID_COMMUNICATE_GIVE_GOODS = 612,										// ������Ʒ
	TK_SNS_MESSAGE_ID_COMMUNICATE_MAX = 800,											// ͨѶ�����ϢID

	TK_SNS_MESSAGE_ID_LOCAL_DATA_MIN = 801,												// ����������С��ϢID
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNSTIMESTAMP_LIST_FROM_LOCAL = 802,				// �ӱ��ػ�ȡ��ϵʱ����б�
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNSTIMESTAMP_LIST_FROM_LOCAL = 803,				// �ӱ����޸Ĺ�ϵʱ����б�
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNSTIMESTAMP_LIST_FROM_LOCAL = 804,				// �ӱ���ɾ����ϵʱ����б�
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_INDEX_LIST_FROM_LOCAL = 805,					// �ӱ��ػ�ȡ��ϵ�����б�
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_PROPERTY_FROM_LOCAL = 806,						// �ӱ��ػ�ȡ��ϵ����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNS_PROPERTY_FROM_LOCAL = 807,					// �ӱ����޸Ĺ�ϵ����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNS_PROPERTY_FROM_LOCAL = 808,					// �ӱ���ɾ����ϵ����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SNS_MEMBER_PROPERTY_FROM_LOCAL = 809,				// �ӱ��ػ�ȡ��ϵ��Ա����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_SNS_MEMBER_PROPERTY_FROM_LOCAL = 810,			// �ӱ����޸Ĺ�ϵ��Ա����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_SNS_MEMBER_PROPERTY_FROM_LOCAL = 811,			// �ӱ���ɾ����ϵ��Ա����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_RELATIONSHIP = 812,								// ��ȡĳ�û��ͱ����û��кι�ϵ
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_USER_PROPERTY_FROM_LOCAL = 813,					// �ӱ��ػ�ȡ�û�����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MODIFY_USER_PROPERTY_FROM_LOCAL = 814,					// �ӱ����޸��û�����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_DELETE_USER_PROPERTY_FROM_LOCAL = 815,					// �ӱ���ɾ���û�����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_GET_SINGLE_PEOPLE_PROPERTY_LIST = 816,					// ��ȡ���������б�
	TK_SNS_MESSAGE_ID_LOCAL_DATA_SNS_MEMBER_FUZZY_FIND = 817,							// ģ�����ҹ�ϵ��Ա
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD = 818,									// ��Ϣ��¼
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_SET = 819,								// ��Ϣ��¼����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_SAVE = 820,								// ��Ϣ��¼����
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_MODIFY_STATE = 821,						// �޸���Ϣ��¼״̬
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_DELETE = 822,							// ɾ����Ϣ��¼
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION1 = 823,					// ��Ϣ��¼��ѯ����1
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION2 = 824,					// ��Ϣ��¼��ѯ����2
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION3 = 825,					// ��Ϣ��¼��ѯ����3
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION4 = 826,					// ��Ϣ��¼��ѯ����4
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION5 = 827,					// ��Ϣ��¼��ѯ����5
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION6 = 828,					// ��Ϣ��¼��ѯ����6
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MESSAGE_RECORD_FIND_CONDITION7 = 829,					// ��Ϣ��¼��ѯ����7
	TK_SNS_MESSAGE_ID_LOCAL_DATA_MAX = 1000,											// �������������ϢID

	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_MIN = 1001,									// ���̼�ͨѶ��С��ϢID
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_SEND_STATISTICS_MSG = 1002,					// ����ͳ����Ϣ
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_USER_LEVEL = 1003,						// ��ȡ�û��ȼ�
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_GOODS_INFO = 1004,						// ��ȡ��Ʒ��Ϣ
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_GOLD_COUNT = 1005,						// ��ȡ�������
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_TICKET = 1006,							// ��ȡƱ֤
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_OPEN_URL = 1007,							// ��URL
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_GET_HEAD_IMAGE_FILE_PATH = 1008,			// ��ȡͷ���ļ�·��
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_UPDATE_UNREAD_MSG_COUNT = 1009,				// ����δ����Ϣ����
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_CHECK_GAME = 1010,							// �����Ϸ
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_SEND_SIGN_UP_OFF_MSG = 1011,				// ���ͱ���������Ϣ
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_OPEN_COMMUNITY_SUB_DLG = 1012,				// �򿪴����ϵ������ӶԻ���
	TK_SNS_MESSAGE_ID_PROCESS_COMMUNICATION_MAX = 1200,									// ���̼�ͨѶ�����ϢID
};

// ��Ϣ������
enum TK_SNS_MESSAGE_TYPE
{
	// ����
	TK_SNS_MESSAGE_TYPE_NONE = 0,
	// �����������(����������������)
	TK_SNS_MESSAGE_TYPE_REQ = 1,
	// Ӧ���������(���������ص�Ӧ������)
	TK_SNS_MESSAGE_TYPE_ACK = 2,
	// ���Ͳ�������(�������������͵�����)
	TK_SNS_MESSAGE_TYPE_PUSH = 3,
	// ���ز�������(�����ػ�ȡ/�޸�����)
	TK_SNS_MESSAGE_TYPE_LOCAL = 4,
	// ���̼��������
	TK_SNS_MESSAGE_TYPE_PROCESS_COMMUNICATION = 5,
};