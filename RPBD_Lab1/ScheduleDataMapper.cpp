#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    if (connectToDB() == 1)
        createTables();
}

ScheduleDataMapper::~ScheduleDataMapper() {
    cout << disconnectFromDB() << endl;
    this->scheduleVector.clear();
    this->scheduleVector.shrink_to_fit();
}

bool ScheduleDataMapper::insert(Schedule schedule) {
    SQLINTEGER auditory = schedule.getAuditoryNumber();
    SQLINTEGER week = schedule.getWeek();
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR time[20];

    strcpy_s((char*)group, strlen(schedule.getGroup().c_str()) + 1, schedule.getGroup().c_str());
    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());
    strcpy_s((char*)time, strlen(schedule.getTime().c_str()) + 1, schedule.getTime().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO auditory(auditory)"
        "VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO group_(group_)"
        "VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO week(week)"
        "VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO day(day)"
        "VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO time(time)"
        "VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule(auditory, group_, week, day, time)"
        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

void ScheduleDataMapper::createTables() {
    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory ("
                    "id serial primary key,"
                    "auditory int unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists group_ ("
                    "id serial primary key,"
                    "group_ varchar(15) unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists week ("
                    "id serial primary key,"
                    "week int unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day ("
                    "id serial primary key,"
                    "day varchar(10) unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time ("
                    "id serial primary key,"
                    "time varchar(15) unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "auditory int references auditory(auditory) on update cascade on delete cascade,"
        "group_ varchar(15) references group_(group_) on update cascade on delete cascade,"
        "week int references week(week) on update cascade on delete cascade,"
        "day varchar(10) references day(day) on update cascade on delete cascade,"
        "time varchar(15) references time(time) on update cascade on delete cascade,"
        "id_Auditory int references auditory(id) on update cascade on delete cascade,"
        "id_Group int references group_(id) on update cascade on delete cascade,"
        "id_Week int references week(id) on update cascade on delete cascade,"
        "id_Day int references day(id) on update cascade on delete cascade,"
        "id_Time int references time(id) on update cascade on delete cascade"
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