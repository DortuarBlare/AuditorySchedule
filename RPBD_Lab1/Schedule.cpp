#include "Schedule.h"

Schedule::Schedule(int id, int classroomNumber, string group, int week, string day, string time) {
	this->id = id;
	this->audNum = classroomNumber;
	this->group = group;
	this->week = week;
	this->day = day;
	this->time = time;
}

Schedule::Schedule(const Schedule& forCopy) {
	this->id = forCopy.id;
	this->audNum = forCopy.audNum;
	this->group = forCopy.group;
	this->week = forCopy.week;
	this->day = forCopy.day;
	this->time = forCopy.time;
}

void Schedule::print() {
	cout << "ID: \t" << this->id << endl;
	cout << "AudNum: \t" << this->audNum << endl;
	cout << "Group: \t" << this->group << endl;
	cout << "Week: \t" << this->week << endl;
	cout << "Day: \t" << this->day << endl;
	cout << "Time: \t" << this->time << endl;
}

bool Schedule::operator==(Schedule& forComparison) {
	return
		this->audNum == forComparison.audNum &&
		this->group == forComparison.group &&
		this->week == forComparison.week &&
		this->day == forComparison.day &&
		this->time == forComparison.time;
}

bool Schedule::operator!=(Schedule& forComparison) {
	return
		this->audNum != forComparison.audNum &&
		this->group != forComparison.group &&
		this->week != forComparison.week &&
		this->day != forComparison.day &&
		this->time != forComparison.time;
}

void Schedule::setId(int id) {
	this->id = id;
}

int Schedule::getId() {
	return this->id;
}

void Schedule::setClassroomNumber(int classroomNumber) {
	this->audNum = classroomNumber;
}

int Schedule::getClassroomNumber() {
	return this->audNum;
}

void Schedule::setWeek(int week) {
	this->week = week;
}

int Schedule::getWeek() {
	return this->week;
}

void Schedule::setGroup(string group) {
	this->group = group;
}

string Schedule::getGroup(){
	return this->group;
}

void Schedule::setDay(string day) {
	this->day = day;
}

string Schedule::getDay() {
	return this->day;
}

void Schedule::setTime(string time) {
	this->time = time;
}

string Schedule::getTime() {
	return this->time;
}
