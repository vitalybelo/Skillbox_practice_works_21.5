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

            cout << "�������� 2� �������� Ax,Ay + Bx,By:\n";
            auto a = getVectorInput("\t������� ���������� 1-�� ������� (Ax,Ay) ����� ������: ");
            auto b = getVectorInput("\t������� ���������� 2-�� ������� (Bx,By) ����� ������: ");
            cout << "\t��������� � + � = ( " << (a.x + b.x) << " , " << (a.y + b.y) << " )\n";
        } else if (comm == "sub") {

            cout << "��������� 2� �������� Ax,Ay - Bx,By:\n";
            auto a = getVectorInput("\t������� ���������� 1-�� ������� (Ax,Ay) ����� ������: ");
            auto b = getVectorInput("\t������� ���������� 2-�� ������� (Bx,By) ����� ������: ");
            cout << "\t��������� � - � = ( " << (a.x - b.x) << " , " << (a.y - b.y) << " )\n";
        } else if (comm == "scale") {

            cout << "��������� ������� Ax,Ay �� ������ B:\n";
            auto a = getVectorInput("\t������� ���������� ������� (Ax,Ay) ����� ������: ");
            cout << "\t������� �������� ������� Bx (float): ";
            float b; cin >> b;
            cout << "\t��������� �x,Ay * � = ( " << (a.x * b) << " , " << (a.y * b) << " )\n";
        } else if (comm == "length") {

            cout << "���������� ����� ������� Ax,Ay:\n";
            auto a = getVectorInput("\t������� ���������� ������� (Ax,Ay) ����� ������: ");
            auto length = sqrtf(powf(a.x,2) + powf(a.y,2));
            cout << "\t����� ������� ( " << a.x << " , " << a.y << " ) = " << length << endl;
        } else if (comm == "normalize") {

            cout << "������������ ������� Ax,Ay:\n";
            auto a = getVectorInput("\t������� ���������� ������� (Ax,Ay) ����� ������: ");
            auto length = sqrtf(powf(a.x,2) + powf(a.y,2));
            auto ax = a.x / length;
            auto ay = a.y / length;
            cout << "\t��������������� ������ ( " << a.x << "/" << length;
            cout << ", " << a.y << "/" << length << " ) = ( " << ax << ", " << ay << " )\n";
        }
    } while (comm != "quit");


    return 0;
}

string getCommand () {
    string command;
    cout << "\n������� ������� (add | sub | scale | length | normalize | quit): ";
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
