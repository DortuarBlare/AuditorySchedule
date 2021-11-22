#include "ScheduleTable.h"

ScheduleTable::~ScheduleTable() {
	this->scheduleList.clear();
	this->scheduleList.shrink_to_fit();

	this->auditoryList.clear();
	this->auditoryList.shrink_to_fit();

	this->groupList.clear();
	this->groupList.shrink_to_fit();

	//this->timeList.clear();
	//this->timeList.shrink_to_fit();
}

bool ScheduleTable::insertSchedule(Schedule schedule) {
	bool success = false;

	if (!auditoryExist(schedule.getAuditory().getAuditoryName())) insertAuditory(schedule.getAuditory());
	if (!groupExist(schedule.getGroup().getGroupName())) insertGroup(schedule.getGroup());

	if (!scheduleExist(schedule)) {
		scheduleList.push_back(schedule);
		success = true;
	}

	return success;
}

bool ScheduleTable::insertSchedule(string auditory, string group, string week, string day, string startTime, string endTime) {
	int weekNumber = 0;
	int amountOfWeeks = 0;
	int weeks[20]{};
	bool success = false;
	stringstream in(week);
	while (in >> weekNumber) weeks[amountOfWeeks++] = weekNumber;

	if (!auditoryExist(auditory)) insertAuditory(auditory);
	if (!groupExist(group)) insertGroup(group);
	//timeList.push_back(Time(startTime, endTime));

	for (int i = 0; i < amountOfWeeks; i++) {
		if (!scheduleExist(auditory, weeks[i], day, startTime, endTime)) {
			scheduleList.push_back(Schedule(auditory, group, weeks[i], day, startTime, endTime));
			success = true;
		}
	}

	return success;
}

bool ScheduleTable::insertAuditory(Auditory auditory) {
	bool success = false;
	int size = auditoryList.size();

	auditoryList.push_back(auditory);

	if (size < auditoryList.size()) success = true;

	return success;
}

bool ScheduleTable::insertAuditory(string auditory) {
	bool success = false;
	int size = auditoryList.size();

	auditoryList.push_back(Auditory(auditory));

	if (size < auditoryList.size()) success = true;

	return success;
}

bool ScheduleTable::insertGroup(Group group) {
	bool success = false;
	int size = groupList.size();

	groupList.push_back(group);

	if (size < groupList.size()) success = true;

	return success;
}

bool ScheduleTable::insertGroup(string group) {
	bool success = false;
	int size = groupList.size();

	groupList.push_back(Group(group));

	if (size < groupList.size()) success = true;

	return success;
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

		cout << "Аудитория:\t" << scheduleList[i].getAuditory().getAuditoryName() << endl;

		cout << "Группа:\t\t" << scheduleList[i].getGroup().getGroupName() << endl;

		cout << "Недели:\t\t" << scheduleList[i].getWeek() << ' ';
		iNext = i + 1;
		while (sameScheduleWithAnotherWeek && iNext < this->scheduleList.size()) {
			if (scheduleList[i].getAuditory() == scheduleList[iNext].getAuditory() &&
				scheduleList[i].getGroup() == scheduleList[iNext].getGroup() &&
				scheduleList[i].getWeek() != scheduleList[iNext].getWeek() &&
				scheduleList[i].getDay() == scheduleList[iNext].getDay() &&
				scheduleList[i].getTime() == scheduleList[iNext].getTime()) {
				cout << scheduleList[iNext++].getWeek() << ' ';
			}
			else sameScheduleWithAnotherWeek = false;
		}
		sameScheduleWithAnotherWeek = true;
		i = iNext - 1;
		cout << endl;

		cout << "День недели:\t" << scheduleList[i].getDay() << endl;

		cout << "Время:\t\t" << scheduleList[i].getTime().getStartTime() << " - " << scheduleList[i].getTime().getEndTime() << endl;
	}
}

void ScheduleTable::showAllAuditories() {
	if (auditoryList.size() == 0) {
		cout << "Аудитории отсутствуют" << endl;
		return;
	}

	cout << endl << "Все аудитории: " << endl;

	for (auto& i : auditoryList) 
		cout << i.getAuditoryName() << endl;
}

void ScheduleTable::showAllGroups() {
	if (groupList.size() == 0) {
		cout << "Группы отсутствуют" << endl;
		return;
	}

	cout << endl << "Все группы: " << endl;

	for (auto& i : groupList)
		cout << i.getGroupName() << endl;
}

// Добавить проверку совпадения Schedule
bool ScheduleTable::fullScheduleEdit(int number, string auditory, string group, string week, string day, string startTime, string endTime) {
	bool success = false;

	if (removeSchedule(number)) {
		success = insertSchedule(auditory, group, week, day, startTime, endTime);
		updateEachIdInSchedule();
	}

	return success;
}

bool ScheduleTable::editAuditoryInSchedule(int number, string newAuditoryName) {
	bool success = false;

	if (scheduleList.size() == 0) {
		cout << "Расписание отсутствует" << endl;
		return success;
	}
	
	if (auditoryExist(newAuditoryName)) {
		vector<int> indexesRange = getIndexesRangeOfSchedule(number);
		Auditory forNewId = findAuditory(newAuditoryName);

		if (indexesRange[0] == indexesRange[1]) {
			Schedule forScheduleCoincidence = scheduleList[indexesRange[0]];
			forScheduleCoincidence.getAuditory().setAuditoryName(newAuditoryName);
			
			if (!scheduleExist(forScheduleCoincidence)) {
				scheduleList[indexesRange[0]].getAuditory().setId(forNewId.getId());
				scheduleList[indexesRange[0]].getAuditory().setAuditoryName(newAuditoryName);
				success = true;
			}
		}
		else {
			for (int i = indexesRange[0]; i <= indexesRange[1]; i++) {
				Schedule forScheduleCoincidence = scheduleList[i];
				forScheduleCoincidence.getAuditory().setAuditoryName(newAuditoryName);

				if (!scheduleExist(forScheduleCoincidence)) {
					scheduleList[i].getAuditory().setId(forNewId.getId());
					scheduleList[i].getAuditory().setAuditoryName(newAuditoryName);
					success = true;
				}
			}
		}
	}
	else cout << "Данная аудитория отсутствует. Сначала добавьте данную аудиторию (0_0)" << endl;

	return success;
}

bool ScheduleTable::editGroupInSchedule(int number, string newGroupName) {
	bool success = false;

	if (scheduleList.size() == 0) {
		cout << "Расписание отсутствует" << endl;
		return success;
	}

	if (groupExist(newGroupName)) {
		vector<int> indexesRange = getIndexesRangeOfSchedule(number);
		Group forNewId = findGroup(newGroupName);

		if (indexesRange[0] == indexesRange[1]) {
			Schedule forScheduleCoincidence = scheduleList[indexesRange[0]];
			forScheduleCoincidence.getGroup().setGroupName(newGroupName);

			if (!scheduleExist(forScheduleCoincidence)) {
				scheduleList[indexesRange[0]].getGroup().setId(forNewId.getId());
				scheduleList[indexesRange[0]].getGroup().setGroupName(newGroupName);
				success = true;
			}
		}
		else {
			for (int i = indexesRange[0]; i <= indexesRange[1]; i++) {
				Schedule forScheduleCoincidence = scheduleList[i];
				forScheduleCoincidence.getGroup().setGroupName(newGroupName);

				if (!scheduleExist(forScheduleCoincidence)) {
					scheduleList[i].getGroup().setId(forNewId.getId());
					scheduleList[i].getGroup().setGroupName(newGroupName);
					success = true;
				}	
			}
		}
	}

	return success;
}

bool ScheduleTable::editDayInSchedule(int number, string newDay) {
	bool success = false;

	if (scheduleList.size() == 0) {
		cout << "Расписание отсутствует" << endl;
		return success;
	}

	vector<int> indexesRange = getIndexesRangeOfSchedule(number);

	if (indexesRange[0] == indexesRange[1]) {
		Schedule forScheduleCoincidence = scheduleList[indexesRange[0]];
		forScheduleCoincidence.setDay(newDay);

		if (!scheduleExist(forScheduleCoincidence)) {
			scheduleList[indexesRange[0]].setDay(newDay);
			success = true;
		}
	}
	else {
		for (int i = indexesRange[0]; i <= indexesRange[1]; i++) {
			Schedule forScheduleCoincidence = scheduleList[indexesRange[0]];
			forScheduleCoincidence.setDay(newDay);

			if (!scheduleExist(forScheduleCoincidence)) {
				scheduleList[i].setDay(newDay);
				success = true;
			}
		}
		
	}

	return success;
}

bool ScheduleTable::editTimeInSchedule(int number, string newStartTime, string newEndTime) {
	bool success = false;

	if (scheduleList.size() == 0) {
		cout << "Расписание отсутствует" << endl;
		return success;
	}

	vector<int> indexesRange = getIndexesRangeOfSchedule(number);

	if (indexesRange[0] == indexesRange[1]) {
		Schedule forScheduleCoincidence = scheduleList[indexesRange[0]];
		forScheduleCoincidence.getTime().setStartTime(newStartTime);
		forScheduleCoincidence.getTime().setEndTime(newEndTime);

		if (!scheduleExist(forScheduleCoincidence)) {
			scheduleList[indexesRange[0]].getTime().setStartTime(newStartTime);
			scheduleList[indexesRange[0]].getTime().setEndTime(newEndTime);
			success = true;
		}
	}
	else {
		for (int i = indexesRange[0]; i <= indexesRange[1]; i++) {
			Schedule forScheduleCoincidence = scheduleList[i];
			forScheduleCoincidence.getTime().setStartTime(newStartTime);
			forScheduleCoincidence.getTime().setEndTime(newEndTime);

			if (!scheduleExist(forScheduleCoincidence)) {
				scheduleList[i].getTime().setStartTime(newStartTime);
				scheduleList[i].getTime().setEndTime(newEndTime);
				success = true;
			}	
		}
	}

	return success;
}

bool ScheduleTable::editAuditory(string oldAuditory, string newAuditory) {
	bool success = false;

	if (auditoryList.size() == 0) {
		cout << "Аудитории отсутствуют" << endl;
		return success;
	}

	for (int i = 0; i < auditoryList.size(); i++) {
		if (auditoryList[i].getAuditoryName() == oldAuditory) {
			success = true;
			auditoryList[i].setAuditoryName(newAuditory);
			break;
		}
	}

	for (auto& i : scheduleList)
		if (i.getAuditory().getAuditoryName() == oldAuditory)
			i.getAuditory().setAuditoryName(newAuditory);

	return success;
}

bool ScheduleTable::editGroup(string oldGroup, string newGroup) {
	bool success = false;

	if (groupList.size() == 0) {
		cout << "Группы отсутствуют" << endl;
		return success;
	}

	for (int i = 0; i < groupList.size(); i++) {
		if (groupList[i].getGroupName() == oldGroup) {
			success = true;
			groupList[i].setGroupName(newGroup);
			break;
		}
	}

	for (auto& i : scheduleList)
		if (i.getGroup().getGroupName() == oldGroup)
			i.getGroup().setGroupName(newGroup);

	return success;
}

bool ScheduleTable::removeSchedule(int number) {
	bool success = false;
	int size = scheduleList.size();

	if (size == 0) {
		cout << "Расписание отсутствует" << endl;
		return success;
	}

	vector<int> indexesRange = getIndexesRangeOfSchedule(number);

	if (indexesRange[0] == indexesRange[1]) 
		scheduleList.erase(scheduleList.begin() + indexesRange[0]);
	else
		scheduleList.erase(scheduleList.begin() + indexesRange[0], scheduleList.begin() + indexesRange[1] + 1);

	if (size > scheduleList.size()) success = true;

	return success;
}

bool ScheduleTable::removeAuditory(string auditory) {
	bool success = false;
	int size = auditoryList.size();

	if (size == 0) {
		cout << "Аудитории отсутствуют" << endl;
		return success;
	}

	for (int i = 0; i < auditoryList.size(); i++) {
		if (auditoryList[i].getAuditoryName() == auditory) {
			auditoryList.erase(auditoryList.begin() + i);
			break;
		}
	}

	for (int i = 0; i < scheduleList.size(); i++) {
		if (scheduleList[i].getAuditory().getAuditoryName() == auditory)
			scheduleList.erase(scheduleList.begin() + i--);
	}

	if (size > auditoryList.size()) success = true;

	return success;
}

bool ScheduleTable::removeGroup(string group) {
	bool success = false;
	int size = groupList.size();

	if (size == 0) {
		cout << "Группы отсутствуют" << endl;
		return success;
	}

	for (int i = 0; i < groupList.size(); i++) {
		if (groupList[i].getGroupName() == group) {
			groupList.erase(groupList.begin() + i);
			break;
		}
	}

	for (int i = 0; i < scheduleList.size(); i++) {
		if (scheduleList[i].getGroup().getGroupName() == group)
			scheduleList.erase(scheduleList.begin() + i--);
	}

	if (size > groupList.size()) success = true;

	return success;
}

Schedule ScheduleTable::findSchedule(string auditory, int week, string day, string startTime, string endTime) {
	for (auto& i : scheduleList)
		if (i.getAuditory().getAuditoryName() == auditory &&
			i.getWeek() == week &&
			i.getDay() == day &&
			i.getTime().getStartTime() == startTime &&
			i.getTime().getEndTime() == endTime) return i;

	return Schedule();
}

Auditory ScheduleTable::findAuditory(string auditory) {
	for (auto& i : auditoryList)
		if (i.getAuditoryName() == auditory)
			return i;

	return Auditory();
}

Group ScheduleTable::findGroup(string group) {
	for (auto& i : groupList)
		if (i.getGroupName() == group)
			return i;

	return Group();
}

bool ScheduleTable::scheduleExist(Schedule schedule) {
	for (auto& i : scheduleList)
		if (i.getAuditory().getAuditoryName() == schedule.getAuditory().getAuditoryName() &&
			i.getWeek() == schedule.getWeek() &&
			i.getDay() == schedule.getDay() &&
			i.getTime().getStartTime() == schedule.getTime().getStartTime() &&
			i.getTime().getEndTime() == schedule.getTime().getEndTime()) return true;

	return false;
}

bool ScheduleTable::scheduleExist(string auditory, int week, string day, string startTime, string endTime) {
	for (auto& i : scheduleList)
		if (i.getAuditory().getAuditoryName() == auditory &&
			i.getWeek() == week &&
			i.getDay() == day &&
			i.getTime().getStartTime() == startTime &&
			i.getTime().getEndTime() == endTime) return true;

	return false;
}

bool ScheduleTable::auditoryExist(string auditory) {
	for (auto& i : auditoryList) 
		if (i.getAuditoryName() == auditory) 
			return true;

	return false;
}

bool ScheduleTable::groupExist(string group) {
	for (auto& i : groupList)
		if (i.getGroupName() == group)
			return true;

	return false;
}

void ScheduleTable::updateEachIdInSchedule() {
	for (auto& schedule : scheduleList) {
		for (auto& auditory : auditoryList)
			if (schedule.getAuditory().getAuditoryName() == auditory.getAuditoryName())
				schedule.getAuditory().setId(auditory.getId());

		for (auto& group : groupList)
			if (schedule.getGroup().getGroupName() == group.getGroupName())
				schedule.getGroup().setId(group.getId());
	}

}

vector<int> ScheduleTable::getIndexesRangeOfSchedule(int number) {
	vector<int> indexes;
	bool foundFirstIndex = false;
	bool foundSecondIndex = false;
	bool sameScheduleWithAnotherWeek = true;

	for (int i = 0, iNext = i + 1, scheduleNumber = 1; i < this->scheduleList.size(); i++, scheduleNumber++) {
		if (scheduleNumber == number && !foundFirstIndex) {
			foundFirstIndex = true;
			indexes.push_back(i);
		}

		iNext = i + 1;
		while (sameScheduleWithAnotherWeek && iNext < this->scheduleList.size()) {
			if (scheduleList[i].getAuditory() == scheduleList[iNext].getAuditory() &&
				scheduleList[i].getGroup() == scheduleList[iNext].getGroup() &&
				scheduleList[i].getWeek() != scheduleList[iNext].getWeek() &&
				scheduleList[i].getDay() == scheduleList[iNext].getDay() &&
				scheduleList[i].getTime() == scheduleList[iNext].getTime()) {
				iNext++;
			}
			else sameScheduleWithAnotherWeek = false;
		}
		if (scheduleNumber == number && !foundSecondIndex) {
			foundSecondIndex = true;
			indexes.push_back(iNext - 1);
			return indexes;
		}

		sameScheduleWithAnotherWeek = true;
		i = iNext - 1;
	}
	return indexes;
}

vector<Schedule>& ScheduleTable::getScheduleList() {
	return scheduleList;
}

vector<Auditory>& ScheduleTable::getAuditoryList() {
	return this->auditoryList;
}

vector<Group>& ScheduleTable::getGroupList() {
	return this->groupList;
}