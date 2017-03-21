#include "dialog.h"
#include <QApplication>
#include "SerializeHelper.h"
#include "DealMsgHelper.h"
extern bool SerializeStruct(ISerialize & pSerialize, TestMy & Value);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

	TestMy s = {1};
	std::string st;
	DealMsgHelper::PackValue(s, st, EnumSerializeFormatJson);


    return a.exec();
}
