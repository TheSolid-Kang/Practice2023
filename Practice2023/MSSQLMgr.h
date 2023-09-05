#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class MSSQLMgr
{
public:
    MSSQLMgr() {
        // ODBC API 함수 호출 전 초기화
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
        SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
        SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    }
public:
    // ODBC 관련 핸들 변수
    SQLHENV henv;//SQL 핸들 
    SQLHDBC hdbc;//SQL 핸들 
    SQLHSTMT hstmt;//SQL 핸들 Statment

};

