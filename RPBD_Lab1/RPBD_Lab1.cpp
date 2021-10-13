#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleDataMapper.h"
#include <iostream>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ScheduleDataMapper dataMapper;
    Schedule tempSchedule;
    int choice;

    while (true) {
        cout << "========================================" << endl;
        cout << "= 1) Посмотреть      расписание        =" << endl;
        cout << "= 2) Добавить        расписание        =" << endl;
        cout << "= 3) Редактировать   расписание        =" << endl;
        cout << "= 4) Удалить         расписание        =" << endl;
        cout << "= 0) Выход                             =" << endl;
        cout << "========================================" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            dataMapper.show();
            break;
        case 2:
            cout << "Введите: \nНомер аудитории, группа, неделя, день, время" << endl;
            cin >> tempSchedule;
            if (dataMapper.insert(tempSchedule)) cout << "Вставка прошла успешно :)" << endl;
            else cout << "Что-то пошло не так, проверьте правильность ввода" << endl;
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}