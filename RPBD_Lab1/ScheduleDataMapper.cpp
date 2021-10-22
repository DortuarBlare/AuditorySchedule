#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    if (connectToDB() == 1)
        createTables();
}

ScheduleDataMapper::~ScheduleDataMapper() {
    disconnectFromDB();
    //this->scheduleVector.clear();
    //this->scheduleVector.shrink_to_fit();
}

bool ScheduleDataMapper::insert(Schedule schedule) {
    SQLINTEGER auditory = schedule.getAuditoryNumber();
    SQLINTEGER week[20];
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR startTime[20];
    SQLWCHAR endTime[20];
    string _startTime, _endTime;
    bool foundStartTime = false;

    strcpy_s((char*)group, strlen(schedule.getGroup().c_str()) + 1, schedule.getGroup().c_str());
    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());

    for (int i = 0; i < schedule.getTime().length(); i++) {
        if (!foundStartTime && schedule.getTime()[i] != ' ' &&
            schedule.getTime()[i] != '-' && schedule.getTime()[i] != '\0') {
            _startTime += schedule.getTime()[i];
            if (schedule.getTime()[i + 1] != ' ' &&
                schedule.getTime()[i + 1] != '-' && schedule.getTime()[i + 1] != '\0')
                foundStartTime = true;
        }
        else if (schedule.getTime()[i] != ' ' &&
            schedule.getTime()[i] != '-' && schedule.getTime()[i] != '\0') {
            _endTime += schedule.getTime()[i];
        }
        else break;
    }

    strcpy_s((char*)startTime, strlen(_startTime.c_str()) + 1, _startTime.c_str());
    strcpy_s((char*)endTime, strlen(_endTime.c_str()) + 1, _endTime.c_str());

    int amountOfWeeks = 0;
    string temp;
    for (int i = 0, j = 0; i < schedule.getWeek().size(); i++) {
        if (schedule.getWeek()[i] != ' ' &&
            schedule.getWeek()[i] != '-' && schedule.getWeek()[i] != '\0')
            temp += schedule.getWeek()[i];
        else {
            week[j++] = atoi(temp.c_str());
            temp.clear();
        }

        if (i == schedule.getWeek().size() - 1 && !temp.empty()) {
            week[amountOfWeeks++] = atoi(temp.c_str());
            temp.clear();
        }
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory(auditory) VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO group_(group_) VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    for (int i = 0; i < amountOfWeeks; i++) {
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week[i], 0, NULL);
        retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO week(week) VALUES (?);", SQL_NTS);
        retcode = SQLExecute(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day(day) VALUES (?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, startTime, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, endTime, 0, NULL);
    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO time(start_time, end_time) VALUES (?, ?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    /*retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);*/

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule(auditory, group_, week, day, time)"
        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

//void ScheduleDataMapper::weekInsert(string weeks) {
//    SQLINTEGER week[20];
//
//    string temp;
//    int amountOfWeeks = 0;
//    for (int i = 0; i < weeks.size(); i++) {
//        if (weeks[i] != ' ' &&
//            weeks[i] != '-' && weeks[i] != '\0')
//            temp += weeks[i];
//        else {
//            week[amountOfWeeks++] = atoi(temp.c_str());
//            temp.clear();
//        }
//
//        if (i == weeks.size() - 1 && !temp.empty()) {
//            week[amountOfWeeks++] = atoi(temp.c_str());
//            temp.clear();
//        }
//    }
//
//    for (int i = 0; i < amountOfWeeks; i++) {
//        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week[i], 0, NULL);
//        retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO week(week) VALUES (?);", SQL_NTS);
//        retcode = SQLExecute(hstmt);
//        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
//    }
//}

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
            for(int j = 0; j < 20; j++)
                 cout << group[j];
            cout << endl;

            cout << "Недели:\t\t";
            for (int j = 0; j < 20; j++)
                cout << week[j];
            cout << endl;

            cout << "День:\t\t";
            for (int j = 0; j < 20; j++)
                 cout << day[j];
            cout << endl;

            cout << "Время:\t\t";
            for (int j = 0; j < 20; j++)
                 cout << time[j];
            cout << endl << endl;

            for (int j = 0; j < 20; j++) {
                group[j] = ' ';
                week[j] = ' ';
                day[j] = ' ';
                time[j] = ' ';
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
            for (int j = 0; j < 20; j++)
                cout << group[j];
            cout << endl;

            cout << "Недели:\t\t";
            for (int j = 0; j < 20; j++)
                cout << week[j];
            cout << endl;

            cout << "День:\t\t";
            for (int j = 0; j < 20; j++)
                cout << day[j];
            cout << endl;

            cout << "Время:\t\t";
            for (int j = 0; j < 20; j++)
                cout << time[j];
            cout << endl << endl;

            for (int j = 0; j < 20; j++) {
                group[j] = ' ';
                week[j] = ' ';
                day[j] = ' ';
                time[j] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
}

bool ScheduleDataMapper::edit(int number, Schedule schedule) {
    remove(number);
    insert(schedule);
    return true;
}

bool ScheduleDataMapper::remove(int number) {
    int id = 0;
    vector<int> idList;

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from schedule order by id;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idList.push_back(id);
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    if (number < 1 || number > idList.size())
        return false;

    SQLINTEGER removeNumber = idList[number - 1];
    idList.clear();
    idList.shrink_to_fit();

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"DELETE FROM schedule WHERE id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}

void ScheduleDataMapper::findFreeAuditoryByTime(int auditoryChoice, string timeChoice) {
    SQLINTEGER auditory = auditoryChoice;
    SQLWCHAR time[20];
    char week[20] = "";
    char day[20] = "";
    vector<vector<string>> weeksAndDays;

    strcpy_s((char*)time, strlen(timeChoice.c_str()) + 1, timeChoice.c_str());

    for (int i = 0; i < 18; i++) {
        weeksAndDays.push_back(vector<string>());
        weeksAndDays[i].push_back("Понедельник");
        weeksAndDays[i].push_back("Вторник");
        weeksAndDays[i].push_back("Среда");
        weeksAndDays[i].push_back("Четверг");
        weeksAndDays[i].push_back("Пятница");
        weeksAndDays[i].push_back("Суббота");
        weeksAndDays[i].push_back("Воскресенье");
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, time, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"select week, day, time from schedule where auditory = ? and time = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, week, 20, NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (string(week) == "Четные" || string(week) == "Ч") {
                for (int j = 1; j < 18; j += 2) {
                    auto iterator = weeksAndDays[j].cbegin();
                    for (int k = 0; k < weeksAndDays[i].size(); k++) {
                        if (weeksAndDays[j][k] == string(day)) {
                            weeksAndDays[j].erase(iterator + k);
                            break;
                        }
                    }
                }
            }
            else if (string(week) == "Нечетные" || string(week) == "Н") {
                for (int j = 0; j < 18; j += 2) {
                    auto iterator = weeksAndDays[j].cbegin();
                    for (int k = 0; k < weeksAndDays[i].size(); k++) {
                        if (weeksAndDays[j][k] == string(day)) {
                            weeksAndDays[j].erase(iterator + k);
                            break;
                        }
                    }
                }
            }
            else {
                string tempNumber = "";
                int tempIntNumber;
                for (int j = 0; j < 20; j++) {
                    if (week[j] != ' ' && week[j] != '-' && week[j] != '\0')
                        tempNumber += week[j];
                    else {
                        tempIntNumber = atoi(tempNumber.c_str());
                        if (tempIntNumber > 0 && tempIntNumber <= 18) {
                            auto iterator = weeksAndDays[tempIntNumber - 1].cbegin();
                            for (int k = 0; k < weeksAndDays[tempIntNumber - 1].size(); k++) {
                                if (weeksAndDays[tempIntNumber - 1][k] == string(day)) {
                                    weeksAndDays[tempIntNumber - 1].erase(iterator + k);
                                    break;
                                }
                            }
                        }
                        tempNumber = "";
                    }
                }
            }

            for (int j = 0; j < 20; j++) {
                week[i] = ' ';
                day[i] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    cout << "В заданное время аудитория свободна:" << endl;
    for (int i = 0; i < 18; i++) {
        if (i < 9) cout << ' ';
        cout << i + 1 << " неделя:\t ";
        for (int j = 0; j < weeksAndDays[i].size(); j++)
            cout << weeksAndDays[i][j] << ", ";
        cout << endl;
    }
    cout << endl;
    
    weeksAndDays.clear();
    weeksAndDays.shrink_to_fit();
}

void ScheduleDataMapper::findFreeAuditoryByNumberOfHours(int auditoryChoice, int numberOfHoursChoice, int weekNumber) {
    SQLINTEGER auditory = auditoryChoice;
    char week[20] = "";
    char day[20] = "";
    char time[20] = "";
    vector<vector<string>> daysAndTime;
    double amountOfClasses = ceil(double(numberOfHoursChoice * 60) / 90);
    double amountOfClassesOnEachDay = 0;
    double temp = ceil(double(amountOfClasses) / 7);

    for (int i = 0; i < 7; i++) {
        daysAndTime.push_back(vector<string>());
        daysAndTime[i].push_back("8:30-10:00");
        daysAndTime[i].push_back("10:15-11:45");
        daysAndTime[i].push_back("12:00-13:30");
        daysAndTime[i].push_back("14:00-15:30");
        daysAndTime[i].push_back("15:45-17:15");
        daysAndTime[i].push_back("17:30-19:00");
        daysAndTime[i].push_back("19:15-20:45");
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"select week, day, time from schedule where auditory = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, week, 20, NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 20, NULL);
    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, time, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (string(week) == "Четные" || string(week) == "Ч") {
                int dayIndex = dayToIndex(string(day));
                for (int j = 1; j < 18; j += 2) {
                    auto iterator = daysAndTime[dayIndex].cbegin();
                    for (int k = 0; k < daysAndTime[dayIndex].size(); k++) {
                        if (daysAndTime[dayIndex][k] == string(time) && j + 1 == weekNumber) {
                            daysAndTime[dayIndex].erase(iterator + k);
                            break;
                        }
                    }
                }
            }
            else if (string(week) == "Нечетные" || string(week) == "Н") {
                int dayIndex = dayToIndex(string(day));
                for (int j = 0; j < 18; j += 2) {
                    auto iterator = daysAndTime[dayIndex].cbegin();
                    for (int k = 0; k < daysAndTime[dayIndex].size(); k++) {
                        if (daysAndTime[dayIndex][k] == string(time) && j + 1 == weekNumber) {
                            daysAndTime[dayIndex].erase(iterator + k);
                            break;
                        }
                    }
                }
            }
            else {
                string tempNumber = "";
                int tempWeekNumber, dayIndex;
                for (int j = 0; j < 20; j++) {
                    if (week[j] != ' ' && week[j] != '-' && week[j] != '\0')
                        tempNumber += week[j];
                    else {
                        tempWeekNumber = atoi(tempNumber.c_str());
                        dayIndex = dayToIndex(string(day));

                        if (tempWeekNumber > 0 && tempWeekNumber <= 18) {
                            auto iterator = daysAndTime[dayIndex].cbegin();
                            for (int k = 0; k < daysAndTime[dayIndex].size(); k++) {
                                if (daysAndTime[dayIndex][k] == string(time) && tempWeekNumber == weekNumber) {
                                    daysAndTime[dayIndex].erase(iterator + k);
                                    break;
                                }
                            }
                        }
                        tempNumber = "";
                    }
                }
            }

            for (int j = 0; j < 20; j++) {
                week[i] = ' ';
                day[i] = ' ';
                time[i] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    cout << endl << "На " << weekNumber << " неделе " << auditoryChoice << " аудитория свободна:" << endl;
    for (int i = 0; i < 7; i++) {
        amountOfClassesOnEachDay = amountOfClassesOnEachDay == 0 ? temp : temp + amountOfClassesOnEachDay;
        if (i == 0)      cout << "Понедельник:\t ";
        else if (i == 1) cout << "    Вторник:\t ";
        else if (i == 2) cout << "      Среда:\t ";
        else if (i == 3) cout << "    Четверг:\t ";
        else if (i == 4) cout << "    Пятница:\t ";
        else if (i == 5) cout << "    Суббота:\t ";
        else if (i == 6) cout << "Воскресенье:\t ";
        for (int j = 0; j < daysAndTime[i].size(); j++) {
            cout << daysAndTime[i][j];
            amountOfClasses--;
            amountOfClassesOnEachDay--;
            if (amountOfClasses == 0 || amountOfClassesOnEachDay == 0) break;
            cout << ", ";
        }
        cout << endl;
        if (amountOfClasses == 0) break;
    }
    cout << endl;

    daysAndTime.clear();
    daysAndTime.shrink_to_fit();
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
                    "day varchar(15) unique"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time ("
                    "id serial primary key,"
                    "start_time time,"
                    "end_time time,"
                    "unique(start_time, end_time)"
                    "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
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
        (SQLWCHAR*)L"Scheduler", SQL_NTS, (SQLWCHAR*)L"159357", SQL_NTS);

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

int ScheduleDataMapper::dayToIndex(string day) {
    if (day == "Понедельник") return 0;
    else if (day == "Вторник") return 1;
    else if (day == "Среда") return 2;
    else if (day == "Четверг") return 3;
    else if (day == "Пятница") return 4;
    else if (day == "Суббота") return 5;
    else if (day == "Воскресенье") return 6;
    return 0;
}