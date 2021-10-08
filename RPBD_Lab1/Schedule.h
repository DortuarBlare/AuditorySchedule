#pragma once
#include <iostream>
using namespace std;

class Schedule {
private:
	int id; // ����������������� �����
	int audNum; // ����� ���������
	int week; // ������ ��������� ���������
	string group; // ������, ������� ������ ���������
	string day; // ���� ��������� ���������
	string time; // ���� ��������� ���������

public:
	Schedule();
	Schedule(int id, int audNum, string group, int week, string day, string time);
	Schedule(const Schedule& forCopy);

	void print();
	bool operator==(Schedule& forComparison);
	bool operator!=(Schedule& forComparison);
	friend ostream& operator<<(ostream& os, Schedule& outputSchedule);
	friend istream& operator>>(istream& is, Schedule& inputSchedule);

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