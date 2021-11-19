#pragma once
#include <iostream>
#include <string>
using namespace std;

class Auditory {
private:
	int id;
	string auditory;

public:
	Auditory();

	bool operator==(Auditory& forComparison);
	bool operator!=(Auditory& forComparison);
	friend ostream& operator<<(ostream& os, Auditory& output);
	friend istream& operator>>(istream& is, Auditory& input);

	int getId();
	void setId(int id);
	string getAuditory();
	void setAuditory(string auditory);
};