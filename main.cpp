#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

struct VectorXY {
    float x = 0.0;
    float y = 0.0;
};

string getCommand ();
VectorXY getVectorInput (const string& title);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    string comm;
    do {
        comm = getCommand();
        if (comm == "add") {

            cout << "Сложение 2х векторов Ax,Ay + Bx,By:\n";
            auto a = getVectorInput("\tВведите координаты 1-го вектора (Ax,Ay) через пробел: ");
            auto b = getVectorInput("\tВведите координаты 2-го вектора (Bx,By) через пробел: ");
            cout << "\tРезультат А + В = ( " << (a.x + b.x) << " , " << (a.y + b.y) << " )\n";
        } else if (comm == "sub") {

            cout << "Вычитание 2х векторов Ax,Ay - Bx,By:\n";
            auto a = getVectorInput("\tВведите координаты 1-го вектора (Ax,Ay) через пробел: ");
            auto b = getVectorInput("\tВведите координаты 2-го вектора (Bx,By) через пробел: ");
            cout << "\tРезультат А - В = ( " << (a.x - b.x) << " , " << (a.y - b.y) << " )\n";
        } else if (comm == "scale") {

            cout << "Умножение вектора Ax,Ay на скаляр B:\n";
            auto a = getVectorInput("\tВведите координаты вектора (Ax,Ay) через пробел: ");
            cout << "\tВведите значение скаляра Bx (float): ";
            float b; cin >> b;
            cout << "\tРезультат Аx,Ay * В = ( " << (a.x * b) << " , " << (a.y * b) << " )\n";
        } else if (comm == "length") {

            cout << "Вычисление длины вектора Ax,Ay:\n";
            auto a = getVectorInput("\tВведите координаты вектора (Ax,Ay) через пробел: ");
            auto length = sqrtf(powf(a.x,2) + powf(a.y,2));
            cout << "\tДлина вектора ( " << a.x << " , " << a.y << " ) = " << length << endl;
        } else if (comm == "normalize") {

            cout << "Нормализация вектора Ax,Ay:\n";
            auto a = getVectorInput("\tВведите координаты вектора (Ax,Ay) через пробел: ");
            auto length = sqrtf(powf(a.x,2) + powf(a.y,2));
            auto ax = a.x / length;
            auto ay = a.y / length;
            cout << "\tНормализованный вектор ( " << a.x << "/" << length;
            cout << ", " << a.y << "/" << length << " ) = ( " << ax << ", " << ay << " )\n";
        }
    } while (comm != "quit");


    return 0;
}

string getCommand () {
    string command;
    cout << "\nВведите команду (add | sub | scale | length | normalize | quit): ";
    cin >> command;
    for (char & i : command) {
        i = (char) tolower(i);
    }
    return command;
}

VectorXY getVectorInput (const string& title) {
    VectorXY a;
    cout << title;
    cin >> a.x >> a.y;
    return a;
}
