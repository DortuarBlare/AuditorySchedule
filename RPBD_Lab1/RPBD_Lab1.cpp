#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include "Schedule.h"
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
    currentString = "  б) расписание у группы";
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

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  г) все аудитории";
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

    currentString = "3) Редактировать в расписании";
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
    currentString = "  а) все поля";
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

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  г) день недели";
    cout << currentString;
    printedSymbolsInRow += currentString.length();
    for (int i = 1; i < width - printedSymbolsInRow; i++) cout << ' ';
    printedSymbolsInRow = 0;
    cout << '|' << endl;

    cout << '|'; printedSymbolsInRow++;
    for (int i = 1; i <= symbolsToPrint; i++, printedSymbolsInRow++)
        cout << ' ';
    currentString = "  д) время";
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

    currentString = "5) Поиск свободной аудитории в заданные часы";
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
            case 'а':
                dataMapper.showAll();
                break;
            case 'б':
                cout << "Введите группу: ";
                cin >> stringChoice;
                cout << endl;
                dataMapper.showByGroup(stringChoice);
                break;
            case 'в':
                dataMapper.showAllGroups();
                break;
            case 'г':
                dataMapper.showAllAuditories();
                break;
            default:
                break;
            }
            break;
        case 2:
            cin >> charChoice;
            switch (charChoice) {
            case 'а':
                cin >> tempSchedule;
                if (dataMapper.insertSchedule(tempSchedule)) cout << "Вставка прошла успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'б':
                cout << "Введите аудиторию: ";
                cin >> stringChoice;
                if (dataMapper.insertAuditory(stringChoice)) cout << "Вставка прошла успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'в':
                cout << "Введите группу: ";
                cin >> stringChoice;
                if (dataMapper.insertGroup(stringChoice)) cout << "Вставка прошла успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            default:
                break;
            }
            break;
        case 3:
            cin >> charChoice;
            switch (charChoice) {
            case 'а':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cin >> tempSchedule;
                if (dataMapper.fullEdit(choice, tempSchedule)) cout << "Редактирование прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'б':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новую аудиторию: ";
                cin >> stringChoice;
                if (dataMapper.edit(choice, Schedule(stringChoice, "...", "...", "...", "...")))
                    cout << "Редактирование прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'в':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новую группу: ";
                cin >> stringChoice;
                if (dataMapper.edit(choice, Schedule("...", stringChoice, "...", "...", "...")))
                    cout << "Редактирование прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'г':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новый день недели: ";
                cin >> stringChoice;
                if (dataMapper.edit(choice, Schedule("...", "...", "...", stringChoice, "...")))
                    cout << "Редактирование прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'д':
                cout << "Введите порядковый номер расписания: ";
                cin >> choice;
                cout << "Введите новое время: ";
                cin >> stringChoice;
                if (dataMapper.edit(choice, Schedule("...", "...", "...", "...", stringChoice)))
                    cout << "Редактирование прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
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
                if (dataMapper.removeSchedule(choice)) cout << "Удаление прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'б':
                cout << "Введите аудиторию для удаления: ";
                cin >> stringChoice;
                if (dataMapper.removeAuditory(stringChoice)) cout << "Удаление прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            case 'в':
                cout << "Введите группу для удаления: ";
                cin >> stringChoice;
                if (dataMapper.removeGroup(stringChoice)) cout << "Удаление прошло успешно :)" << endl;
                else cout << "Что-то пошло не так, проверьте правильность ввода данных :(" << endl;
                break;
            default:
                break;
            }
            break;
        case 5:
            cout << "Введите время: ";
            cin >> stringChoice;
            cout << endl;
            dataMapper.findFreeAuditoryByTime(stringChoice);
            break;
        case 6:
            int weekNumber;
            cout << "Введите количество часов: ";
            cin >> choice;
            cout << "Введите номер недели: ";
            cin >> weekNumber;
            dataMapper.findFreeAuditoryByNumberOfHours(choice, weekNumber);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}