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

bool Time::operator==(Time& forComparison) {
	return
		this->id == forComparison.id &&
		this->startTime == forComparison.startTime &&
		this->endTime == forComparison.endTime;
}

bool Time::operator!=(Time& forComparison) {
	return
		this->id != forComparison.id &&
		this->startTime != forComparison.startTime &&
		this->endTime != forComparison.endTime;
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