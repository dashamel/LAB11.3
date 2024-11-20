#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <windows.h>
#include <Windows.h> 
using namespace std;

// Прототипи функцій
void CreateRoutesFile(const char* filename);
void PrintRouteByNumber(const char* filename, int routeNumber);
void SortRoutesFile(const char* filename);
void PrintAllRoutes(const char* filename);
void AddRoutesToFile(const char* filename);

void CreateRoutesFile(const char* filename)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    char ch;
    do {
        string startPoint, endPoint;
        int routeNumber;
        cin.get(); // Очищуємо буфер
        cin.sync();
        cout << "Введіть початковий пункт: ";
        getline(cin, startPoint);
        cout << "Введіть кінцевий пункт: ";
        getline(cin, endPoint);
        cout << "Введіть номер маршруту: ";
        cin >> routeNumber;

        fout << startPoint << " " << endPoint << " " << routeNumber << endl;

        cout << "Додати ще маршрут? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Дані збережено у файл: " << filename << endl;
}

void PrintRouteByNumber(const char* filename, int routeNumber) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    string startPoint, endPoint;
    int number;
    bool found = false;

    while (fin >> startPoint >> endPoint >> number) {
        if (number == routeNumber) {
            cout << "============================================================" << endl;
            cout << "|  Початковий пункт  |  Кінцевий пункт  |  Номер маршруту  |" << endl;
            cout << "============================================================" << endl;
            cout << "| " << setw(19) << left << startPoint
                << "| " << setw(17) << left << endPoint
                << "| " << setw(17) << left << number << "|" << endl;
            cout << "============================================================" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Маршрут із номером " << routeNumber << " не знайдено." << endl;
    }

    fin.close();
}

void SortRoutesFile(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    struct Route {
        string startPoint;
        string endPoint;
        int routeNumber;
    };

    Route temp;
    Route routes[100];
    int size = 0;

    // Зчитування даних у тимчасовий масив
    while (fin >> routes[size].startPoint >> routes[size].endPoint >> routes[size].routeNumber) {
        size++;
    }
    fin.close();

    // Сортування
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (routes[j].routeNumber > routes[j + 1].routeNumber) {
                temp = routes[j];
                routes[j] = routes[j + 1];
                routes[j + 1] = temp;
            }
        }
    }

    // Запис відсортованих даних назад у файл
    ofstream fout(filename);
    for (int i = 0; i < size; i++) {
        fout << routes[i].startPoint << " " << routes[i].endPoint << " " << routes[i].routeNumber << endl;
    }
    fout.close();

    cout << "Маршрути відсортовано за номером." << endl;
}

void PrintAllRoutes(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    string startPoint, endPoint;
    int routeNumber;

    cout << "============================================================" << endl;
    cout << "|  Початковий пункт  |  Кінцевий пункт  |  Номер маршруту  |" << endl;
    cout << "============================================================" << endl;

    while (fin >> startPoint >> endPoint >> routeNumber) {
        cout << "| " << setw(19) << left << startPoint
            << "| " << setw(17) << left << endPoint
            << "| " << setw(17) << left << routeNumber << "|" << endl;
    }

    cout << "============================================================" << endl;
     
    fin.close();
}

void AddRoutesToFile(const char* filename) {
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    char ch;
    do {
        string startPoint, endPoint;
        int routeNumber;
        cin.get(); // Очищуємо буфер
        cin.sync();
        cout << "Введіть початковий пункт: ";
        getline(cin, startPoint);
        cout << "Введіть кінцевий пункт: ";
        getline(cin, endPoint);
        cout << "Введіть номер маршруту: ";
        cin >> routeNumber;

        fout << startPoint << " " << endPoint << " " << routeNumber << endl;

        cout << "Додати ще маршрут? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Дані додано до файлу: " << filename << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char filename[100];
    cout << "Введіть ім'я файлу: ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl;
        cout << "Оберіть дію:" << endl;
        cout << " [1] - Створити файл маршрутів" << endl;
        cout << " [2] - Вивести маршрут за номером" << endl;
        cout << " [3] - Сортувати маршрути у файлі" << endl;
        cout << " [4] - Вивести всі маршрути" << endl;
        cout << " [5] - Додати маршрути до файлу" << endl;
        cout << " [0] - Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateRoutesFile(filename);
            break;
        case 2: {
            int routeNumber;
            cout << "Введіть номер маршруту: ";
            cin >> routeNumber;
            PrintRouteByNumber(filename, routeNumber);
            break;
        }
        case 3:
            SortRoutesFile(filename);
            break;
        case 4:
            PrintAllRoutes(filename);
            break;
        case 5:
            AddRoutesToFile(filename);
            break;
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
