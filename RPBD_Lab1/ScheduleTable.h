#pragma once
#include "Schedule.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class ScheduleTable {
private:
	vector<Schedule> scheduleList;
	vector<Auditory> auditoryList;
	vector<Group> groupList;
	vector<Time> timeList;

public:
	~ScheduleTable();

	void insertSchedule(string auditory, string group, string week, string day, string startTime, string endTime);
	void insertAuditory(string auditory);
	void insertGroup(string group);
	void showAll();
	void showAllAuditories();
	void showAllGroups();
	void removeSchedule(int number);

	vector<Schedule> getScheduleList();
	void setScheduleList(vector<Schedule> scheduleList);
};