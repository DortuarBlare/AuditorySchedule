#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleDataMapper.h"
#include <vector>
#include <iostream>
using namespace std;

int connectToDB() {
    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retcode < 0)
        return -1;
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_NTS);
    if (retcode < 0)
        return -2;
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (retcode < 0)
        return -3;

    retcode = SQLConnect(hdbc, (SQLWCHAR*)L"Test", SQL_NTS,
        (SQLWCHAR*)L"scheduler", SQL_NTS, (SQLWCHAR*)L"159357", SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
        if (retcode < 0)
            return -6;

        return 1;
    }
    if (retcode < 0)
        return -4;

    return -5;
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<Schedule> scheduleVector;
    scheduleVector.push_back(Schedule(0, 303, "AVT-815", 5, "Monday", "12:00 - 13:30"));
    scheduleVector.push_back(Schedule(1, 303, "AVT-815", 5, "Monday", "12:00 - 13:30"));
    scheduleVector.push_back(Schedule(2, 404, "AVT-815", 4, "Tuesday", "12:00 - 13:30"));
    if (scheduleVector[0] == scheduleVector[1]) scheduleVector[0].print();
    cout << endl;
    scheduleVector[2].print();
}