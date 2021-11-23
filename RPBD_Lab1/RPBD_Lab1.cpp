#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
#include "ScheduleTable.h"
#include "ScheduleDataMapper.h"
#include <iostream>
using namespace std;

void printMenu(int width) {
    int printedSymbolsInRow = 0;
    int symbolsToPrint = 0;
    for (int i = 0; i < width; i++) cout << '=';

    string currentString = "1) Посмотреть";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << endl << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << " \\"; printedSymbolsInRow += 2;
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  а) всё расписание";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  б) все аудитории";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  в) все группы";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "2) Добавить";
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << " \\"; printedSymbolsInRow += 2;
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  а) расписание";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  б) аудиторию";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  в) группу";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "3) Редактировать";
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << " \\"; printedSymbolsInRow += 2;
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  а) все поля в расписании";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  б) аудиторию в расписании";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  в) группу в расписании";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  г) день недели в расписании";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  д) время в расписании";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  е) аудиторию";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  ж) группу";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "4) Удалить";
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << " \\"; printedSymbolsInRow += 2;
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  а) расписание";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  б) аудиторию";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  в) группу";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "5) Поиск свободной аудитории в заданные часы в течение всего семестра";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "6) Поиск свободной аудитории на заданное число часов в указанную неделю";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "7) Сохранить все в базу данных";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "8) Загрузить все из базы данных";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|';
    for (int i = 1; i <= width - 2; i++) cout << ' ';
    cout << '|' << endl;

    currentString = "0) Выход";
    symbolsToPrint = (width / 2) - (currentString.length() / 2);
    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    for (int i = 0; i < width; i++) cout << '=';
    cout << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HANDLE hWndConsole{};
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    
    ScheduleDataMapper dataMapper;
    ScheduleTable scheduleTable;
    Schedule tempSchedule;
    string stringChoice;
    int choice;
    char charChoice;

    while (true) {
        if (hWndConsole = GetStdHandle(-12)) {
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
                printMenu(consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1);
        }
        cin >> choice;
        switch (choice) {
        case 1:
            cin >> charChoice;
            switch (charChoice) {
            case 'а': {
                scheduleTable.showAll();
                break;
            }
            case 'б':
                scheduleTable.showAllAuditories();
                break;
            case 'в':
                scheduleTable.showAllGroups();
                break;
            default:
                break;
            }
            break;
        case 2:
            cin >> charChoice;
            switch (charChoice) {
            case 'а': {
                string auditory;
                string group;
                string week;
                string day;
                string startTime;
                string endTime;
                bool success = false;
                
                cout << "Введите аудиторию: ";
                cin >> auditory;
                cout << "Введите группу: ";
                cin >> group;
                cout << "Введите недели: ";
                cin.ignore();
                getline(cin, week);
                cout << "Введите день недели: ";
                cin >> day;
                cout << "Введите начальное время: ";
                cin >> startTime;
                cout << "Введите конечное время: ";
                cin >> endTime;

                if (scheduleTable.insertSchedule(auditory, group, week, day, startTime, endTime))
                    cout << "Вставка расписания прошла успешно :)" << endl;
                else 
                    cout << "Вставка расписания прошла неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            }
            case 'б':
                cout << "Введите аудиторию: ";
                cin >> stringChoice;

                if (scheduleTable.insertAuditory(stringChoice))
                    cout << "Вставка аудитории прошла успешно :)" << endl;
                else 
                    cout << "Вставка аудитории прошла неудачно. Проверьте правильность ввода данных :(" << endl;
                
                break;
            case 'в':
                cout << "Введите группу: ";
                cin >> stringChoice;

                if (scheduleTable.insertGroup(stringChoice))
                    cout << "Вставка группы прошла успешно :)" << endl;
                else cout << "Вставка группы прошла неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            default:
                break;
            }
            break;
        case 3:
            cin >> charChoice;
            switch (charChoice) {
            case 'а': {
                string auditory;
                string group;
                string week;
                string day;
                string startTime;
                string endTime;
                bool success = false;

                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новую аудиторию: ";
                cin >> auditory;
                cout << "Введите новую группу: ";
                cin >> group;
                cout << "Введите новые недели: ";
                cin.ignore();
                getline(cin, week);
                cout << "Введите новый день недели: ";
                cin >> day;
                cout << "Введите новое начальное время: ";
                cin >> startTime;
                cout << "Введите новое конечное время: ";
                cin >> endTime;
                
                if (scheduleTable.fullScheduleEdit(choice, auditory, group, week, day, startTime, endTime))
                    cout << "Редактирование расписания прошло успешно :)" << endl;
                else
                    cout << "Редактирование расписания прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                
                break;
            }
            case 'б': {
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новую аудиторию: ";
                cin >> stringChoice;

                if (scheduleTable.editAuditoryInSchedule(choice, stringChoice))
                    cout << "Редактирование аудитории в расписании прошло успешно :)" << endl;
                else
                    cout << "Редактирование аудитории в расписании прошло неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            }
            case 'в':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новую группу: ";
                cin >> stringChoice;

                if (scheduleTable.editGroupInSchedule(choice, stringChoice))
                    cout << "Редактирование группы в расписании прошло успешно :)" << endl;
                else
                    cout << "Редактирование группы в расписании прошло неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            case 'г':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новый день недели: ";
                cin >> stringChoice;

                if (scheduleTable.editDayInSchedule(choice, stringChoice))
                    cout << "Редактирование дня недели в расписании прошло успешно :)" << endl;
                else
                    cout << "Редактирование дня недели в расписании прошло неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            case 'д': {
                string newEndTime;

                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новое начальное время: ";
                cin >> stringChoice;
                cout << "Введите новое конечное время: ";
                cin >> newEndTime;

                if (scheduleTable.editTimeInSchedule(choice, stringChoice, newEndTime))
                    cout << "Редактирование времени в расписании прошло успешно :)" << endl;
                else
                    cout << "Редактирование времени в расписании прошло неудачно. Проверьте правильность ввода данных :(" << endl;

                break;
            }
            case 'е': {
                string oldAuditory;
                cout << "Введите старую аудиторию: ";
                cin >> oldAuditory;
                cout << "Введите новую аудиторию: ";
                cin >> stringChoice;
                if (scheduleTable.editAuditory(oldAuditory, stringChoice))
                    cout << "Редактирование аудитории прошло успешно :)" << endl;
                else
                    cout << "Редактирование аудитории прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                break;
            }
            case 'ж': {
                string oldGroup;
                cout << "Введите старую группу: ";
                cin >> oldGroup;
                cout << "Введите новую группу: ";
                cin >> stringChoice;
                if (scheduleTable.editGroup(oldGroup, stringChoice))
                    cout << "Редактирование группы прошло успешно :)" << endl;
                else
                    cout << "Редактирование группы прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                break;
            }
            default:
                break;
            }
            break;
        case 4:
            cin >> charChoice;
            switch (charChoice) {
            case 'а':
                cout << "Введите порядковый номер расписания для удаления: ";
                cin >> choice;
                if (scheduleTable.removeSchedule(choice))
                    cout << "Удаление расписания прошло успешно :)" << endl;
                else 
                    cout << "Удаление расписания прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                break;
            case 'б':
                cout << "Введите аудиторию для удаления: ";
                cin >> stringChoice;
                if (scheduleTable.removeAuditory(stringChoice))
                    cout << "Удаление аудитории прошло успешно :)" << endl;
                else
                    cout << "Удаление аудитории прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                break;
            case 'в':
                cout << "Введите группу для удаления: ";
                cin >> stringChoice;
                if (scheduleTable.removeGroup(stringChoice))
                    cout << "Удаление группы прошло успешно :)" << endl;
                else
                    cout << "Удаление группы прошло неудачно. Проверьте правильность ввода данных :(" << endl;
                break;
            default:
                break;
            }
            break;
        case 5: {
            string endTime;

            cout << "Введите начальное время: ";
            cin >> stringChoice;
            cout << "Введите конечное время: ";
            cin >> endTime;
            cout << endl;
            scheduleTable.findFreeAuditoryByTime(stringChoice, endTime);

            break;
        }
        case 6:
            int weekNumber;
            cout << "Введите количество часов: ";
            cin >> choice;
            cout << "Введите номер недели: ";
            cin >> weekNumber;
            scheduleTable.findFreeAuditoryByNumberOfHours(choice, weekNumber);
            break;
        case 7:
            dataMapper.saveAll(scheduleTable);
            break;
        case 8:
            dataMapper.loadAll(scheduleTable);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}