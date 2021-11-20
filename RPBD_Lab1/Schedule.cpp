#include "Schedule.h"

Schedule::Schedule() {
	this->id = -1;
	this->auditory = new Auditory();
	this->week = -1;
	this->group = new Group();
	this->day = "...";
	this->time = new Time();
}

//Schedule::Schedule(int id, string auditory, string group, string week, string day, Time time) {
//	this->id = id;
//	this->auditory = new Auditory(auditory);
//	this->group = group;
//	this->week = week;
//	this->day = day;
//	this->time = new Time();
//}

Schedule::Schedule(string auditory, string group, int week, string day, string startTime, string endTime) {
	this->id = -1;
	this->auditory = new Auditory(auditory);
	this->group = new Group(group);
	this->week = week;
	this->day = day;
	this->time = new Time(startTime, endTime);
}

Schedule::Schedule(Auditory* auditory, Group* group, int week, string day, Time* time) {
	this->id = -1;
	this->auditory = auditory;
	this->group = group;
	this->week = week;
	this->day = day;
	this->time = time;
}

Schedule::Schedule(const Schedule& forCopy) {
	this->id = forCopy.id;
	this->auditory = new Auditory(*forCopy.auditory);
	this->group = new Group(*forCopy.group);
	this->week = forCopy.week;
	this->day = forCopy.day;
	this->time = new Time(*forCopy.time);
}

Schedule::~Schedule() {
	delete auditory;
	delete group;
	delete time;
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
	os << "Id расписания:\t\t" << outputSchedule.id << endl;
	os << "\t" << *outputSchedule.auditory << endl;
	os << "Группа:\t\t" << outputSchedule.group << endl;
	os << "Недели:\t\t" << outputSchedule.week << endl;
	os << "День:\t\t" << outputSchedule.day << endl;
	os << "Время:\t\t" << outputSchedule.time << endl;

	return os;
}

istream& operator>>(istream& is, Schedule& inputSchedule) {
	cin >> *inputSchedule.auditory;

	cin >> *inputSchedule.group;

	cout << "Введите неделю: ";
	cin >> inputSchedule.week;

	cout << "Введите день: ";
	getline(is, inputSchedule.day);

	cin >> *inputSchedule.time;

	return is;
}

int Schedule::getId() {
	return this->id;
}

void Schedule::setId(int id) {
	this->id = id;
}

Auditory* Schedule::getAuditory() {
	return this->auditory;
}

void Schedule::setAuditory(Auditory* newAuditory) {
	this->auditory = new Auditory(*newAuditory);
}

int Schedule::getWeek() {
	return this->week;
}

void Schedule::setWeek(int week) {
	this->week = week;
}

Group* Schedule::getGroup() {
	return this->group;
}

void Schedule::setGroup(Group* group) {
	this->group = new Group(*group);
}

string Schedule::getDay() {
	return this->day;
}

void Schedule::setDay(string day) {
	this->day = day;
}

Time* Schedule::getTime() {
	return this->time;
}

void Schedule::setTime(Time* time) {
	this->time = new Time(*time);
}