#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleDataMapper.h"
#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    ScheduleDataMapper dataMapper;
    
    dataMapper.insert(Schedule(2, 303, "AVT-815", 5, "Monday", "18pukpuk"));
}