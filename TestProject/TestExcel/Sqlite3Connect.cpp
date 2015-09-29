#include <assert.h>
#include <string.h>
#include "Sqlite3Connect.h"

CSQLiteDataReader::CSQLiteDataReader(sqlite3_stmt* apStmt)
{
	m_pStmt = NULL;

	if (apStmt == NULL)
	{
		assert(false);
		return;
	}

	m_pStmt = apStmt;
}

CSQLiteDataReader::~CSQLiteDataReader()
{
	assert(m_pStmt == NULL);
}

// 读取一行数据
BOOL CSQLiteDataReader::Read()
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_step(m_pStmt) != SQLITE_ROW)
	{
		return FALSE;
	}

	return TRUE;
}

// 关闭Reader,读取结束后调用
void CSQLiteDataReader::Close()
{
	if (m_pStmt != NULL)
	{
		sqlite3_finalize(m_pStmt);
		m_pStmt = NULL;
	}
}

// 总的列数
int CSQLiteDataReader::ColumnCount()
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return -1;
	}

	return sqlite3_column_count(m_pStmt);
}

// 获取某列的名称 
const char* CSQLiteDataReader::GetName(int aiCol)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return NULL;
	}

	return sqlite3_column_name(m_pStmt, aiCol);
}

// 获取某列的数据类型
SQLITE_DATATYPE CSQLiteDataReader::GetDataType(int aiCol)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return SQLITE_DATATYPE_DEFAULT;
	}

	return (SQLITE_DATATYPE)sqlite3_column_type(m_pStmt, aiCol);
}

// 获取某列的值(整形)
int CSQLiteDataReader::GetIntValue(int aiCol)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return -1;
	}

	return sqlite3_column_int(m_pStmt, aiCol);
}

// 获取某列的值(长整形)
sqlite_int64 CSQLiteDataReader::GetInt64Value(int aiCol)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return -1;
	}

	return sqlite3_column_int64(m_pStmt, aiCol);
}

// 获取某列的值(浮点形)
double CSQLiteDataReader::GetDoubleValue(int aiCol)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return 0;
	}

	return sqlite3_column_double(m_pStmt, aiCol);
}

// 获取某列的值(字符串)
const unsigned char* CSQLiteDataReader::GetStringValue(int aiCol, int &aiLen)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return NULL;
	}

	aiLen = sqlite3_column_bytes(m_pStmt, aiCol);
    return sqlite3_column_text(m_pStmt, aiCol);
}

// 获取某列的值(二进制数据)
const unsigned char* CSQLiteDataReader::GetBlobValue(int aiCol, int &aiLen)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return NULL;
	}

	aiLen = sqlite3_column_bytes(m_pStmt, aiCol);
	return (const unsigned char*)sqlite3_column_blob(m_pStmt, aiCol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CSQLiteCommand::CSQLiteCommand(CSQLite* apSqlite)
{
	m_pSqlite = NULL;
	m_pStmt = NULL;

	if (apSqlite == NULL)
	{
		assert(false);
		return;
	}

	m_pSqlite = apSqlite;
}

CSQLiteCommand::CSQLiteCommand(CSQLite* apSqlite, const char* apSql)
{
	m_pSqlite = NULL;
	m_pStmt = NULL;

	if (apSqlite == NULL)
	{
		assert(false);
		return;
	}

	m_pSqlite = apSqlite;

	SetCommandText(apSql);
}

CSQLiteCommand::~CSQLiteCommand()
{
	assert(m_pSqlite == NULL);
	assert(m_pStmt == NULL);
}

// 设置命令
BOOL CSQLiteCommand::SetCommandText(const char* apSql)
{
	if (m_pSqlite == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_prepare(m_pSqlite->GetDB(), apSql, -1, &m_pStmt, NULL) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 获取参数的序号
int CSQLiteCommand::GetParamIndex(const char* apParam)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	return sqlite3_bind_parameter_index(m_pStmt, apParam);
}

// 绑定参数
BOOL CSQLiteCommand::BindParam(int aiIndex, int aiValue)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_bind_int(m_pStmt, aiIndex, aiValue) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 绑定参数
BOOL CSQLiteCommand::BindParam(int aiIndex, double adValue)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_bind_double(m_pStmt, aiIndex, adValue) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 绑定参数
BOOL CSQLiteCommand::BindParam(int aiIndex, const char* apValue)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_bind_text(m_pStmt, aiIndex, apValue, -1, SQLITE_TRANSIENT) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 绑定参数
BOOL CSQLiteCommand::BindParam(int aiIndex, const unsigned char* pbyValue, int aiLen)
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (sqlite3_bind_blob(m_pStmt, aiIndex, pbyValue, aiLen, NULL) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 执行命令
BOOL CSQLiteCommand::Excute()
{
	if (m_pStmt == NULL)
	{
		assert(false);
		return FALSE;
	}

	sqlite3_step(m_pStmt);

	return (sqlite3_reset(m_pStmt) == SQLITE_OK) ? TRUE : FALSE;
}

// 清除命令（命令不再使用时需调用该接口清除）
void CSQLiteCommand::Clear()
{
	if (m_pStmt != NULL)
	{
		sqlite3_finalize(m_pStmt);
		m_pStmt = NULL;
	}
	m_pSqlite = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CSQLite::CSQLite()
{
	m_pDB = NULL;
}

CSQLite::~CSQLite()
{
	assert(m_pDB == NULL);
}

// 打开数据库
BOOL CSQLite::Open(const char* apDBFlie)
{
	if (apDBFlie == NULL)
	{
		assert(false);
		return FALSE;
	}

    if (sqlite3_open(apDBFlie, &m_pDB) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 关闭数据库
void CSQLite::Close()
{
	if (m_pDB != NULL)
	{
		sqlite3_close(m_pDB);
		m_pDB = NULL;
	}
}

// 获取sqlite3指针
sqlite3* CSQLite::GetDB()
{
	return m_pDB;
}

// 执行非查询操作（更新或删除）
BOOL CSQLite::ExcuteNonQuery(const char* apSql)
{
	if (apSql == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

    sqlite3_stmt* pstmt = NULL;
	if (sqlite3_prepare(m_pDB, apSql, -1, &pstmt, NULL) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	sqlite3_step(pstmt);

	return (sqlite3_finalize(pstmt) == SQLITE_OK) ? TRUE : FALSE;
}

// 执行非查询操作（更新或删除）
BOOL CSQLite::ExcuteNonQuery(CSQLiteCommand* apCmd)
{
	if (apCmd == NULL)
	{
		assert(false);
		return FALSE;
	}

	return apCmd->Excute();
}

// 执行查询操作
CSQLiteDataReader CSQLite::ExcuteQuery(const char* apSql)
{
	if (apSql == NULL)
	{
		assert(false);
		return FALSE;
	}

	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

    sqlite3_stmt* pstmt = NULL;
	if (sqlite3_prepare(m_pDB, apSql, -1, &pstmt, NULL) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return CSQLiteDataReader(pstmt);
}

// 开始事务
BOOL CSQLite::BeginTransaction()
{
	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

	char* pErrMsg = NULL;
    if (sqlite3_exec(m_pDB, "BEGIN TRANSACTION;", NULL, NULL, &pErrMsg) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 提交事务
BOOL CSQLite::CommitTransaction()
{
	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

	char* pErrMsg = NULL;
	if (sqlite3_exec(m_pDB, "COMMIT TRANSACTION;;", NULL, NULL, &pErrMsg) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 回滚事务
BOOL CSQLite::RollbackTransaction()
{
	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

	char* pErrMsg = NULL;
	if (sqlite3_exec(m_pDB, "ROLLBACK  TRANSACTION;", NULL, NULL, &pErrMsg) != SQLITE_OK)
	{
		assert(false);
		return FALSE;
	}

	return TRUE;
}

// 获取上一条错误信息
const char* CSQLite::GetLastErrorMsg()
{
	if (m_pDB == NULL)
	{
		assert(false);
		return FALSE;
	}

    return sqlite3_errmsg(m_pDB);
}
