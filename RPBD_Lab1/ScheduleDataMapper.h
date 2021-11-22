#pragma once
#include "Schedule.h"
#include "ScheduleTable.h"
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include <iostream>
using namespace std;

class ScheduleDataMapper {
private:
    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

public:
    ScheduleDataMapper();
    ~ScheduleDataMapper();

    bool insertSchedule(Schedule schedule);
    bool insertAuditory(string auditoryChoice);
    bool insertGroup(string groupChoice);
    void showAll();
    void showByGroup(string choice);
    void showAllGroups();
    void showAllAuditories();
    bool fullEdit(int number, Schedule schedule);
    bool edit(int number, Schedule schedule);
    bool editAuditory(string number, string newAuditory);
    bool editGroup(string oldGroup, string newGroup);
    bool removeSchedule(int number);
    bool removeAuditory(string auditoryChoice);
    bool removeGroup(string groupChoice);
    void findFreeAuditoryByTime(string timeChoice);
    void findFreeAuditoryByNumberOfHours(int numberOfHoursChoice, int weekNumber);

    void saveAll(ScheduleTable& scheduleTable);
    void saveAllSchedule(vector<Schedule>& scheduleList);
    int saveSchedule(Schedule& schedule);
    void saveAllAuditories(vector<Auditory>& auditoryList);
    int saveAuditory(Auditory& auditory);
    void saveAllGroups(vector<Group>& groupList);
    int saveGroup(Group& group);
    void loadAll(ScheduleTable& scheduleTable);
    void createTables();

    int connectToDB();
    int disconnectFromDB();
    int dayToIndex(string day);
};