#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

struct Employee {
    string firstName = "Incognito";
    string lastName = "Incognito";
    string paymentDay = "22.10.2022";
    int amount = 0;
};

string getCommand();
void printEmployee (Employee &e);
bool getDateString(string &date);
void getDateFromNow (Employee &e);
bool writeEmployeeToFile (Employee &e, const string& fileName);
bool readEmployeeFromFile (Employee &e, const string& fileName);

int main() {
    setlocale(LC_ALL, "RUS");

    char yes;
    string comm;
    Employee employee;

    do {
        comm = getCommand();
        if (comm == "add") {
            cout << "Введите имя и фамилию (через пробел): ";
            cin >> employee.firstName >> employee.lastName;
            cout << "Использовать текущую выдачи ? (y/n): ";
            cin >> yes;
            if (yes == 'y') {
                getDateFromNow(employee);
            } else {
                bool validDate;
                do {
                    cout << "Введите дату выдачи (dd.mm.yyyy): ";
                    validDate = getDateString(employee.paymentDay);
                    if (!validDate) {
                        cout << "Введите пожалуйста дату в формате (дд.мм.гггг)\n";
                    }
                } while (!validDate);
            }
            cout << "Введите сумму выплаты: ";
            cin >> employee.amount;
            writeEmployeeToFile(employee, "../data/employee.data");

        } else if (comm == "list") {
            readEmployeeFromFile(employee, "../data/employee.data");
        }
    } while (comm != "quit");

    return 0;
}

bool getDateString (string &date) {
    int days[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    cin >> date;
    if (date.length() != 10) return false;
    if (date[2] != '.' && date[5] != '.') return false;

    int year = stoi(date.substr(6,4));
    if (year > 2022 || year < 0) return false;
    int month = stoi(date.substr(3,2));
    if (month < 0 || month > 12) return false;
    int day = stoi(date.substr(0,2));
    if (day <= 0 || day > days[month - 1]) return false;

    return true;
}

string getCommand () {
    string command;
    cout << "\nВведите команду (add | list | quit): ";
    cin >> command;
    for (char & i : command) {
        i = (char) tolower(i);
    }
    return command;
}

bool writeEmployeeToFile (Employee &e, const string& fileName) {

    ofstream fileWriter(fileName, ios::out | ios::app);
    if (fileWriter.is_open()) {
        fileWriter << e.firstName << " ";
        fileWriter << e.lastName << " ";
        fileWriter << e.paymentDay << " ";
        fileWriter << e.amount << endl;
        fileWriter.close();
        return true;
    }
    cerr << "Output file path no found. Record denied." << endl;
    return false;
}

bool readEmployeeFromFile (Employee &e, const string& fileName) {

    ifstream fileReader (fileName, ios::in);
    if (fileReader.is_open()) {
        cout << endl;
        while (!fileReader.eof()) {
            if (fileReader >> e.firstName) {
                fileReader >> e.lastName;
                fileReader >> e.paymentDay;
                fileReader >> e.amount;
                printEmployee(e);
            }
        }
        fileReader.close();
        return true;
    }
    cerr << "Output file path no found. Record denied." << endl;
    return false;
}

void getDateFromNow (Employee &e) {
    time_t now = time(0);
    tm *tm = localtime(&now);
    e.paymentDay = "";
    e.paymentDay += to_string(tm->tm_mday) + ".";
    e.paymentDay += to_string(tm->tm_mon + 1) + ".";
    e.paymentDay += to_string(tm->tm_year + 1900);
}

void printEmployee (Employee &e) {
    cout << e.firstName << " " << e.lastName << " :: ";
    cout << e.paymentDay << " :: сумма выплаты = " << e.amount << endl;
}
