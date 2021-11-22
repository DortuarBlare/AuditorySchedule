#include "Time.h"

Time::Time() {
	this->id = -1;
	this->startTime = "...";
	this->endTime = "...";
}

Time::Time(string startTime, string endTime) {
	this->id = -1;
	this->startTime = startTime;
	this->endTime = endTime;
}

Time::Time(const Time& forCopy) {
	this->id = forCopy.id;
	this->startTime = forCopy.startTime;
	this->endTime = forCopy.endTime;
}

int Time::getId() {
	return this->id;
}

void Time::setId(int id) {
	this->id = id;
}

string Time::getStartTime() {
	return this->startTime;
}

void Time::setStartTime(string newStartTime) {
	this->startTime = newStartTime;
}

string Time::getEndTime() {
	return this->endTime;
}

void Time::setEndTime(string newEndTime) {
	this->endTime = newEndTime;
}

bool operator==(const Time& left, const Time& right) {
	return
		left.id == right.id &&
		left.startTime == right.startTime &&
		left.endTime == right.endTime;
}

bool operator!=(const Time& left, const Time& right) {
	return
		left.id != right.id &&
		left.startTime != right.startTime &&
		left.endTime != right.endTime;
}

ostream& operator<<(ostream& os, Time& output) {
	os << "ID:\t" << output.id << endl;
	os << "¬рем€:\t" << output.startTime << " - " << output.endTime << endl;

	return os;
}

istream& operator>>(istream& is, Time& input) {
	cout << "¬ведите начальное врем€: ";
	getline(is, input.startTime);

	cout << "¬ведите конечное врем€: ";
	getline(is, input.endTime);

	return is;
}