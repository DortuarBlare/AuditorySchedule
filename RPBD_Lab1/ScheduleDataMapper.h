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
    vector<Schedule> scheduleVector;

    SQLHENV henv; // ���������� ���������
    SQLHDBC hdbc; // ���������� ����������
    SQLHSTMT hstmt; // ���������� ���������
    SQLRETURN retcode; // ��� ��������

public:
    ScheduleDataMapper();
    ~ScheduleDataMapper();

    bool insert(Schedule schedule);

    int connectToDB();
    int disconnectFromDB();
};