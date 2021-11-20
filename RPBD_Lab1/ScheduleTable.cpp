#include "ScheduleTable.h"

ScheduleTable::~ScheduleTable() {
	this->scheduleList.clear();
	this->scheduleList.shrink_to_fit();

	this->auditoryList.clear();
	this->auditoryList.shrink_to_fit();

	this->groupList.clear();
	this->groupList.shrink_to_fit();

	this->timeList.clear();
	this->timeList.shrink_to_fit();
}

void ScheduleTable::insertSchedule(string auditory, string group, string week, string day, string startTime, string endTime) {
	/*int amountOfWeeks = 0;
	int weeks[20]{};
	string temp;
	for (int i = 0, j = 0; i < week.size(); i++) {
		if (week[i] != ' ' && week[i] != '\0')
			temp += week[i];
		else {
			weeks[amountOfWeeks++] = atoi(temp.c_str());
			temp.clear();
		}

		if (i == week.size() - 1 && !temp.empty()) {
			weeks[amountOfWeeks++] = atoi(temp.c_str());
			if (amountOfWeeks >= 18) break;
			temp.clear();
		}
	}*/
	int weekNumber = 0;
	int amountOfWeeks = 0;
	int weeks[20]{};
	stringstream in(week);
	while (in >> weekNumber) weeks[amountOfWeeks++] = weekNumber;

	Auditory newAuditory = Auditory(auditory);
	Group newGroup = Group(group);
	Time newTime = Time(startTime, endTime);

	auditoryList.push_back(newAuditory);
	groupList.push_back(newGroup);
	timeList.push_back(newTime);

	for (int i = 0; i < amountOfWeeks; i++) 
		scheduleList.push_back(Schedule(auditory, group, weeks[i], day, startTime, endTime));
}

void ScheduleTable::insertAuditory(string auditory) {
	this->auditoryList.push_back(Auditory(auditory));
}

void ScheduleTable::insertGroup(string group) {
	groupList.push_back(Group(group));
}

void ScheduleTable::showAll() {
	if (this->scheduleList.size() == 0) {
		cout << "Расписание отсутствует" << endl;
		return;
	}

	bool sameScheduleWithAnotherWeek = true;
	int iNext = 0;

	for (int i = 0, scheduleNumber = 1; i < this->scheduleList.size(); i++, scheduleNumber++) {
		cout << endl << "Порядковый номер расписания: " << scheduleNumber << endl;

		cout << "Аудитория:\t" << scheduleList[i].getAuditory()->getAuditory() << endl;

		cout << "Группа:\t\t" << scheduleList[i].getGroup()->getGroup() << endl;

		cout << "Недели:\t\t" << scheduleList[i].getWeek() << ' ';
		iNext = i + 1;
		while (sameScheduleWithAnotherWeek && iNext < this->scheduleList.size()) {
			if (*scheduleList[i].getAuditory() == *scheduleList[iNext].getAuditory() &&
				*scheduleList[i].getGroup() == *scheduleList[iNext].getGroup() &&
				scheduleList[i].getWeek() != scheduleList[iNext].getWeek() &&
				scheduleList[i].getDay() == scheduleList[iNext].getDay() &&
				*scheduleList[i].getTime() == *scheduleList[iNext].getTime()) {
				cout << scheduleList[iNext++].getWeek() << ' ';
			}
			else sameScheduleWithAnotherWeek = false;
		}
		sameScheduleWithAnotherWeek = true;
		i = iNext - 1;
		cout << endl;

		cout << "День недели:\t" << scheduleList[i].getDay() << endl;

		cout << "Время:\t\t" << scheduleList[i].getTime()->getStartTime() << " - " << scheduleList[i].getTime()->getEndTime() << endl;
	}
}

void ScheduleTable::showAllAuditories() {
	cout << endl << "Все аудитории: " << endl;

	for (auto& i : auditoryList) 
		cout << i.getAuditory() << endl;
}

void ScheduleTable::showAllGroups() {
	cout << endl << "Все группы: " << endl;

	for (auto& i : groupList)
		cout << i.getGroup() << endl;
}

void ScheduleTable::removeSchedule(int number) {
	bool sameScheduleWithAnotherWeek = true;

	for (int i = 0, iNext = i + 1, scheduleNumber = 1; i < this->scheduleList.size(); i++, scheduleNumber++) {
		iNext = i + 1;
		while (sameScheduleWithAnotherWeek && iNext < this->scheduleList.size()) {
			if (*scheduleList[i].getAuditory() == *scheduleList[iNext].getAuditory() &&
				*scheduleList[i].getGroup() == *scheduleList[iNext].getGroup() &&
				scheduleList[i].getWeek() != scheduleList[iNext].getWeek() &&
				scheduleList[i].getDay() == scheduleList[iNext].getDay() &&
				*scheduleList[i].getTime() == *scheduleList[iNext].getTime()) {
				iNext++;
			}
			else sameScheduleWithAnotherWeek = false;
		}
		if (scheduleNumber == number) {
			scheduleList.erase(scheduleList.begin() + i, scheduleList.begin() + iNext);
			return;
		}
	}
}

vector<Schedule> ScheduleTable::getScheduleList() {
	return scheduleList;
}

void ScheduleTable::setScheduleList(vector<Schedule> scheduleList) {
	this->scheduleList = scheduleList;
}