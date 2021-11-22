#pragma once
#include <iostream>
#include <string>
using namespace std;

class Time {
private:
	int id;
	string startTime;
	string endTime;

public:
	Time();
	Time(string startTime, string endTime);
	Time(const Time& forCopy);

	int getId();
	void setId(int id);
	string getStartTime();
	void setStartTime(string newStartTime);
	string getEndTime();
	void setEndTime(string newEndTime);

	friend bool operator==(const Time& left, const Time& right);
	friend bool operator!=(const Time& left, const Time& right);
	friend ostream& operator<<(ostream& os, Time& output);
	friend istream& operator>>(istream& is, Time& input);
};