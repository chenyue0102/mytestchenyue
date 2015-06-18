// TestProtocolBuffer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.pb.h"
#pragma comment(lib, "libprotobuf-lite.lib")
//#pragma comment(lib, "protoc.lib")
//#pragma comment(lib, "libprotoc.lib")
#pragma comment(lib, "libprotobuf.lib")
using namespace google;
using namespace protobuf;

struct MyStaff
{
	unsigned long staffid;
	std::string staffname;
	unsigned long stafflevel;
};

MyStaff Conver(const Test_Staff &t)
{
	MyStaff my;
	my.staffid = t.staffid();
	my.staffname = t.staffname();
	my.stafflevel = t.stafflevel();
	return my;
}
Test_Staff Conver(const MyStaff &my)
{
	Test_Staff t;
	t.set_staffid(my.staffid);
	t.set_staffname(my.staffname);
	t.set_stafflevel(my.stafflevel);
	return t;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test t;
	t.set_name("abc123");
	t.set_id(456789);
	t.add_propertyvalues(std::string("abc1234"));
	t.add_propertyvalues(std::string("def4567"));
	
	auto pstaff = t.add_staffarray();
	
	pstaff->set_staffid(1111);
	pstaff->set_stafflevel(99);
	pstaff->set_staffname("张三");
	MyStaff my = Conver(*pstaff);
	pstaff = t.add_staffarray();
	pstaff->set_staffid(22222);
	pstaff->set_stafflevel(888);
	pstaff->set_staffname("李四");
	std::string strOut;
	bool b = t.AppendToString(&strOut);

	Test r;
	b = r.ParseFromString(strOut);
	auto values = r.propertyvalues();
	auto first = values.Get(0);
	auto second = values.Get(1);

	auto firststaff = r.staffarray(0);
	auto secondstaff = r.staffarray(1);
	return 0;
}

