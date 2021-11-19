#pragma once
#include "Auditory.h"
#include <iostream>
#include <string>
using namespace std;

class Schedule {
private:
	int id; // Идентификационный номер
	Auditory* auditory; // Номер аудитории
	string week; // Неделя занятости аудитории
	string group; // Группа, которой занята аудитория
	string day; // День занятости аудитории
	string time; // Часы занятости аудитории

public:
	Schedule();
	Schedule(int id, Auditory* auditory, string group, string week, string day, string time);
	Schedule(Auditory* auditory, string group, string week, string day, string time);
	Schedule(const Schedule& forCopy);

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);

	int getId();
	void setId(int id);

	string getAuditory();
	void setAuditory(string classroomNumber);

	string getWeek();
	void setWeek(string week);

	string getGroup();
	void setGroup(string group);

	string getDay();
	void setDay(string day);

	string getTime();
	void setTime(string time);
};