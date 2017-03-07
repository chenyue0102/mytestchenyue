#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "EnumSerialize.h"
#include "InterfaceSerialize.h"
#include "SerializeHelper.h"
#include "DealMsgHelper.h"

using namespace SerializeExport;
struct TestA
{
	int a;
};

inline bool SerializeStruct(ISerialize &pSerialize, TestA &Value)
{
	try
	{
		SERIALIZE_VALUE(a);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

struct TestB
{
	std::string strName;
	std::vector<std::string> vtValue;
};

inline bool SerializeStruct(ISerialize &pSerialize, TestB &Value)
{
	try
	{
		SERIALIZE_VALUE(strName);
		SERIALIZE_VALUE(vtValue);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

using namespace SerializeExport;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
	void OnTestAllType();
	void OnTKType();
	void OnLoss();
	void OnTestVoidT();
	void OnTestVoidVoid();
	void OnTestULongT();
	void OnTestULongIO();
private:
	EnumSerializeFormat GetSerializeFormat();
private:
	void OnNotifyVoidT(const TestA &a);
	void OnNotifyVoidVoid();
	unsigned long OnQueryULongT(TestB &b);
	unsigned long OnQueryULongIO(const TestA &a, TestB &b);
private:
    Ui::Dialog *ui;
	DealMsgHelper::CDealMsgHelper m_DealMsgHelper;
};

#endif // DIALOG_H
