#include "Group.h"

Group::Group() {
	this->id = -1;
	this->groupName = "...";
}

Group::Group(int id, string group) {
	this->id = id;
	this->groupName = group;
}

Group::Group(string group) {
	this->id = -1;
	this->groupName = group;
}

Group::Group(const Group& forCopy) {
	this->id = forCopy.id;
	this->groupName = forCopy.groupName;
}

int& Group::getId() {
	return this->id;
}

void Group::setId(int id) {
	this->id = id;
}

string Group::getGroupName() {
	return this->groupName;
}

void Group::setGroupName(string newGroup) {
	this->groupName = newGroup;
}

bool operator==(const Group& left, const Group& right) {
	return
		left.id == right.id &&
		left.groupName == right.groupName;
}

bool operator!=(const Group& left, const Group& right) {
	return
		left.id != right.id &&
		left.groupName != right.groupName;
}

ostream& operator<<(ostream& os, Group& output) {
	os << "ID:\t" << output.id << endl;
	os << "√руппа:\t" << output.groupName << endl;

	return os;
}

istream& operator>>(istream& is, Group& input) {
	cout << "¬ведите группу: ";
	getline(is, input.groupName);

	return is;
}
