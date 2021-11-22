#include "Schedule.h"

Schedule::Schedule() {
	this->id = -1;
	this->auditory = Auditory();
	this->week = -1;
	this->group = Group();
	this->day = "...";
	this->time = Time();
}

Schedule::Schedule(string auditory, string group, int week, string day, string startTime, string endTime) {
	this->id = -1;
	this->auditory = Auditory(auditory);
	this->group = Group(group);
	this->week = week;
	this->day = day;
	this->time = Time(startTime, endTime);
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

int Schedule::getId() {
	return this->id;
}

void Schedule::setId(int id) {
	this->id = id;
}

Auditory& Schedule::getAuditory() {
	return this->auditory;
}

void Schedule::setAuditory(Auditory newAuditory) {
	this->auditory = newAuditory;
}

int Schedule::getWeek() {
	return this->week;
}

void Schedule::setWeek(int week) {
	this->week = week;
}

Group& Schedule::getGroup() {
	return this->group;
}

void Schedule::setGroup(Group group) {
	this->group = group;
}

string Schedule::getDay() {
	return this->day;
}

void Schedule::setDay(string day) {
	this->day = day;
}

Time& Schedule::getTime() {
	return this->time;
}

void Schedule::setTime(Time time) {
	this->time = time;
}

bool operator==(const Schedule& left, const Schedule& right) {
	return
		left.auditory == right.auditory &&
		left.group == right.group &&
		left.week == right.week &&
		left.day == right.day &&
		left.time == right.time;
}

bool operator!=(const Schedule& left, const Schedule& right) {
	return
		left.auditory != right.auditory &&
		left.group != right.group &&
		left.week != right.week &&
		left.day != right.day &&
		left.time != right.time;
}

ostream& operator<<(ostream& os, Schedule& outputSchedule) {
	os << "Id расписания:\t\t" << outputSchedule.id << endl;
	os << outputSchedule.auditory << endl;
	os << outputSchedule.group << endl;
	os << "Недели:\t\t" << outputSchedule.week << endl;
	os << "День:\t\t" << outputSchedule.day << endl;
	os << outputSchedule.time << endl;

	return os;
}

istream& operator>>(istream& is, Schedule& inputSchedule) {
	cin >> inputSchedule.auditory;

	cin >> inputSchedule.group;

	cout << "Введите неделю: ";
	cin >> inputSchedule.week;

	cout << "Введите день: ";
	getline(is, inputSchedule.day);

	cin >> inputSchedule.time;

	return is;
}