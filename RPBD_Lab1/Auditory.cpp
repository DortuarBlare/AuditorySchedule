#include "Auditory.h"

Auditory::Auditory() {

}

bool Auditory::operator==(Auditory& forComparison) {
	return
		this->id == forComparison.id &&
		this->auditory == forComparison.auditory;
}

bool Auditory::operator!=(Auditory& forComparison) {
	return
		this->id != forComparison.id && 
		this->auditory != forComparison.auditory;
}

ostream& operator<<(ostream& os, Auditory& output) {
	os << "ID:\t" << output.id << endl;
	os << "Аудитория:\t" << output.auditory << endl;

	return os;
}

istream& operator>>(istream& is, Auditory& input) {
	cout << "Аудитория: ";
	is.ignore();
	getline(is, input.auditory);

	return is;
}

int Auditory::getId() {
	return this->id;
}

void Auditory::setId(int id) {
	this->id = id;
}

string Auditory::getAuditory() {
	return this->auditory;
}

void Auditory::setAuditory(string auditory) {
	this->auditory = auditory;
}