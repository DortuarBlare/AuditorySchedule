#include "Schedule.h"

Schedule::Schedule() {
	this->id = -1;
	this->auditory = -1;
	this->week = -1;
	this->group = "...";
	this->day = "...";
	this->time = "...";
}

Schedule::Schedule(int id, int auditory, string group, int week, string day, string time) {
	this->id = id;
	this->auditory = auditory;
	this->group = group;
	this->week = week;
	this->day = day;
	this->time = time;
}

Schedule::Schedule(const Schedule& forCopy) {
	this->id = forCopy.id;
	this->auditory = forCopy.auditory;
	this->group = forCopy.group;
	this->week = forCopy.week;
	this->day = forCopy.day;
	this->time = forCopy.time;
}

void Schedule::print() {
	cout << "ID:\t" << this->id << endl;
	cout << "Auditory:\t\t" << this->auditory << endl;
	cout << "Group:\t\t" << this->group << endl;
	cout << "Week:\t\t" << this->week << endl;
	cout << "Day:\t\t" << this->day << endl;
	cout << "Time:\t\t" << this->time << endl;
}

bool Schedule::operator==(Schedule& forComparison) {
	return
		this->auditory == forComparison.auditory &&
		this->group == forComparison.group &&
		this->week == forComparison.week &&
		this->day == forComparison.day &&
		this->time == forComparison.time;
}

bool Schedule::operator!=(Schedule& forComparison) {
	return
		this->auditory != forComparison.auditory &&
		this->group != forComparison.group &&
		this->week != forComparison.week &&
		this->day != forComparison.day &&
		this->time != forComparison.time;
}

ostream& operator<<(ostream& os, Schedule& outputSchedule) {
	os << "Auditory:\t" << outputSchedule.auditory << endl;
	os << "Group:\t\t" << outputSchedule.group << endl;
	os << "Week:\t\t" << outputSchedule.week << endl;
	os << "Day:\t\t" << outputSchedule.day << endl;
	os << "Time:\t\t" << outputSchedule.time << endl;
	return os;
}

istream& operator>>(istream& is, Schedule& inputSchedule) {
	is >> inputSchedule.id;
	is >> inputSchedule.auditory;
	is >> inputSchedule.group;
	is >> inputSchedule.week;
	is >> inputSchedule.day;
	is >> inputSchedule.time;
	return is;
}

void Schedule::setId(int id) {
	this->id = id;
}

int Schedule::getId() {
	return this->id;
}

void Schedule::setAuditory(int classroomNumber) {
	this->auditory = classroomNumber;
}

int Schedule::getAuditory() {
	return this->auditory;
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