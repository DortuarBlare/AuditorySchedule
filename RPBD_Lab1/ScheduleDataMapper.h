#pragma once
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <Schedule.h>
#include <iostream>
using namespace std;

class ScheduleDataMapper {
private:
    SQLHENV henv; // ���������� ���������
    SQLHDBC hdbc; // ���������� ����������
    SQLHSTMT hstmt; // ���������� ���������
    SQLRETURN retcode; // ��� ��������

public:
    ScheduleDataMapper();
    ~ScheduleDataMapper();


};