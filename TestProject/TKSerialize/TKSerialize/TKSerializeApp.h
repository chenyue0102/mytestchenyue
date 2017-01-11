#pragma once
#include <set>
#include "InterfaceSerialize.h"
#include "NormalLock.h"

using namespace SerializeExport;
class TKSerializeApp
{
public:
	TKSerializeApp(void);
	~TKSerializeApp(void);
public:
	void InitInstance();
	void ExitInstance();
public:
	ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat);
	bool DestroySerializeInterface(ISerialize *pInterface);
	bool SetDefaultStringCode(EnumSerializeStringCode DefaultStringCode);
	EnumSerializeStringCode GetDefaultStringCode();
private:
	std::set<ISerialize*> m_ISerializeArray;
	CNormalLock m_NormalLock;
	EnumSerializeStringCode m_DefaultStringCode;
};
extern TKSerializeApp theApp;
