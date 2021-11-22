#include "ScheduleDataMapper.h"

ScheduleDataMapper::ScheduleDataMapper() {
    if (connectToDB() == 1)
        createTables();
}

ScheduleDataMapper::~ScheduleDataMapper() {
    disconnectFromDB();
}

bool ScheduleDataMapper::insertSchedule(Schedule schedule) {
    SQLWCHAR auditory[20];
    SQLINTEGER week = schedule.getWeek();
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR startTime[20];
    SQLWCHAR endTime[20];
    bool foundStartTime = false;
    SQLINTEGER id_auditory = 0, id_group = 0, id_week = 0, id_day = 0, id_time = 0;

    strcpy_s((char*)auditory, strlen(schedule.getAuditory().getAuditoryName().c_str()) + 1,
        schedule.getAuditory().getAuditoryName().c_str());
    strcpy_s((char*)group, strlen(schedule.getGroup().getGroupName().c_str()) + 1,
        schedule.getGroup().getGroupName().c_str());
    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());

    strcpy_s((char*)startTime, strlen(schedule.getTime().getStartTime().c_str()) + 1,
        schedule.getTime().getStartTime().c_str());
    strcpy_s((char*)endTime, strlen(schedule.getTime().getEndTime().c_str()) + 1,
        schedule.getTime().getEndTime().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO auditory(auditory) VALUES (?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO group_(group_) VALUES (?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    // Запросы для получения id каждого поля
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM auditory WHERE auditory = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM group_ WHERE group_ = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM day WHERE day = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, startTime, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, endTime, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM time_ WHERE start_time = ? AND end_time = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    /*for (int i = 0; i < amountOfWeeks; i++) {
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_auditory, 0, NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &weeks[i], 0, NULL);
        retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
        retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
        retcode = SQLExecDirect(hstmt,
            (SQLWCHAR*)L"INSERT INTO schedule(id_auditory, id_group, week, id_day, id_time)"
                        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
        if (retcode < 0) {
            retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
            return false;
        }
    }*/
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule(id_auditory, id_group, week, id_day, id_time)"
        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
    if (retcode < 0) {
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        return false;
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    return true;
}

bool ScheduleDataMapper::insertAuditory(string auditoryChoice) {
    char auditory[20] = "";

    strcpy_s((char*)auditory, strlen(auditoryChoice.c_str()) + 1, auditoryChoice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO auditory(auditory) VALUES(?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    if (retcode < 0)
        return false;
    return true;
}

bool ScheduleDataMapper::insertGroup(string groupChoice) {
    char group[20] = "";

    strcpy_s((char*)group, strlen(groupChoice.c_str()) + 1, groupChoice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO group_(group_) VALUES(?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    if (retcode < 0)
        return false;
    return true;
}

void ScheduleDataMapper::showAll() {
    char auditory[20] = "";
    int week = 0;
    char group[20] = "";
    char day[20] = "";
    char start_time[20] = "";
    char end_time[20] = "";
    int id_auditory = 0, id_group = 0, id_day = 0, id_time = 0;
    int temp_id_auditory = 0, temp_id_group = 0, temp_id_day = 0, temp_id_time = 0;

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, group_, week, day, start_time, end_time, "
                    "id_auditory, id_group, id_day, id_time FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "ORDER BY auditory, group_, day, week;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1,  SQL_C_CHAR,      auditory,      20,                  NULL);
    retcode = SQLBindCol(hstmt, 2,  SQL_C_CHAR,      group,         20,                  NULL);
    retcode = SQLBindCol(hstmt, 3,  SQL_C_SLONG,     &week,         sizeof(week),        NULL);
    retcode = SQLBindCol(hstmt, 4,  SQL_C_CHAR,      day,           20,                  NULL);
    retcode = SQLBindCol(hstmt, 5,  SQL_C_CHAR,      &start_time,   20,                  NULL);
    retcode = SQLBindCol(hstmt, 6,  SQL_C_CHAR,      &end_time,     20,                  NULL);
    retcode = SQLBindCol(hstmt, 7,  SQL_C_SLONG,     &id_auditory,  sizeof(id_auditory), NULL);
    retcode = SQLBindCol(hstmt, 8,  SQL_C_SLONG,     &id_group,     sizeof(id_group),    NULL);
    retcode = SQLBindCol(hstmt, 9,  SQL_C_SLONG,     &id_day,       sizeof(id_day),      NULL);
    retcode = SQLBindCol(hstmt, 10, SQL_C_SLONG,     &id_time,      sizeof(id_time),     NULL);

    for (int i = 0, j = 1; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (id_auditory != temp_id_auditory || id_group != temp_id_group ||
                id_day      != temp_id_day      || id_time  != temp_id_time) {
                temp_id_auditory = id_auditory;
                temp_id_group = id_group;
                temp_id_day = id_day;
                temp_id_time = id_time;

                cout << endl << endl;
                cout << "Порядковый номер расписания: " << j++ << endl;
                cout << "Аудитория:\t" << string(auditory) << endl;

                cout << "Группа:\t\t" << string(group) << endl;

                cout << "День:\t\t" << string(day) << endl;

                string tempStartTime(start_time);
                string tempEndTime(end_time);
                tempStartTime.resize(tempStartTime.size() - 3);
                tempEndTime.resize(tempEndTime.size() - 3);
                cout << "Время:\t\t" << tempStartTime << " - " << tempEndTime << endl;

                cout << "Недели:\t\t" << week << ' ';
            }
            else cout << week << ' ';

            for (int j = 0; j < 20; j++) {
                auditory[j] = ' ';
                group[j] = ' ';
                day[j] = ' ';
                start_time[j] = ' ';
                end_time[j] = ' ';
            }
        }
        else {
            cout << endl;
            break;
        }
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
}

void ScheduleDataMapper::showByGroup(string choice) {
    char auditory[20] = "";
    int week = 0;
    char group[20] = "";
    char day[20] = "";
    char start_time[20] = "";
    char end_time[20] = "";
    int id_auditory = 0, id_group = 0, id_day = 0, id_time = 0;
    int temp_id_auditory = 0, temp_id_group = 0, temp_id_day = 0, temp_id_time = 0;

    strcpy_s((char*)group, strlen(choice.c_str()) + 1, choice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, group_, week, day, start_time, end_time, "
                    "id_auditory, id_group, id_day, id_time FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "WHERE group_ = ? "
                    "ORDER BY auditory, day, week", SQL_NTS);

    retcode = SQLBindCol(hstmt, 1,  SQL_C_CHAR,  auditory,     20,                  NULL);
    retcode = SQLBindCol(hstmt, 2,  SQL_C_CHAR,  group,        20,                  NULL);
    retcode = SQLBindCol(hstmt, 3,  SQL_C_SLONG, &week,        sizeof(week),        NULL);
    retcode = SQLBindCol(hstmt, 4,  SQL_C_CHAR,  day,          20,                  NULL);
    retcode = SQLBindCol(hstmt, 5,  SQL_C_CHAR,  &start_time,  20,                  NULL);
    retcode = SQLBindCol(hstmt, 6,  SQL_C_CHAR,  &end_time,    20,                  NULL);
    retcode = SQLBindCol(hstmt, 7,  SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
    retcode = SQLBindCol(hstmt, 8,  SQL_C_SLONG, &id_group,    sizeof(id_group),    NULL);
    retcode = SQLBindCol(hstmt, 9,  SQL_C_SLONG, &id_day,      sizeof(id_day),      NULL);
    retcode = SQLBindCol(hstmt, 10, SQL_C_SLONG, &id_time,     sizeof(id_time),     NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (id_auditory != temp_id_auditory || id_group != temp_id_group ||
                id_day != temp_id_day || id_time != temp_id_time) {
                temp_id_auditory = id_auditory;
                temp_id_group = id_group;
                temp_id_day = id_day;
                temp_id_time = id_time;

                cout << endl << endl;
                cout << "Аудитория:\t" << string(auditory) << endl;

                cout << "Группа:\t\t" << string(group) << endl;

                cout << "День:\t\t" << string(day) << endl;

                string tempStartTime(start_time);
                string tempEndTime(end_time);
                tempStartTime.resize(tempStartTime.size() - 3);
                tempEndTime.resize(tempEndTime.size() - 3);
                cout << "Время:\t\t" << tempStartTime << " - " << tempEndTime << endl;

                cout << "Недели:\t\t" << week << ' ';
            }
            else cout << week << ' ';

            for (int j = 0; j < 20; j++) {
                auditory[j] = ' ';
                group[j] = ' ';
                day[j] = ' ';
                start_time[j] = ' ';
                end_time[j] = ' ';
            }
        }
        else {
            cout << endl;
            break;
        }
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
}

void ScheduleDataMapper::showAllGroups() {
    char group[20] = "";    

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT group_ FROM group_ ORDER BY group_;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, group, 20, NULL);
    cout << endl << "Все группы: " << endl;

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            cout << string(group) << endl;

            for (int j = 0; j < 20; j++) 
                group[j] = ' ';
        }
        else break;
    }
    cout << endl;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
}

void ScheduleDataMapper::showAllAuditories() {
    char auditory[20] = "";

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT auditory FROM auditory ORDER BY auditory;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, auditory, 20, NULL);
    cout << endl << "Все аудитории: " << endl;

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            cout << string(auditory) << endl;

            for (int j = 0; j < 20; j++)
                auditory[j] = ' ';
        }
        else break;
    }
    cout << endl;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
}

bool ScheduleDataMapper::fullEdit(int number, Schedule schedule) {
    if (removeSchedule(number))
        if (insertSchedule(schedule))
            return true;
    return false;
}

bool ScheduleDataMapper::edit(int number, Schedule schedule) {
    SQLWCHAR auditory[20];
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR startTime[20];
    SQLWCHAR endTime[20];
    string _startTime, _endTime;
    bool foundStartTime = false;
    SQLINTEGER id = 0, id_auditory = 0, id_group = 0, id_day = 0, id_time = 0;
    SQLINTEGER temp_id_auditory = 0, temp_id_group = 0, temp_id_day = 0, temp_id_time = 0;
    int fieldToEdit = 0;
    bool firstSchedule = true;
    vector<vector<int>> idList;

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, group_, week, day, start_time, end_time, "
                    "schedule.id, id_auditory, id_group, id_day, id_time FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "ORDER BY auditory, group_, day, week;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 7,  SQL_C_SLONG, &id,          sizeof(id),          NULL);
    retcode = SQLBindCol(hstmt, 8,  SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
    retcode = SQLBindCol(hstmt, 9,  SQL_C_SLONG, &id_group,    sizeof(id_group),    NULL);
    retcode = SQLBindCol(hstmt, 10, SQL_C_SLONG, &id_day,      sizeof(id_day),      NULL);
    retcode = SQLBindCol(hstmt, 11, SQL_C_SLONG, &id_time,     sizeof(id_time),     NULL);

    // Составляем список id для каждого расписания
    for (int i = 0, j = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (id_auditory != temp_id_auditory || id_group != temp_id_group ||
                id_day != temp_id_day || id_time != temp_id_time) {
                temp_id_auditory = id_auditory;
                temp_id_group = id_group;
                temp_id_day = id_day;
                temp_id_time = id_time;

                idList.push_back(vector<int>());
                if (firstSchedule) {
                    idList[j].push_back(id);
                    firstSchedule = false;
                }
                else idList[++j].push_back(id);
            }
            else idList[j].push_back(id);
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

    if (number < 1 || number > idList.size())
        return false;

    if (schedule.getAuditory().getAuditoryName() != "...") {
        fieldToEdit = 1;
        strcpy_s((char*)auditory, strlen(schedule.getAuditory().getAuditoryName().c_str()) + 1, schedule.getAuditory().getAuditoryName().c_str());

        // Вставляем аудиторию в таблицу аудиторий, если её нет
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO auditory(auditory) VALUES(?);", SQL_NTS);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT id FROM auditory WHERE auditory = ?; ", SQL_NTS);
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
        retcode = SQLFetch(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    }
    else if (schedule.getGroup().getGroupName() != "...") {
        fieldToEdit = 2;
        strcpy_s((char*)group, strlen(schedule.getGroup().getGroupName().c_str()) + 1, 
            schedule.getGroup().getGroupName().c_str());

        // Вставляем группу в таблицу групп, если её нет
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO group_(group_) VALUES(?);", SQL_NTS);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT id FROM group_ WHERE group_ = ?; ", SQL_NTS);
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    }
    else if (schedule.getDay() != "...") {
        fieldToEdit = 4;
        strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT id FROM day WHERE day = ?; ", SQL_NTS);
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
        retcode = SQLFetch(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    }
    /*else if (schedule.getTime() != "...") {
        fieldToEdit = 5;
        for (int i = 0; i < schedule.getTime().length(); i++) {
            if (!foundStartTime && schedule.getTime()[i] != ' ' &&
                schedule.getTime()[i] != '-' && schedule.getTime()[i] != '\0') {
                _startTime += schedule.getTime()[i];
                if (schedule.getTime()[i + 1] == ' ' ||
                    schedule.getTime()[i + 1] == '-' || schedule.getTime()[i + 1] == '\0')
                    foundStartTime = true;
            }
            else if (schedule.getTime()[i] != ' ' &&
                schedule.getTime()[i] != '-' && schedule.getTime()[i] != '\0') {
                _endTime += schedule.getTime()[i];
            }
        }
        strcpy_s((char*)startTime, strlen(_startTime.c_str()) + 1, _startTime.c_str());
        strcpy_s((char*)endTime, strlen(_endTime.c_str()) + 1, _endTime.c_str());
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, startTime, 0, NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, endTime, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from time_ where start_time = ? and end_time = ?; ", SQL_NTS);
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
        retcode = SQLFetch(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    }*/

    for (int i = 0; i < idList[number - 1].size(); i++) {
        SQLINTEGER editNumber = idList[number - 1][i];
        if (fieldToEdit == 1) {
            retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_auditory, 0, NULL);
            retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
            retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE schedule SET id_auditory = ? WHERE id = ?;", SQL_NTS);
        }
        else if (fieldToEdit == 2) {
            retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
            retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
            retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE schedule SET id_group = ? WHERE id = ?;", SQL_NTS);
        }
        else if (fieldToEdit == 4) {
            retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
            retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
            retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE schedule SET id_day = ? WHERE id = ?;", SQL_NTS);
        }
        else if (fieldToEdit == 5) {
            retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
            retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);
            retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE schedule SET id_time = ? WHERE id = ?;", SQL_NTS);
        }
        if (retcode < 0) {
            idList.clear();
            idList.shrink_to_fit();
            return false;
        }
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    }

    idList.clear();
    idList.shrink_to_fit();
    return true;
}

bool ScheduleDataMapper::editAuditory(string oldAuditory, string newAuditory) {
    SQLWCHAR _oldAuditory[20];
    SQLWCHAR _newAuditory[20];

    strcpy_s((char*)_newAuditory, strlen(newAuditory.c_str()) + 1, newAuditory.c_str());
    strcpy_s((char*)_oldAuditory, strlen(oldAuditory.c_str()) + 1, oldAuditory.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, _newAuditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, _oldAuditory, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE auditory SET auditory = ? WHERE auditory = ?;", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;
}

bool ScheduleDataMapper::editGroup(string oldGroup, string newGroup) {
    SQLWCHAR _oldGroup[20];
    SQLWCHAR _newGroup[20];

    strcpy_s((char*)_oldGroup, strlen(oldGroup.c_str()) + 1, oldGroup.c_str());
    strcpy_s((char*)_newGroup, strlen(newGroup.c_str()) + 1, newGroup.c_str());
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, _newGroup, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, _oldGroup, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"UPDATE group_ SET group_ = ? WHERE group_ = ?;", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;
}

bool ScheduleDataMapper::removeSchedule(int number) {
    int id = 0, id_auditory = 0, id_group = 0, id_day = 0, id_time = 0;
    int temp_id_auditory = 0, temp_id_group = 0, temp_id_day = 0, temp_id_time = 0;
    bool firstSchedule = true;
    vector<vector<int>> idList;

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, group_, week, day, start_time, end_time, "
                    "schedule.id, id_auditory, id_group, id_day, id_time FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "ORDER BY auditory, group_, day, week;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 7,  SQL_C_SLONG, &id,           sizeof(id),             NULL);
    retcode = SQLBindCol(hstmt, 8,  SQL_C_SLONG, &id_auditory,  sizeof(id_auditory),    NULL);
    retcode = SQLBindCol(hstmt, 9,  SQL_C_SLONG, &id_group,     sizeof(id_group),       NULL);
    retcode = SQLBindCol(hstmt, 10,  SQL_C_SLONG, &id_day,       sizeof(id_day),         NULL);
    retcode = SQLBindCol(hstmt, 11,  SQL_C_SLONG, &id_time,      sizeof(id_time),        NULL);

    for (int i = 0, j = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (id_auditory != temp_id_auditory || id_group != temp_id_group ||
                id_day != temp_id_day || id_time != temp_id_time) {
                temp_id_auditory = id_auditory;
                temp_id_group = id_group;
                temp_id_day = id_day;
                temp_id_time = id_time;

                idList.push_back(vector<int>());
                if (firstSchedule) {
                    idList[j].push_back(id);
                    firstSchedule = false;
                }
                else idList[++j].push_back(id);
            }
            else idList[j].push_back(id);
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

    if (number < 1 || number > idList.size())
        return false;

    for (int i = 0; i < idList[number - 1].size(); i++) {
        SQLINTEGER removeNumber = idList[number - 1][i];
        //cout << "removeNumber: " << removeNumber << endl;
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
        retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"DELETE FROM schedule WHERE id = ?;", SQL_NTS);
        if (retcode < 0) {
            idList.clear();
            idList.shrink_to_fit();
            return false;
        }
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    }

    idList.clear();
    idList.shrink_to_fit();
    return true;
}

bool ScheduleDataMapper::removeAuditory(string auditoryChoice) {
    char auditory[20] = "";

    strcpy_s((char*)auditory, strlen(auditoryChoice.c_str()) + 1, auditoryChoice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditory, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"DELETE FROM auditory WHERE auditory = ?;", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    if (retcode < 0)
        return false;
    return true;
}

bool ScheduleDataMapper::removeGroup(string groupChoice) {
    char group[20] = "";

    strcpy_s((char*)group, strlen(groupChoice.c_str()) + 1, groupChoice.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, group, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"DELETE FROM group_ WHERE group_ = ?;", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    if (retcode < 0)
        return false;
    return true;
}

void ScheduleDataMapper::findFreeAuditoryByTime(string timeChoice) {
    SQLWCHAR startTime[20];
    SQLWCHAR endTime[20];
    string _startTime, _endTime;
    bool foundStartTime = false;
    int week = 0;
    char auditory[20] = "";
    char day[20] = "";
    vector<vector<string>> weeksAndDays;
    vector<string> busyAuditory;

    for (int i = 0; i < timeChoice.length(); i++) {
        if (!foundStartTime && timeChoice[i] != ' ' &&
            timeChoice[i] != '-' && timeChoice[i] != '\0') {
            _startTime += timeChoice[i];
            if (timeChoice[i + 1] == ' ' ||
                timeChoice[i + 1] == '-' || timeChoice[i + 1] == '\0')
                foundStartTime = true;
        }
        else if (timeChoice[i] != ' ' &&
            timeChoice[i] != '-' && timeChoice[i] != '\0') {
            _endTime += timeChoice[i];
        }
    }

    strcpy_s((char*)startTime, strlen(_startTime.c_str()) + 1, _startTime.c_str());
    strcpy_s((char*)endTime, strlen(_endTime.c_str()) + 1, _endTime.c_str());

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

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, startTime, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, endTime, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, week, day FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "WHERE start_time = ? and end_time = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, &auditory, 20, NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &week, 0, NULL);
    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, day, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            auto iterator = weeksAndDays[week - 1].cbegin();
            for (int k = 0; k < weeksAndDays[week - 1].size(); k++) {
                if (weeksAndDays[week - 1][k] == string(day)) {
                    weeksAndDays[week - 1].erase(iterator + k);
                    break;
                }
            }
            if (!busyAuditory.empty()) {
                if (busyAuditory[busyAuditory.size() - 1] != auditory)
                    busyAuditory.push_back(auditory);
            }
            else busyAuditory.push_back(auditory);
                

            for (int j = 0; j < 20; j++)
                day[j] = '0';
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

    cout << "Аудитория(и): ";
    for (int i = 0; i < busyAuditory.size(); i++)
        cout << busyAuditory[i] << ' ';
    cout << endl << "свободна(ы) в " << timeChoice << " в данные недели и дни:" << endl << endl;
    for (int i = 0; i < 18; i++) {
        if (i < 9) cout << ' ';
        cout << i + 1 << " неделя:\t ";
        for (int j = 0; j < weeksAndDays[i].size(); j++) {
            if (j == weeksAndDays[i].size() - 1)
                cout << weeksAndDays[i][j];
            else 
                cout << weeksAndDays[i][j] << ", ";

        }
        cout << endl;
    }
    cout << endl << "Остальные аудитории в " << timeChoice << " свободны в любой день любой недели" << endl << endl;
    
    weeksAndDays.clear();
    weeksAndDays.shrink_to_fit();
}

void ScheduleDataMapper::findFreeAuditoryByNumberOfHours(int numberOfHoursChoice, int weekNumber) {
    char auditory[20] = "";
    int week = 0;
    char day[20] = "";
    char startTime[20] = "";
    char endTime[20] = "";
    vector<vector<string>> daysAndTime;
    vector<string> busyAuditory;
    SQLINTEGER chosenWeek  = weekNumber;
    double amountOfClasses = ceil(double(numberOfHoursChoice * 60) / 90);
    double amountOfClassesOnEachDay = 0;
    double temp = ceil(double(amountOfClasses) / 7);

    for (int i = 0; i < 7; i++) {
        daysAndTime.push_back(vector<string>());
        daysAndTime[i].push_back("08:30-10:00");
        daysAndTime[i].push_back("10:15-11:45");
        daysAndTime[i].push_back("12:00-13:30");
        daysAndTime[i].push_back("14:00-15:30");
        daysAndTime[i].push_back("15:45-17:15");
        daysAndTime[i].push_back("17:30-19:00");
        daysAndTime[i].push_back("19:15-20:45");
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &chosenWeek, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT auditory, week, day, start_time, end_time FROM schedule "
                    "INNER JOIN auditory on auditory.id = id_auditory "
                    "INNER JOIN group_ on group_.id = id_group "
                    "INNER JOIN day on day.id = id_day "
                    "INNER JOIN time_ on time_.id = id_time "
                    "WHERE week = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, auditory, 20, NULL);
    retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &week, 0, NULL);
    retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, day, 20, NULL);
    retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, startTime, 20, NULL);
    retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, endTime, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            string tempStartTime(startTime);
            string tempEndTime(endTime);
            tempStartTime.resize(tempStartTime.size() - 3);
            tempEndTime.resize(tempEndTime.size() - 3);
            string time = tempStartTime + '-' + tempEndTime;

            int dayIndex = dayToIndex(string(day));

            auto iterator = daysAndTime[dayIndex].cbegin();
            for (int k = 0; k < daysAndTime[dayIndex].size(); k++) {
                if (daysAndTime[dayIndex][k] == time && week == weekNumber) {
                    daysAndTime[dayIndex].erase(iterator + k);
                    break;
                }
            }

            if (!busyAuditory.empty()) {
                if (busyAuditory[busyAuditory.size() - 1] != auditory)
                    busyAuditory.push_back(auditory);
            }
            else busyAuditory.push_back(auditory);

            for (int j = 0; j < 20; j++) {
                auditory[j] = ' ';
                day[j] = ' ';
                startTime[j] = ' ';
                endTime[j] = ' ';
            }
        }
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);

    cout << endl << "Аудитория(и): ";
    for (int i = 0; i < busyAuditory.size(); i++)
        cout << busyAuditory[i] << ' ';
    cout << endl << "на " << ceil(double(numberOfHoursChoice * 60) / 90) << " занятий свободна(ы) на " 
        << weekNumber << " неделе в данные дни и время:" << endl << endl;
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
    cout << endl << "Остальные аудитории на " << weekNumber << " неделе свободны в любой день в любое время" << endl << endl;

    daysAndTime.clear();
    daysAndTime.shrink_to_fit();
}

void ScheduleDataMapper::saveAll(ScheduleTable& scheduleTable) {
    saveAllAuditories(scheduleTable.getAuditoryList());
    saveAllGroups(scheduleTable.getGroupList());
    scheduleTable.updateEachIdInSchedule();
    saveAllSchedule(scheduleTable.getScheduleList());
}

void ScheduleDataMapper::saveAllSchedule(vector<Schedule>& scheduleList) {
    for (auto& i : scheduleList)
        i.setId(saveSchedule(i));
}

int ScheduleDataMapper::saveSchedule(Schedule& schedule) {
    int id = 0;
    SQLINTEGER week = schedule.getWeek();
    SQLWCHAR day[20];
    SQLWCHAR startTime[20];
    SQLWCHAR endTime[20];
    bool foundStartTime = false;
    SQLINTEGER id_week = 0, id_day = 0, id_time = 0;

    strcpy_s((char*)day, strlen(schedule.getDay().c_str()) + 1, schedule.getDay().c_str());
    strcpy_s((char*)startTime, strlen(schedule.getTime().getStartTime().c_str()) + 1,
        schedule.getTime().getStartTime().c_str());
    strcpy_s((char*)endTime, strlen(schedule.getTime().getEndTime().c_str()) + 1,
        schedule.getTime().getEndTime().c_str());

    // Запросы для получения id каждого поля
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, day, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM day WHERE day = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, startTime, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, endTime, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM time_ WHERE start_time = ? AND end_time = ?; ", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &schedule.getAuditory().getId(), 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &schedule.getGroup().getId(), 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"INSERT INTO schedule(id_auditory, id_group, week, id_day, id_time)"
        "VALUES (?, ?, ?, ?, ?);", SQL_NTS);
    if (retcode < 0) {
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        return 0;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"SELECT id FROM schedule WHERE"
        "id_auditory = ? AND "
        "id_group = ? AND "
        "week = ? AND "
        "id_day = ? AND "
        "id_time = ?;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, 0, NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return id;
}

void ScheduleDataMapper::saveAllAuditories(vector<Auditory>& auditoryList) {
    for (auto& i : auditoryList)
        i.setId(saveAuditory(i));
}

int ScheduleDataMapper::saveAuditory(Auditory& auditory) {
    int id = 0;
    char auditoryName[20] = "";

    strcpy_s((char*)auditoryName, strlen(auditory.getAuditoryName().c_str()) + 1, auditory.getAuditoryName().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, auditoryName, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO auditory(auditory) VALUES(?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT id FROM auditory WHERE auditory = ?;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, 0, NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return id;
}

void ScheduleDataMapper::saveAllGroups(vector<Group>& groupList) {
    for (auto& i : groupList)
        i.setId(saveGroup(i));
}

int ScheduleDataMapper::saveGroup(Group& group) {
    int id = 0;
    char groupName[20] = "";

    strcpy_s((char*)groupName, strlen(group.getGroupName().c_str()) + 1, group.getGroupName().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, groupName, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"INSERT INTO group_(group_) VALUES(?);", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT id FROM group_ WHERE group_ = ?;", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, 0, NULL);
    retcode = SQLFetch(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return id;
}

void ScheduleDataMapper::createTables() {
    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory ("
                    "id serial primary key,"
                    "auditory varchar(15) unique"
                    "); ", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"create table if not exists group_ ("
                    "id serial primary key,"
                    "group_ varchar(15) unique"
                    ");", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"create table if not exists day ("
                    "id serial primary key,"
                    "day varchar(15) unique);"
                    "INSERT INTO day(day) VALUES('Понедельник');"
                    "INSERT INTO day(day) VALUES('Вторник');"
                    "INSERT INTO day(day) VALUES('Среда');"
                    "INSERT INTO day(day) VALUES('Четверг');"
                    "INSERT INTO day(day) VALUES('Пятница');"
                    "INSERT INTO day(day) VALUES('Суббота');"
                    "INSERT INTO day(day) VALUES('Воскресенье');", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"create table if not exists time_ ("
                    "id serial primary key,"
                    "start_time time,"
                    "end_time time,"
                    "unique(start_time, end_time));"
                    "INSERT INTO time_(start_time, end_time) VALUES('8:30', '10:00');"
                    "INSERT INTO time_(start_time, end_time) VALUES('10:15', '11:45');"
                    "INSERT INTO time_(start_time, end_time) VALUES('12:00', '13:30');"
                    "INSERT INTO time_(start_time, end_time) VALUES('14:00', '15:30');"
                    "INSERT INTO time_(start_time, end_time) VALUES('15:45', '17:15');"
                    "INSERT INTO time_(start_time, end_time) VALUES('17:30', '19:00');"
                    "INSERT INTO time_(start_time, end_time) VALUES('19:15', '20:45');", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLExecDirect(hstmt,
        (SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS schedule ("
                    "id serial primary key,"
                    "id_Auditory int references auditory(id) on update cascade on delete cascade,"
                    "id_Group int references group_(id) on update cascade on delete cascade,"
                    "week int CHECK (week >= 1 AND week <= 18), "
                    "id_Day int references day(id) on update cascade on delete cascade,"
                    "id_Time int references time_(id) on update cascade on delete cascade,"
                    "unique(id_Auditory, week, id_Day, id_Time)); ", SQL_NTS);
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