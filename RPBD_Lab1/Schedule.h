#pragma once
#include <iostream>
using namespace std;

class Schedule {
private:
	int id; // Идентификационный номер
	int audNum; // Номер аудитории
	int week; // Неделя занятости аудитории
	string group; // Группа, которой занята аудитория
	string day; // День занятости аудитории
	string time; // Часы занятости аудитории

public:
	Schedule(int id, int classroomNumber, string group, int week, string day, string time);
	Schedule(const Schedule& forCopy);

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);

	void setId(int id);
	int getId();
	void setClassroomNumber(int classroomNumber);
	int getClassroomNumber();
	void setWeek(int week);
	int getWeek();
	void setGroup(string group);
	string getGroup();
	void setDay(string day);
	string getDay();
	void setTime(string time);
	string getTime();
};