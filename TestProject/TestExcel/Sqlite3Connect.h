// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：Sqlite3Connect.h
// 创建日期：2013-03-27
// 创建人：罗俊杰
// 文件说明：Sqlite3的连接类
// $_FILEHEADER_END ***********************************************************

#ifndef SQLITE3_CONNECT_H
#define SQLITE3_CONNECT_H

#ifndef WIN32	// Linux下
#include "Typedef.h"
#else			// Windows下
#include <windows.h>
#endif
#include "sqlite3.h"

// Sqlite3的数据类型
enum SQLITE_DATATYPE
{
	SQLITE_DATATYPE_DEFAULT = 0,				// 默认值
	SQLITE_DATATYPE_INTEGER = SQLITE_INTEGER,	// int整型
	SQLITE_DATATYPE_FLOAT = SQLITE_FLOAT,		// float
	SQLITE_DATATYPE_TEXT = SQLITE_TEXT,			// char类型字符串
	SQLITE_DATATYPE_BLOB = SQLITE_BLOB,			// 二进制
	SQLITE_DATATYPE_NULL= SQLITE_NULL,			// 空
};

class CSQLite;
class CSQLiteDataReader
{
public:
	CSQLiteDataReader(sqlite3_stmt* apStmt);
	~CSQLiteDataReader();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Read
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：读取一行数据
	// $_FUNCTION_END *********************************************************
	BOOL Read();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Close
	// 函数参数：
	// 返 回 值：
	// 函数说明：关闭Reader,读取结束后调用
	// $_FUNCTION_END *********************************************************
	void Close();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ColumnCount
	// 函数参数：
	// 返 回 值：总的列数
	// 函数说明：获取总的列数
	// $_FUNCTION_END *********************************************************
	int ColumnCount();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetName
	// 函数参数：aiCol		[输入]	列号
	// 返 回 值：某列的名称
	// 函数说明：获取某列的名称
	// $_FUNCTION_END *********************************************************
	const char* GetName(int aiCol);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDataType
	// 函数参数：aiCol		[输入]	列号
	// 返 回 值：某列的数据类型
	// 函数说明：获取某列的数据类型
	// $_FUNCTION_END *********************************************************
	SQLITE_DATATYPE GetDataType(int aiCol);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetIntValue
	// 函数参数：aiCol		[输入]	列号
	// 返 回 值：某列的值(整形)
	// 函数说明：获取某列的值(整形)
	// $_FUNCTION_END *********************************************************
	int GetIntValue(int aiCol);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetInt64Value
	// 函数参数：aiCol		[输入]	列号
	// 返 回 值：某列的值(长整形)
	// 函数说明：获取某列的值(长整形)
	// $_FUNCTION_END *********************************************************
	sqlite_int64 GetInt64Value(int aiCol);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetFloatValue
	// 函数参数：aiCol		[输入]	列号
	// 返 回 值：某列的值(浮点形)
	// 函数说明：获取某列的值(浮点形)
	// $_FUNCTION_END *********************************************************
	double GetDoubleValue(int aiCol);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetStringValue
	// 函数参数：aiCol		[输入]	列号
	//			 aiLen		[输入|输出]	数据长度
	// 返 回 值：某列的值(字符串)
	// 函数说明：获取某列的值(字符串)
	// $_FUNCTION_END *********************************************************
	const unsigned char* GetStringValue(int aiCol, int &aiLen);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetBlobValue
	// 函数参数：aiCol		[输入]		列号
	//			 aiLen		[输入|输出]	数据长度
	// 返 回 值：某列的值(二进制数据)
	// 函数说明：获取某列的值(二进制数据)
	// $_FUNCTION_END *********************************************************
	const unsigned char* GetBlobValue(int aiCol, int &aiLen);

private:
	sqlite3_stmt*	m_pStmt;
};

class CSQLiteCommand
{
public:
	CSQLiteCommand(CSQLite* apSqlite);
	CSQLiteCommand(CSQLite* apSqlite, const char* apSql);
	~CSQLiteCommand();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetCommandText
	// 函数参数：apSql		[输入]		命令
	// 返 回 值：调用是否成功
	// 函数说明：设置命令
	// $_FUNCTION_END *********************************************************
	BOOL SetCommandText(const char* apSql);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetParamIndex
	// 函数参数：apParam	[输入]		参数名称
	// 返 回 值：参数的序号
	// 函数说明：获取参数的序号
	// $_FUNCTION_END *********************************************************
	int GetParamIndex(const char* apParam);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BindParam
	// 函数参数：aiIndex		[输入]		绑定参数的序号,从1开始
	//			 apValue		[输入]		整型
	// 返 回 值：调用是否成功
	// 函数说明：绑定参数
	// $_FUNCTION_END *********************************************************
	BOOL BindParam(int aiIndex, int aiValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BindParam
	// 函数参数：aiIndex		[输入]		绑定参数的序号,从1开始
	//			 adValue		[输入]		浮点型
	// 返 回 值：调用是否成功
	// 函数说明：绑定参数
	// $_FUNCTION_END *********************************************************
	BOOL BindParam(int aiIndex, double adValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BindParam
	// 函数参数：aiIndex		[输入]		绑定参数的序号,从1开始
	//			 apValue		[输入]		字符串
	// 返 回 值：调用是否成功
	// 函数说明：绑定参数
	// $_FUNCTION_END *********************************************************
	BOOL BindParam(int aiIndex, const char* apValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BindParam
	// 函数参数：aiIndex		[输入]		绑定参数的序号,从1开始
	//			 pbyValue		[输入]		二进度数据
	//			 aiLen			[输入]		二进度数据长度
	// 返 回 值：调用是否成功
	// 函数说明：绑定参数
	// $_FUNCTION_END *********************************************************
	BOOL BindParam(int aiIndex, const unsigned char* pbyValue, int aiLen);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Excute
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：执行命令
	// $_FUNCTION_END *********************************************************
	BOOL Excute();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Clear
	// 函数参数：
	// 返 回 值：
	// 函数说明：清除命令（命令不再使用时需调用该接口清除）
	// $_FUNCTION_END *********************************************************
	void Clear();

private:
	CSQLite*		m_pSqlite;
	sqlite3_stmt*	m_pStmt;
};

class CSQLite
{
public:
	CSQLite();
	~CSQLite();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Open
	// 函数参数：apDBFlie		[输入]	DB文件路径
	// 返 回 值：调用是否成功
	// 函数说明：打开数据库
	// $_FUNCTION_END *********************************************************
	BOOL Open(const char* apDBFlie);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Close
	// 函数参数：
	// 返 回 值：
	// 函数说明：关闭数据库
	// $_FUNCTION_END *********************************************************
	void Close();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDB
	// 函数参数：
	// 返 回 值：sqlite3指针
	// 函数说明：获取sqlite3指针
	// $_FUNCTION_END *********************************************************
	sqlite3* GetDB();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ExcuteNonQuery
	// 函数参数：apSql		[输入]	命令
	// 返 回 值：调用是否成功
	// 函数说明：执行非查询操作（更新或删除）
	// $_FUNCTION_END *********************************************************
	BOOL ExcuteNonQuery(const char* apSql);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ExcuteNonQuery
	// 函数参数：apCmd		[输入]	命令
	// 返 回 值：调用是否成功
	// 函数说明：执行非查询操作（更新或删除）
	// $_FUNCTION_END *********************************************************
	BOOL ExcuteNonQuery(CSQLiteCommand* apCmd);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ExcuteQuery
	// 函数参数：apSql		[输入]	命令
	// 返 回 值：数据读取对象
	// 函数说明：执行查询操作
	// $_FUNCTION_END *********************************************************
	CSQLiteDataReader ExcuteQuery(const char* apSql);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginTransaction
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：开始事务
	// $_FUNCTION_END *********************************************************
	BOOL BeginTransaction();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：CommitTransaction
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：提交事务
	// $_FUNCTION_END *********************************************************
	BOOL CommitTransaction();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：RollbackTransaction
	// 函数参数：
	// 返 回 值：调用是否成功
	// 函数说明：回滚事务
	// $_FUNCTION_END *********************************************************
	BOOL RollbackTransaction();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetLastErrorMsg
	// 函数参数：
	// 返 回 值：上一条错误信息
	// 函数说明：获取上一条错误信息
	// $_FUNCTION_END *********************************************************
	const char* GetLastErrorMsg();

private:
	sqlite3* m_pDB;
};

#endif
