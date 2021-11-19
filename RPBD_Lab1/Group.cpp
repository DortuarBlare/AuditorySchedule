#include "Group.h"

Group::Group() {
	this->id = -1;
	this->group = "...";
}

Group::Group(string group) {
	this->id = -1;
	this->group = group;
}

Group::Group(const Group& forCopy) {
	this->id = forCopy.id;
	this->group = forCopy.group;
}

bool Group::operator==(Group& forComparison) {
	return
		this->id == forComparison.id &&
		this->group == forComparison.group;
}

bool Group::operator!=(Group& forComparison) {
	return
		this->id != forComparison.id &&
		this->group != forComparison.group;
}

int Group::getId() {
	return this->id;
}

void Group::setId(int id) {
	this->id = id;
}

string Group::getGroup() {
	return this->group;
}

void Group::setGroup(string newGroup) {
	this->group = newGroup;
}

ostream& operator<<(ostream& os, Group& output) {
	os << "ID:\t" << output.id << endl;
	os << "√руппа:\t" << output.group << endl;

	return os;
}

istream& operator>>(istream& is, Group& input) {
	cout << "¬ведите группу: ";
	getline(is, input.group);

	return is;
}
