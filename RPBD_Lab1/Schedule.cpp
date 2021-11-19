#include "Schedule.h"

Schedule::Schedule() {
	this->id = -1;
	this->auditory = new Auditory();
	this->week = "...";
	this->group = "...";
	this->day = "...";
	this->time = "...";
}

Schedule::Schedule(int id, Auditory* auditory, string group, string week, string day, string time) {
	this->id = id;
	this->auditory = auditory;
	this->group = group;
	this->week = week;
	this->day = day;
	this->time = time;
}

Schedule::Schedule(Auditory* auditory, string group, string week, string day, string time) {
	this->id = -1;
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
	os << "Id ����������:\t\t" << outputSchedule.id << endl;
	os << "���������:\t" << outputSchedule.auditory << endl;
	os << "������:\t\t" << outputSchedule.group << endl;
	os << "������:\t\t" << outputSchedule.week << endl;
	os << "����:\t\t" << outputSchedule.day << endl;
	os << "�����:\t\t" << outputSchedule.time << endl;
	return os;
}

istream& operator>>(istream& is, Schedule& inputSchedule) {
	cout << "���������: ";
	is.ignore();
	//getline(is, inputSchedule.auditory);
	cin >> inputSchedule.auditory;
	cout << "������: ";
	getline(is, inputSchedule.group);
	cout << "������: ";
	getline(is, inputSchedule.week);
	cout << "����: ";
	getline(is, inputSchedule.day);
	cout << "�����: ";
	getline(is, inputSchedule.time);
	return is;
}

void Schedule::setId(int id) {
	this->id = id;
}

int Schedule::getId() {
	return this->id;
}

void Schedule::setAuditory(string auditory) {
	this->auditory = auditory;
}

string Schedule::getAuditory() {
	return this->auditory;
}

void Schedule::setWeek(string week) {
	this->week = week;
}

string Schedule::getWeek() {
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