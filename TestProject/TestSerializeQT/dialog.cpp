#include "dialog.h"
#include "ui_dialog.h"
#include "TestStruct.h"
#include "TKPtrList.h"
#include "SerializeHelperEx.h"
#include <QRadioButton>
#include <QDebug>
#include "PostMsgHelper.h"


struct TKTest
{
	CTKPtrList<std::string> stringArray;
	std::vector<std::string*> stringVector;

	TKTest()
	{

	}
	void init()
	{
		std::string *pstr1 = new std::string("111111");
		stringArray.AddTail(pstr1);

		std::string *pstr2 = new std::string("22222");
		stringArray.AddTail(pstr2);

		std::string *pstr3 = new std::string("333333");
		stringArray.AddTail(pstr3);

		std::string *pstrvector1 = new std::string("aaaaaa");
		stringVector.push_back(pstrvector1);

		std::string *pstrvector2 = new std::string("bbbbbbb");
		stringVector.push_back(pstrvector2);

		std::string *pstrvector3 = new std::string("ccccccc");
		stringVector.push_back(pstrvector3);
	}
	bool operator==(const TKTest &other)
	{
		return (stringArray == other.stringArray
			&& stringVector == other.stringVector
			);
	}
};

bool SerializeStruct(ISerialize *pSerialize, TKTest &Value)
{
	try
	{
		SERIALIZE_VALUE(stringArray);
		SERIALIZE_VALUE(stringVector);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
	connect(ui->pushButtonAllType, SIGNAL(clicked()), SLOT(OnTestAllType()));
	connect(ui->pushButtonTK, SIGNAL(clicked()), SLOT(OnTKType()));
	connect(ui->pushButtonLoss, SIGNAL(clicked()), SLOT(OnLoss()));
	connect(ui->pushButtonNoitfyVoidT, SIGNAL(clicked()), SLOT(OnTestVoidT()));
	connect(ui->pushButtonNoitfyVoidVoid, SIGNAL(clicked()), SLOT(OnTestVoidVoid()));
	connect(ui->pushButtonQueryULongT, SIGNAL(clicked()), SLOT(OnTestULongT()));
	connect(ui->pushButtonQueryULongIO, SIGNAL(clicked()), SLOT(OnTestULongIO()));
	

	m_DealMsgHelper.RegMsg(1, this, &Dialog::OnNotifyVoidT);
	m_DealMsgHelper.RegMsg(2, this, &Dialog::OnNotifyVoidVoid);
	m_DealMsgHelper.RegMsg(3, this, &Dialog::OnQueryULongT);
	m_DealMsgHelper.RegMsg(4, this, &Dialog::OnQueryULongIO);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::OnTestAllType()
{
	auto f = GetSerializeFormat();
	Test2(f);
}

void Dialog::OnTKType()
{
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(GetSerializeFormat()), &DestroySerializeInterface);
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(GetSerializeFormat()), &DestroySerializeInterface);
	DoTest2<TKTest>(pSerializeWrite.get(), pSerializeRead.get());
}

SerializeExport::EnumSerializeFormat Dialog::GetSerializeFormat()
{
	if (ui->radioButtonBin->isChecked())
	{
		return EnumSerializeFormatBinary;
	}
	else if (ui->radioButtonJson->isChecked())
	{
		return EnumSerializeFormatJson;
	}
	else
	{
		return EnumSerializeFormatXml;
	}
}

void Dialog::OnLoss()
{
	auto f = GetSerializeFormat();
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(f), &DestroySerializeInterface);
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(f), &DestroySerializeInterface);
	DoTestMiss(pSerializeWrite.get(), pSerializeRead.get());
}

void Dialog::OnNotifyVoidT(const TestA &a)
{
	qDebug() << "OnNotifyVoidT " << a.a;
}

void Dialog::OnTestVoidT()
{
	auto f = GetSerializeFormat();
	TestA ta;
	ta.a = 123456;
	PostMsgHelper::PostNotifyMsg(1, ta, f, &m_DealMsgHelper);
}

void Dialog::OnNotifyVoidVoid()
{
	qDebug() << "OnNotifyVoidVoid ";
}

void Dialog::OnTestVoidVoid()
{
	PostMsgHelper::PostNotifyMsg(2, &m_DealMsgHelper);
}

unsigned long Dialog::OnQueryULongT(TestB &b)
{
	qDebug() << "OnQueryULongT " << b.strName.c_str() << " " ;
	b.strName = "cat";
	b.vtValue.clear();
	b.vtValue.push_back("some cats");
	return 10;
}

void Dialog::OnTestULongT()
{
	auto f = GetSerializeFormat();
	unsigned long ulRet = 0;
	TestB b;
	b.strName = "dog";
	b.vtValue.push_back("some dogs");
	PostMsgHelper::SendQueryMsg(3, b, &ulRet, f, &m_DealMsgHelper);
}

unsigned long Dialog::OnQueryULongIO(const TestA &a, TestB &b)
{
	qDebug() << "OnQueryULongIO " << a.a << " " ;
	b.strName = "monkey";
	b.vtValue.push_back("some monkeys");
	return 11;
}

void Dialog::OnTestULongIO()
{
	auto f = GetSerializeFormat();
	unsigned long ulRet = 0;
	TestA a;
	a.a = 77777;
	TestB b;
	PostMsgHelper::SendQueryMsg(4, a, b, &ulRet, f, &m_DealMsgHelper);
}

