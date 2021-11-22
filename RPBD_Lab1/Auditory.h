#pragma once
#include <iostream>
#include <string>
using namespace std;

class Auditory {
private:
	int id;
	string auditoryName;

public:
	Auditory();
	Auditory(int id, string auditory);
	Auditory(string auditory);
	Auditory(const Auditory& forCopy);

	int& getId();
	void setId(int id);
	string getAuditoryName();
	void setAuditoryName(string auditory);

	friend bool operator==(const Auditory& left, const Auditory& right);
	friend bool operator!=(const Auditory& left, const Auditory& right);
	friend ostream& operator<<(ostream& os, Auditory& output);
	friend istream& operator>>(istream& is, Auditory& input);
};