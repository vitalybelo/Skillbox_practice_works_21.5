#include <iostream>
#include <fstream>
#include <random>
#include <conio.h>
#include <windows.h>

using namespace std;

// да простят меня боги за глобальные переменные - перекину потом в class .. аминь
const string fileName = "../data/save-game.bin";
const int SIZE_FX = 17;         // размер поля по горизонтали
const int SIZE_FY = 10;         // размер поля по вертикали
const char FREE_CELL = '.';     // знак свободной клетки
const char HERO_CELL = 'H';     // символ отображающая положение героя
const char ENEMY_CELL = 'X';    // символ отображающая положение противников
char field[SIZE_FY][SIZE_FX];   // игровое поле
bool chit_enemy = false;        // режим good - все противники на паузе (в процессе игры жми 'p')

struct GamePerson {
    string name = "Mario";      // имя персонажа
    int life = 150;             // уровень жизни, изначально 50 - 150
    int armor = 50;             // уровень брони, изначально 0 - 50
    int damage = 30;            // уровень наносимого врагам ущерба, изначально 10-30
    int x = 0;                  // координата на игровом поле X
    int y = 0;                  // координата на игровом поле Y
    bool alive = true;          // жив или не жив
};

GamePerson createEnemy (const int& index);

void displayHelp ();
void displayPersonData (GamePerson &p);
void displayBattleField (GamePerson person[], int enemyCount);
bool validKey (const char &a);
void createBattleField (GamePerson p[], int enemyCount);
void writePersons(GamePerson p[], const int& enemyCount);
void readPersons(GamePerson p[], const int& enemyCount);

void movePerson(GamePerson &p, const char direct) {
    int x = p.x;
    int y = p.y;
    char sign = field[p.y][p.x];

    field[p.y][p.x] = FREE_CELL;
    switch (direct) {
        case 'a': // move left
            if (p.x > 0 && field[p.y][p.x - 1] == FREE_CELL) p.x--;
            break;
        case 'd': // move right
            if (p.x < (SIZE_FX - 1) && field[p.y][p.x + 1] == FREE_CELL) p.x++;
            break;
        case 'w': // move up
            if (p.y > 0 && field[p.y - 1][p.x] == FREE_CELL) p.y--;
            break;
        case 's': // move down
            if (p.y < (SIZE_FY - 1) && field[p.y + 1][p.x] == FREE_CELL) p.y++;
            break;
        default: return;
    }

    field[p.y][p.x] = sign;

}

void moveEnemies(GamePerson p[], int enemyCount) {
    random_device rd;
    mt19937 gen(rd());
    for (int i = 1; i <= enemyCount; i++) {
        int move = int(gen() % 4);
        switch (move) {
            case 0: movePerson(p[i], 'a'); break;    // влево
            case 1: movePerson(p[i], 'w'); break;    // вверх
            case 2: movePerson(p[i], 'd'); break;    // вправо
            case 3: movePerson(p[i], 's'); break;    // вниз
        }
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    int enemyNumbers = 5;
    GamePerson person[enemyNumbers + 1];
    person[0] = {"Galaxy Lord", 150, 50, 20, SIZE_FX / 2, SIZE_FY / 2};

    for (int i = 1; i <= enemyNumbers; i++)
        person[i] = createEnemy(i);

    createBattleField(person, enemyNumbers);

    char comm;
    do {
        system("cls");
        displayBattleField(person, enemyNumbers);
        while(kbhit()) _getch();    // clear buffer overflow cycling
        while (!_kbhit()) {         // look for press to instant read it
            comm = (char) tolower(_getch());
            if (validKey(comm)) break;
        }
        switch (comm) {
            case 'i':  // load game
                readPersons(person, enemyNumbers);
                createBattleField(person, enemyNumbers);
                break;
            case 'o': case'u':  // save game
                writePersons(person, enemyNumbers);
                break;
            case 'p':
                chit_enemy = !chit_enemy;
                break;
            default:
                movePerson(person[0], comm);
                if (!chit_enemy) moveEnemies(person, enemyNumbers);
                break;
        }
    } while (comm != 'u');

    return 0;
}

GamePerson createEnemy (const int& index) {
    random_device rd;
    mt19937 gen(rd());

    GamePerson gp;
    gp.name = "Enemy # " + to_string(index);
    gp.life = int (50 + gen() % 100);
    gp.armor = int (gen() % 50);
    gp.damage = int (10 + gen() % 20);
    gp.x = int (gen() % SIZE_FX);
    gp.y = int (gen() % SIZE_FY);

    return gp;
}

void createBattleField (GamePerson p[], int enemyCount) {

    // заполняем карту поля точками
    for (auto & y : field) {
        for (auto &x: y) x = FREE_CELL;
    }
    // расставляем героев по местам
    for (int i = 0; i <= enemyCount; i++) {
        field[p[i].y][p[i].x] = char(i + '0');
    }
}

bool validKey (const char &a) {
    char keys[] {'a','w','d','s','u','i','o','p'};
    int size = sizeof(keys) / sizeof(char);
    for (int i = 0; i < size; i++)
        if (a == keys[i]) return true;
    return false;
}

void displayPersonData (GamePerson &p) {
    cout << p.name;
    if (p.alive) {
        cout << "\tL: " << p.life << "\tA: " << p.armor << "\tD: " << p.damage << endl;
    } else {
        cout << "\t personage is DEAD" << endl;
    }
}

void displayHelp () {
    cout << "\nКоманды управления:\n";
    cout << "A,W,S,D - перемещение по полю\n";
    cout << "I - загрузить сохраненную игру\n";
    cout << "O - сохранить текущую игру\n";
    cout << "U - выход (с сохранением)\n";
}

void displayBattleField (GamePerson person[], int enemyCount) {

    // отображаем параметры игроков
    for (int i = 0; i <= enemyCount; i++)
        displayPersonData(person[i]);

    // отображаем карту в консоли
    char sign;
    cout << endl;
    for (int y = 0; y < SIZE_FY; y++) {
        cout << y + 1 << "\t";
        for (int x = 0; x < SIZE_FX; x++) {
            sign = FREE_CELL;
            if (field[y][x] == '0') {
                sign = HERO_CELL;
            } else if (field[y][x] > '0') {
                sign = ENEMY_CELL;
            }
            cout << sign;
        }
        cout << endl;
    }
    displayHelp();
}

void writePersons(GamePerson p[], const int& enemyCount) {

    ofstream fileWriter(fileName, ios::binary);
    if (fileWriter.is_open()) {
        for (int i = 0; i <= enemyCount; i++) {
            int nameSize = (int) p[i].name.length();
            fileWriter.write((char *) &nameSize, sizeof(nameSize));
            fileWriter.write(p[i].name.c_str(), nameSize);
            fileWriter.write((char *) &p[i].life, sizeof(p[i].life));
            fileWriter.write((char *) &p[i].armor, sizeof(p[i].armor));
            fileWriter.write((char *) &p[i].damage, sizeof(p[i].damage));
            fileWriter.write((char *) &p[i].alive, sizeof(p[i].alive));
            fileWriter.write((char *) &p[i].x, sizeof(p[i].x));
            fileWriter.write((char *) &p[i].y, sizeof(p[i].y));
        }
        fileWriter.close();
    }
}

void readPersons(GamePerson p[], const int& enemyCount) {

    ifstream fileReader(fileName, ios::binary);
    if (fileReader.is_open()) {
        int nameSize;
        for (int i = 0; i <= enemyCount; i++) {
            fileReader.read((char *) &nameSize, sizeof(nameSize));
            p[i].name.resize(nameSize);
            fileReader.read((char *) p[i].name.c_str(), nameSize);
            fileReader.read((char *) &p[i].life, sizeof(p[i].life));
            fileReader.read((char *) &p[i].armor, sizeof(p[i].armor));
            fileReader.read((char *) &p[i].damage, sizeof(p[i].damage));
            fileReader.read((char *) &p[i].alive, sizeof(p[i].alive));
            fileReader.read((char *) &p[i].x, sizeof(p[i].x));
            fileReader.read((char *) &p[i].y, sizeof(p[i].y));
        }
        fileReader.close();
    } else {
        cerr << "File not found\n";
    }
}
