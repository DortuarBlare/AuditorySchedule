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
	//vector<Time> timeList;

public:
	~ScheduleTable();

	bool insertSchedule(string auditory, string group, string week, string day, string startTime, string endTime);
	bool insertAuditory(string auditory);
	bool insertGroup(string group);

	void showAll();
	void showAllAuditories();
	void showAllGroups();

	bool fullScheduleEdit(int number, string auditory, string group, string week, string day, string startTime, string endTime);
	bool editAuditoryInSchedule(int number, string newAuditoryName);
	bool editGroupInSchedule(int number, string newGroupName);
	bool editDayInSchedule(int number, string newDay);
	bool editTimeInSchedule(int number, string newStartTime, string newEndTime);
	bool editAuditory(string number, string newAuditory);
	bool editGroup(string oldGroup, string newGroup);

	bool removeSchedule(int number);
	bool removeAuditory(string auditory);
	bool removeGroup(string group);

	bool scheduleExist(string auditory, int week, string day, string startTime, string endTime);
	bool auditoryExist(string auditory);
	bool groupExist(string group);

	void updateEachIdInSchedule();

	vector<int> getIndexesRangeOfSchedule(int number);
	vector<Schedule>& getScheduleList();
	void setScheduleList(vector<Schedule> scheduleList);
	vector<Auditory>& getAuditoryList();
	vector<Group>& getGroupList();
};