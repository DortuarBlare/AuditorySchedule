#pragma once
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include <vector>
#include <iostream>
using namespace std;

class ScheduleDataMapper {
private:
    //vector<Schedule> scheduleVector;

    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

public:
    ScheduleDataMapper();
    ~ScheduleDataMapper();

    bool insert(Schedule schedule);
    void showAll();
    void showByGroup(string choice);
    bool edit(int number, Schedule schedule);
    bool remove(int number);
    void findFreeAuditoryByTime(int auditoryChoice, string timeChoice);
    void findFreeAuditoryByNumberOfHours(int auditoryChoice, int numberOfHoursChoice, int weekNumber);
    void createTables();

    int connectToDB();
    int disconnectFromDB();
    int dayToIndex(string day);
};