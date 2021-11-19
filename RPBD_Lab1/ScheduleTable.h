#pragma once
#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ScheduleTable {
private:
	vector<Schedule> scheduleList;

public:
	vector<Schedule> getScheduleList();
	void setScheduleList(vector<Schedule> scheduleList);
};