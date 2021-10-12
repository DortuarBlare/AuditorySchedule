#pragma once
#include <iostream>
using namespace std;

class Schedule {
private:
	int id; // Идентификационный номер
	int auditory; // Номер аудитории
	int week; // Неделя занятости аудитории
	string group; // Группа, которой занята аудитория
	string day; // День занятости аудитории
	string time; // Часы занятости аудитории

public:
	Schedule();
	Schedule(int id, int auditory, string group, int week, string day, string time);
	Schedule(int auditory, string group, int week, string day, string time);
	Schedule(const Schedule& forCopy);

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);

	void setId(int id);
	int getId();
	void setAuditoryNumber(int classroomNumber);
	int getAuditoryNumber();
	void setWeek(int week);
	int getWeek();
	void setGroup(string group);
	string getGroup();
	void setDay(string day);
	string getDay();
	void setTime(string time);
	string getTime();
};