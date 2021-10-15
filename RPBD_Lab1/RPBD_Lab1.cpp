#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleDataMapper.h"
#include <iostream>
using namespace std;

void printMenu() {
    for (int i = 0; i < 120; i++) cout << '=';

    cout << endl << '|';
    for (int i = 0; i <= 44; i++) cout << ' ';
    cout << "1) Посмотреть      расписание";
    for (int i = 0; i <= 43; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 44; i++) cout << ' ';
    cout << "2) Добавить        расписание";
    for (int i = 0; i <= 43; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 44; i++) cout << ' ';
    cout << "3) Редактировать   расписание";
    for (int i = 0; i <= 43; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 44; i++) cout << ' ';
    cout << "4) Удалить         расписание";
    for (int i = 0; i <= 43; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 36; i++) cout << ' ';
    cout << "5) Поиск свободной аудитории в заданные часы";
    for (int i = 0; i <= 36; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 23; i++) cout << ' ';
    cout << "6) Поиск свободной аудитории на заданное число часов в указанную неделю";
    for (int i = 0; i <= 22; i++) cout << ' ';
    cout << '|' << endl;

    cout << '|';
    for (int i = 0; i <= 54; i++) cout << ' ';
    cout << "0) Выход";
    for (int i = 0; i <= 54; i++) cout << ' ';
    cout << '|' << endl;

    for (int i = 0; i < 120; i++) cout << '=';
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ScheduleDataMapper dataMapper;
    Schedule tempSchedule;
    string stringChoice;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Посмотреть всё(1) или по группе(2)?" << endl;
            cin >> choice;
            cout << endl;
            if (choice == 1) dataMapper.showAll();
            else {
                cout << "Введите группу: ";
                cin >> stringChoice;
                cout << endl;
                dataMapper.showByGroup(stringChoice);
            }
            break;
        case 2:
            cin >> tempSchedule;
            if (dataMapper.insert(tempSchedule)) cout << "Вставка прошла успешно :)" << endl;
            else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
            break;
        case 3:
            cout << "Введите порядковый номер расписания: ";
            cin >> choice;
            cin >> tempSchedule;
            if (dataMapper.edit(choice, tempSchedule)) cout << "Редактирование прошло успешно :)" << endl;
            else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
            break;
        case 4:
            cout << "Введите порядковый номер расписания: ";
            cin >> choice;
            if (dataMapper.remove(choice)) cout << "Удаление прошло успешно :)" << endl;
            else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
            break;
        case 5:
            cout << "Введите номер аудитории: ";
            cin >> choice;
            cout << "Введите время: ";
            cin >> stringChoice;
            cout << endl;
            dataMapper.findFreeAuditoryByHours(choice, stringChoice);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}