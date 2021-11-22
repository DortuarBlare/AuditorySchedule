#pragma once
#include <iostream>
#include <string>
using namespace std;

class Group {
private:
	int id;
	string groupName;

public:
	Group();
	Group(string group);
	Group(const Group& forCopy);

	int& getId();
	void setId(int id);
	string getGroupName();
	void setGroupName(string newGroup);

	friend bool operator==(const Group& left, const Group& right);
	friend bool operator!=(const Group& left, const Group& right);
	friend ostream& operator<<(ostream& os, Group& output);
	friend istream& operator>>(istream& is, Group& input);
};