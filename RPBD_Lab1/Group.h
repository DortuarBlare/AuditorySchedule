#pragma once
#include <iostream>
#include <string>
using namespace std;

class Group {
private:
	int id;
	string group;

public:
	Group();
	Group(string group);
	Group(const Group& forCopy);

	bool operator==(Group& forComparison);
	bool operator!=(Group& forComparison);
	friend ostream& operator<<(ostream& os, Group& output);
	friend istream& operator>>(istream& is, Group& input);

	int getId();
	void setId(int id);
	string getGroup();
	void setGroup(string newGroup);
};