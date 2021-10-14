#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    if (connectToDB() == 1)
        createTables();
}

ScheduleDataMapper::~ScheduleDataMapper() {
    disconnectFromDB();
    this->scheduleVector.clear();
    this->scheduleVector.shrink_to_fit();
}

bool ScheduleDataMapper::insert(Schedule schedule) {
    SQLINTEGER auditory = schedule.getAuditoryNumber();
    SQLWCHAR week[20];
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR time[20];

    strcpy_s((char*)week, strlen(schedule.getWeek().c_str()) + 1, schedule.getWeek().c_str());
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

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, week, 0, NULL);
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
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule(auditory, group_, week, day, time)"
        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

void ScheduleDataMapper::showAll() {
    int auditory = 0;
    char week[20] = "";
    char group[20] = "";
    char day[20] = "";
    char time[20] = "";

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"select auditory, group_, week, day, time from schedule order by id;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, group, 20, NULL);
    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, week, 20, NULL);
    retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, day, 20, NULL);
    retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, time, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            cout << "Порядковый номер: " << i + 1 << endl;
            cout << "Аудитория:\t" << auditory << endl;

            cout << "Группа:\t\t";
            for(int i = 0; i < 20; i++)
                 cout << group[i];
            cout << endl;

            cout << "Недели:\t\t";
            for (int i = 0; i < 20; i++)
                cout << week[i];
            cout << endl;

            cout << "День:\t\t";
            for (int i = 0; i < 20; i++)
                 cout << day[i];
            cout << endl;

            cout << "Время:\t\t";
            for (int i = 0; i < 20; i++)
                 cout << time[i];
            cout << endl << endl;

            for (int i = 0; i < 20; i++) {
                group[i] = ' ';
                week[i] = ' ';
                day[i] = ' ';
                time[i] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
}

void ScheduleDataMapper::showByGroup(string choice) {
    SQLWCHAR group_[20];
    int auditory = 0;
    char week[20] = "";
    char group[20] = "";
    char day[20] = "";
    char time[20] = "";

    strcpy_s((char*)group_, strlen(choice.c_str()) + 1, choice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group_, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"select auditory, group_, week, day, time from schedule where group_ = ?;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, group, 20, NULL);
    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, week, 20, NULL);
    retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, day, 20, NULL);
    retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, time, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            cout << "Порядковый номер: " << i + 1 << endl;
            cout << "Аудитория:\t" << auditory << endl;

            cout << "Группа:\t\t";
            for (int i = 0; i < 20; i++)
                cout << group[i];
            cout << endl;

            cout << "Недели:\t\t";
            for (int i = 0; i < 20; i++)
                cout << week[i];
            cout << endl;

            cout << "День:\t\t";
            for (int i = 0; i < 20; i++)
                cout << day[i];
            cout << endl;

            cout << "Время:\t\t";
            for (int i = 0; i < 20; i++)
                cout << time[i];
            cout << endl << endl;

            for (int i = 0; i < 20; i++) {
                group[i] = ' ';
                week[i] = ' ';
                day[i] = ' ';
                time[i] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
}

//void ScheduleDataMapper::showTable() {
//    int auditory = 0;
//    char week[20] = "";
//    char group[20] = "";
//    char day[20] = "";
//    char time[20] = "";
//    char forComparison[20] = "";
//    vector<string> allGroups;
//
//    retcode = SQLExecDirect(hstmt,
//        (SQLWCHAR*)L"select group_ from group_;", SQL_NTS);
//    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, forComparison, 20, NULL);
//
//    for (int i = 0; ; i++) {
//        retcode = SQLFetch(hstmt);
//        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
//            cout << "Error" << endl;
//        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
//            allGroups.push_back(string(forComparison));
//            for (int i = 0; i < 20; i++)
//                forComparison[i] = ' ';
//        }
//        else break;
//    }
//    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
//
//    retcode = SQLExecDirect(hstmt, 
//        (SQLWCHAR*)L"select auditory, group_, week, day, time from schedule;", SQL_NTS);
//    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);
//    retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, group, 20, NULL);
//    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, week, 20, NULL);
//    retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, day, 20, NULL);
//    retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, time, 20, NULL);
//
//    
//    for (int i = 0; ; i++) {
//        retcode = SQLFetch(hstmt);
//        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
//            cout << "Error" << endl;
//        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
//            for (int i = 0; i < allGroups.size(); i++) {
//                if (equal(group, group, allGroups[i].c_str())) {
//                    cout << allGroups[i] << endl;
//                    for (int i = 0; i < 120; i++) cout << '=';
//                    cout << endl << "| Время       | Недели     | Номер аудитории     |";
//                    for (int i = 0; i < 68; i++) cout << ' ';
//                    cout << '|' << endl;
//                    for (int i = 0; i < 120; i++) cout << '=';
//
//                    break;
//                }
//            }
//        }
//        else break;
//    }
//
//    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
//}

bool ScheduleDataMapper::edit(int number, Schedule schedule) {
    SQLINTEGER auditory = schedule.getAuditoryNumber();
    SQLWCHAR week[20];
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR time[20];
    SQLINTEGER editNumber = number;

    strcpy_s((char*)week, strlen(schedule.getWeek().c_str()) + 1, schedule.getWeek().c_str());
    strcpy_s((char*)group, strlen(schedule.getGroup().c_str()) + 1, schedule.getGroup().c_str());
    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());
    strcpy_s((char*)time, strlen(schedule.getTime().c_str()) + 1, schedule.getTime().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);
    retcode = SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
    
    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"UPDATE schedule SET auditory = ?, group_ = ?, week = ?, day = ?, time = ? "
        "WHERE id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

bool ScheduleDataMapper::remove(int number) {
    SQLINTEGER editNumber = number;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
    
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"DELETE FROM schedule WHERE id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
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
                    "week varchar(15) unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day ("
                    "id serial primary key,"
                    "day varchar(15) unique"
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
        "week varchar(15) references week(week) on update cascade on delete cascade,"
        "day varchar(15) references day(day) on update cascade on delete cascade,"
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

    retcode = SQLConnect(hdbc, (SQLWCHAR*)L"Schedule", SQL_NTS,
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