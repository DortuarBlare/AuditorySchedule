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
    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

public:
    ScheduleDataMapper();
    ~ScheduleDataMapper();

    bool insert(Schedule schedule);
    void showAll();
    void showAllGroups();
    void showByGroup(string choice);
    bool fullEdit(int number, Schedule schedule);
    bool edit(int number, Schedule schedule);
    bool remove(int number);
    void findFreeAuditoryByTime(string timeChoice);
    void findFreeAuditoryByNumberOfHours(int numberOfHoursChoice, int weekNumber);
    void createTables();

    int connectToDB();
    int disconnectFromDB();
    int dayToIndex(string day);
};