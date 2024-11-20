#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <windows.h>
#include <Windows.h> 
using namespace std;

// ��������� �������
void CreateRoutesFile(const char* filename);
void PrintRouteByNumber(const char* filename, int routeNumber);
void SortRoutesFile(const char* filename);
void PrintAllRoutes(const char* filename);
void AddRoutesToFile(const char* filename);

void CreateRoutesFile(const char* filename)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    char ch;
    do {
        string startPoint, endPoint;
        int routeNumber;
        cin.get(); // ������� �����
        cin.sync();
        cout << "������ ���������� �����: ";
        getline(cin, startPoint);
        cout << "������ ������� �����: ";
        getline(cin, endPoint);
        cout << "������ ����� ��������: ";
        cin >> routeNumber;

        fout << startPoint << " " << endPoint << " " << routeNumber << endl;

        cout << "������ �� �������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "��� ��������� � ����: " << filename << endl;
}

void PrintRouteByNumber(const char* filename, int routeNumber) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    string startPoint, endPoint;
    int number;
    bool found = false;

    while (fin >> startPoint >> endPoint >> number) {
        if (number == routeNumber) {
            cout << "============================================================" << endl;
            cout << "|  ���������� �����  |  ʳ������ �����  |  ����� ��������  |" << endl;
            cout << "============================================================" << endl;
            cout << "| " << setw(19) << left << startPoint
                << "| " << setw(17) << left << endPoint
                << "| " << setw(17) << left << number << "|" << endl;
            cout << "============================================================" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "������� �� ������� " << routeNumber << " �� ��������." << endl;
    }

    fin.close();
}

void SortRoutesFile(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
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

    // ���������� ����� � ���������� �����
    while (fin >> routes[size].startPoint >> routes[size].endPoint >> routes[size].routeNumber) {
        size++;
    }
    fin.close();

    // ����������
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (routes[j].routeNumber > routes[j + 1].routeNumber) {
                temp = routes[j];
                routes[j] = routes[j + 1];
                routes[j + 1] = temp;
            }
        }
    }

    // ����� ������������ ����� ����� � ����
    ofstream fout(filename);
    for (int i = 0; i < size; i++) {
        fout << routes[i].startPoint << " " << routes[i].endPoint << " " << routes[i].routeNumber << endl;
    }
    fout.close();

    cout << "�������� ����������� �� �������." << endl;
}

void PrintAllRoutes(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    string startPoint, endPoint;
    int routeNumber;

    cout << "============================================================" << endl;
    cout << "|  ���������� �����  |  ʳ������ �����  |  ����� ��������  |" << endl;
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
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    char ch;
    do {
        string startPoint, endPoint;
        int routeNumber;
        cin.get(); // ������� �����
        cin.sync();
        cout << "������ ���������� �����: ";
        getline(cin, startPoint);
        cout << "������ ������� �����: ";
        getline(cin, endPoint);
        cout << "������ ����� ��������: ";
        cin >> routeNumber;

        fout << startPoint << " " << endPoint << " " << routeNumber << endl;

        cout << "������ �� �������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "��� ������ �� �����: " << filename << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char filename[100];
    cout << "������ ��'� �����: ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl;
        cout << "������ ��:" << endl;
        cout << " [1] - �������� ���� ��������" << endl;
        cout << " [2] - ������� ������� �� �������" << endl;
        cout << " [3] - ��������� �������� � ����" << endl;
        cout << " [4] - ������� �� ��������" << endl;
        cout << " [5] - ������ �������� �� �����" << endl;
        cout << " [0] - �����" << endl;
        cout << "��� ����: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateRoutesFile(filename);
            break;
        case 2: {
            int routeNumber;
            cout << "������ ����� ��������: ";
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
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
