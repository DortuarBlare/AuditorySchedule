#include "Auditory.h"

Auditory::Auditory() {
	this->id = -1;
	this->auditoryName = "...";
}

Auditory::Auditory(string auditory) {
	this->id = -1;
	this->auditoryName = auditory;
}

Auditory::Auditory(const Auditory& forCopy) {
	this->id = forCopy.id;
	this->auditoryName = forCopy.auditoryName;
}

int& Auditory::getId() {
	return this->id;
}

void Auditory::setId(int id) {
	this->id = id;
}

string Auditory::getAuditoryName() {
	return this->auditoryName;
}

void Auditory::setAuditoryName(string auditory) {
	this->auditoryName = auditory;
}

bool operator==(const Auditory& left, const Auditory& right) {
	return
		left.id == right.id &&
		left.auditoryName == right.auditoryName;
}

bool operator!=(const Auditory& left, const Auditory& right) {
	return
		left.id != right.id &&
		left.auditoryName != right.auditoryName;
}

ostream& operator<<(ostream& os, Auditory& output) {
	os << "ID:\t" << output.id << endl;
	os << "Аудитория:\t" << output.auditoryName << endl;

	return os;
}

istream& operator>>(istream& is, Auditory& input) {
	cout << "Введите аудиторию: ";
	is.ignore();
	getline(is, input.auditoryName);

	return is;
}