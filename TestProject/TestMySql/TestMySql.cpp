// TestMySql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include<cppconn/prepared_statement.h>
#include <mysql_driver.h>


#ifdef _DEBUG
#error release
#else
#pragma comment(lib, "mysqlcppconn.lib")
#endif


void test1()
{
	std::cout << "test1" << std::endl;

	try
	{
		sql::Driver *driver = nullptr;
		sql::Connection *con = nullptr;
		sql::Statement *stmt = nullptr;
		sql::ResultSet *res = nullptr;

		//创建连接
		driver = get_driver_instance();
		//连接mysql
		con = driver->connect("tcp://localhost:3306", "username", "password");
		//设置使用的数据库
		con->setSchema("test");

		stmt = con->createStatement();
		res = stmt->executeQuery("select id,name from user where name='jim'");

		while (res->next())
		{
			auto id = res->getInt(1);
			std::string nameutf8 = res->getString(2);
			std::cout << "id=" << id
				<< " name=" << nameutf8 << std::endl;
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}

void test2()
{
	std::cout << "test2" << std::endl;

	try
	{
		sql::Driver *driver = nullptr;
		sql::Connection *con = nullptr;
		sql::PreparedStatement *preQuery = nullptr;
		sql::ResultSet *res = nullptr;

		//创建连接
		driver = get_driver_instance();
		//连接mysql
		con = driver->connect("tcp://localhost:3306", "username", "password");
		//设置使用的数据库
		con->setSchema("test");

		preQuery = con->prepareStatement("call get_by_name(?)");
		sql::SQLString name("jim");
		preQuery->setString(1, name);
		res = preQuery->executeQuery();

		while (res->next())
		{
			auto id = res->getInt(1);
			std::string nameutf8 = res->getString(2);
			std::cout << "id=" << id
				<< " name=" << nameutf8 << std::endl;
		}
		delete res;
		delete preQuery;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}

void test3()
{
	
}

int main()
{
	test1();
	test2();
	//test3();
    return 0;
}

