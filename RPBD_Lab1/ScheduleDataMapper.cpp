#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    cout << connectToDB() << endl;
}

ScheduleDataMapper::~ScheduleDataMapper() {
    cout << disconnectFromDB() << endl;
    this->scheduleVector.clear();
    this->scheduleVector.shrink_to_fit();
}

bool ScheduleDataMapper::insert(Schedule schedule) {
    SQLINTEGER id = schedule.getId();
    SQLINTEGER auditory = schedule.getAuditory();
    SQLINTEGER week = schedule.getWeek();
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR time[20];
    SQLINTEGER testNumber = -1;

    strcpy_s((char*)group, strlen(schedule.getGroup().c_str()) + 1, schedule.getGroup().c_str());
    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());
    strcpy_s((char*)time, strlen(schedule.getTime().c_str()) + 1, schedule.getTime().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);
    retcode = SQLBindParameter(hstmt, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &testNumber, 0, NULL);
    retcode = SQLBindParameter(hstmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &testNumber, 0, NULL);
    retcode = SQLBindParameter(hstmt, 9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &testNumber, 0, NULL);
    retcode = SQLBindParameter(hstmt, 10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &testNumber, 0, NULL);
    retcode = SQLBindParameter(hstmt, 11, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &testNumber, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

void ScheduleDataMapper::createTables() {
    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
                    "id int,"
                    "auditory int,"
                    "group_ varchar(15),"
                    "week int,"
                    "day varchar(10),"
                    "time varchar(15),"
                    "id_Auditory int,"
                    "id_Group int,"
                    "id_Week int,"
                    "id_Day int,"
                    "id_Time int"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory ("
                    "id int,"
                    "auditory int"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists group_ ("
                    "id int,"
                    "group_ varchar(15)"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists week ("
                    "id int,"
                    "week int"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day ("
                    "id int,"
                    "day varchar(10)"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time ("
                    "id int,"
                    "time varchar(15)"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
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
