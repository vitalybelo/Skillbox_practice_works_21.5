#include <iostream>
#include <windows.h>
using namespace std;

struct VectorXY {
    float x = 0.0;
    float y = 0.0;
};

string getCommand () {
    string command;
    cout << "\n¬ведите команду (add | sub | scale | length | normalize | quit): ";
    cin >> command;
    for (char & i : command) {
        i = (char) tolower(i);
    }
    return command;
}

VectorXY getVectorInput () {
    VectorXY a;
    cout << "¬ведите координаты вектора (x,y) через пробел: ";
    cin >> a.x >> a.y;
    return a;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    string comm;
    do {
        comm = getCommand();
        if (comm == "add") {
            VectorXY a = getVectorInput();
        }


    } while (comm != "quit");


    return 0;
}
