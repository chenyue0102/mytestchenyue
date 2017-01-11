#include "TKSerializeApp.h"
#include <assert.h>
#include "BinarySerialize.h"
#include "JsonSerialize.h"
#include "XmlSerialize.h"

TKSerializeApp theApp;
TKSerializeApp::TKSerializeApp(void)
	: m_ISerializeArray()
	, m_NormalLock()
	, m_DefaultStringCode(EnumSerializeStringCodeNone)
{
}


TKSerializeApp::~TKSerializeApp(void)
{
	assert(0 == m_ISerializeArray.size());
}

void TKSerializeApp::InitInstance()
{

}

void TKSerializeApp::ExitInstance()
{

}

ISerialize* TKSerializeApp::CreateSerializeInterface(EnumSerializeFormat SerializeFormat)
{
	ISerialize *pInterface = nullptr;
	switch (SerializeFormat)
	{
	case EnumSerializeFormatBinary:
		pInterface = new CBinarySerialize();
		break;
	case EnumSerializeFormatJson:
		pInterface = new CJsonSerialize();
		break;
	case EnumSerializeFormatXml:
		pInterface = new CXmlSerialize();
		break;
	default:
		assert(false);
		break;
	}
	if (nullptr != pInterface)
	{
		CAutoLock AutoLock(m_NormalLock);
		pInterface->SetSerializeStringCode(m_DefaultStringCode);
		auto pair = m_ISerializeArray.insert(pInterface);
		assert(pair.second);
	}
	return pInterface;
}

bool TKSerializeApp::DestroySerializeInterface(ISerialize *pInterface)
{
	CAutoLock AutoLock(m_NormalLock);
	auto itor = m_ISerializeArray.find(pInterface);
	if (itor != m_ISerializeArray.end())
	{
		if (nullptr != pInterface)
		{
			switch (pInterface->GetSerializeFormat())
			{
			case EnumSerializeFormatBinary:
				delete static_cast<CBinarySerialize*>(pInterface);
				break;
			case EnumSerializeFormatJson:
				delete static_cast<CJsonSerialize*>(pInterface);
				break;
			case EnumSerializeFormatXml:
				delete static_cast<CXmlSerialize*>(pInterface);
				break;
			default:
				assert(false);
				break;
			}
		}
		m_ISerializeArray.erase(itor);
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

bool TKSerializeApp::SetDefaultStringCode(EnumSerializeStringCode DefaultStringCode)
{
	CAutoLock AutoLock(m_NormalLock);
	if (DefaultStringCode == EnumSerializeStringCodeNone
		|| DefaultStringCode == EnumSerializeStringCodeUtf8
		|| DefaultStringCode == EnumSerializeStringCodeBinary
		|| DefaultStringCode == EnumSerializeStringCodeGB2312)
	{
		m_DefaultStringCode = DefaultStringCode;
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

SerializeExport::EnumSerializeStringCode TKSerializeApp::GetDefaultStringCode()
{
	CAutoLock AutoLock(m_NormalLock);
	return m_DefaultStringCode;
}
