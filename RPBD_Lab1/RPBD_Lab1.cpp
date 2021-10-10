#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleDataMapper.h"
#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    //Schedule sched(2, 303, "AVT-815", 5, "Monday", "18:00-19:30");
    //cout << sched;
    
    ScheduleDataMapper dataMapper;
    //dataMapper.insert(Schedule(0, 303, "AVT-815", 5, "Monday", "18:00-19:30"));
    dataMapper.createTables();
    dataMapper.insert(Schedule(1, 404, "AVT-814", 5, "Tuesday", "12:00-13:30"));
}