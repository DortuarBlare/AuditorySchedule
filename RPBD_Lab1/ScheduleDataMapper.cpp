#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    connectToDB();
}

ScheduleDataMapper::~ScheduleDataMapper() {

}

int ScheduleDataMapper::connectToDB() {
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retcode < 0) return -1;
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_NTS);
    if (retcode < 0) return -2;
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (retcode < 0) return -3;

    retcode = SQLConnect(hdbc, (SQLWCHAR*)L"Test", SQL_NTS,
        (SQLWCHAR*)L"scheduler", SQL_NTS, (SQLWCHAR*)L"159357", SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
        if (retcode < 0) return -6;

        return 1;
    }
    if (retcode < 0) return -4;

    return -5;
}

int ScheduleDataMapper::disconnectFromDB() {
    retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    if (retcode < 0) return -21;
    retcode = SQLDisconnect(hdbc);
    if (retcode < 0) return -22;
    retcode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    if (retcode < 0) return -23;
    retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
    if (retcode < 0) return -24;

    return 2;
}
