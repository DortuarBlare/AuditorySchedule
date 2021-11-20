#pragma once
#include "Auditory.h"
#include "Group.h"
#include "Time.h"
#include <iostream>
#include <string>
using namespace std;

class Schedule {
private:
	int id; // Идентификационный номер
	Auditory* auditory; // Номер аудитории
	Group* group; // Группа, которой занята аудитория
	int week; // Неделя занятости аудитории
	string day; // День занятости аудитории
	Time* time; // Часы занятости аудитории

public:
	Schedule();
	Schedule(string auditory, string group, int week, string day, string startTime, string endTime);
	Schedule(Auditory* auditory, Group* group, int week, string day, Time* time);
	Schedule(const Schedule& forCopy);
	~Schedule();

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);

	int getId();
	void setId(int id);

	Auditory* getAuditory();
	void setAuditory(Auditory* auditory);

	int getWeek();
	void setWeek(int week);

	Group* getGroup();
	void setGroup(Group* group);

	string getDay();
	void setDay(string day);

	Time* getTime();
	void setTime(Time* time);
};