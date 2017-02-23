#include "dialog.h"
#include "ui_dialog.h"
#include "TestStruct.h"
#include "TKPtrList.h"
#include "SerializeHelperEx.h"
#include <QRadioButton>


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
