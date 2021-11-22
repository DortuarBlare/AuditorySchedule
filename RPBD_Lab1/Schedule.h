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
	Auditory auditory; // Номер аудитории
	Group group; // Группа, которой занята аудитория
	int week; // Неделя занятости аудитории
	string day; // День занятости аудитории
	Time time; // Часы занятости аудитории

public:
	Schedule();
	Schedule(int id, Auditory auditory, Group group, int week, string day, Time time);
	Schedule(string auditory, string group, int week, string day, string startTime, string endTime);
	Schedule(const Schedule& forCopy);

	void print();

	int& getId();
	void setId(int id);

	Auditory& getAuditory();
	void setAuditory(Auditory auditory);

	int& getWeek();
	void setWeek(int week);

	Group& getGroup();
	void setGroup(Group group);

	string getDay();
	void setDay(string day);

	Time& getTime();
	void setTime(Time time);

	friend bool operator==(const Schedule& left, const Schedule& right);
	friend bool operator!=(const Schedule& left, const Schedule& right);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);
};