#include <windows.h>
#include <iostream>
#include <random>
using namespace std;

struct GamePerson {
    string name = "Mario";  // имя персонажа
    int life = 150;         // уровень жизни, изначально 50 - 150
    int armor = 50;         // уровень брони, изначально 0 - 50
    int damage = 30;        // уровень наносимого врагам ущерба, изначально 10-30
    int x = 0;
    int y = 0;
};

GamePerson createEnemies (int number);

void displayBattleField (GamePerson &hero, GamePerson enemy[], int enemyCount) {

    cout << hero.name << " -> L: " << hero.life << " A: " << hero.armor << endl;



}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    int enemyNumbers = 5;
    GamePerson myHero {"Iron Man",150, 50,20,9,9};
    GamePerson enemy[enemyNumbers];

    for (int i = 0; i < enemyNumbers; i++)
            enemy[i] = createEnemies(i);

    displayBattleField(myHero, enemy, enemyNumbers);



    return 0;
}

GamePerson createEnemies (int number) {
    random_device rd;
    mt19937 gen(rd());

    GamePerson gp;
    gp.name = "Enemy #" + to_string(number);
    gp.life = int (50 + gen() % 100);
    gp.armor = int (gen() % 50);
    gp.damage = int (10 + gen() % 20);
    gp.x = int (gen() % 19);
    gp.y = int (gen() % 19);

    return gp;
}
