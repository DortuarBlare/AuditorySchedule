#pragma once
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <Schedule.h>
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


};