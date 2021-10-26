#pragma once
#include <iostream>
#include <string>
using namespace std;

class Schedule {
private:
	int id; // ����������������� �����
	string auditory; // ����� ���������
	string week; // ������ ��������� ���������
	string group; // ������, ������� ������ ���������
	string day; // ���� ��������� ���������
	string time; // ���� ��������� ���������

public:
	Schedule();
	Schedule(int id, string auditory, string group, string week, string day, string time);
	Schedule(string auditory, string group, string week, string day, string time);
	Schedule(const Schedule& forCopy);

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);

	void setId(int id);
	int getId();
	void setAuditory(string classroomNumber);
	string getAuditory();
	void setWeek(string week);
	string getWeek();
	void setGroup(string group);
	string getGroup();
	void setDay(string day);
	string getDay();
	void setTime(string time);
	string getTime();
};