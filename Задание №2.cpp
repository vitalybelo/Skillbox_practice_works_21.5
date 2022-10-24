#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

/**
 * Единственный параметр который не нужно вводить = название комнаты (для упрощения ввода)
 * Вывод названий комнат enum переопределен для большей ясности и наглядности
 */
enum RoomType { WATER_CLOSET = 0, BATHROOM, KITCHEN, STORAGE,
    LIVING_ROOM, CHILD_ROOM, BED_ROOM, LAUNDRY_ROOM };

ostream& operator<<(ostream& os, const RoomType& rt) {
    switch (rt) {
        case 0: { os << "Санузел"; break; }
        case 1: { os << "Ванная"; break; }
        case 2: { os << "Кухня"; break; }
        case 3: { os << "Кладовка"; break; }
        case 4: { os << "Гостиная"; break; }
        case 5: { os << "Детская"; break; }
        case 6: { os << "Спальня"; break; }
        case 7: { os << "Постирочная"; break; }
        default: { os << "Комнатушка"; break; }
    }
    return os;
}

struct BuildingRoom {
    RoomType name = BED_ROOM;
    float roomArea = 3;
};

struct BuildingFloor {
    float floorHeight = 2.75;
    int roomNumbers = 3;
    vector<BuildingRoom> rooms;
};

struct VillageBuilding {
    string name = "Undefined";
    float occupiedArea = 15;
    bool heatingSystem = true;
    int floorNumbers = 1;
    vector<BuildingFloor> floors;
};

struct VillageSettlement {
    int siteNumber = 33;
    float siteArea = 333;
    int buildingNumbers = 1;
    vector<VillageBuilding> buildings;
};

int main() {
    setlocale(LC_ALL, "RUS");

    char yes;
    VillageSettlement site;
    srand(time(0));

    cout << "Ввод данных дачного участка\n\n";
    cout << "Введите номер участка: ";
    cin >> site.siteNumber;
    cout << "Введите общую площадь участка (кв.метры): ";
    cin >> site.siteArea;
    cout << "Введите количество построек на участке: ";
    cin >> site.buildingNumbers;

    cout << "Ввод данных о постройках на участке:\n";
    for (int b = 0; b < site.buildingNumbers; b++) {
        // ввод общих данных постройки
        VillageBuilding building;
        cout << "\n\tВведите данные о постройке № " << b + 1 << endl;
        cout << "\tВведите название постройки: ";
        cin >> building.name;
        cout << "\tВведите площадь по фундаменту (кв.метры): ";
        cin >> building.occupiedArea;
        cout << "\tВ доме имеется печь или котел ? (если да = 1): ";
        cin >> yes;
        building.heatingSystem = (yes == '1');
        cout << "\tВведите количество этажей постройки: ";
        cin >> building.floorNumbers;
        site.buildings.push_back(building);
        // ввод уточненных данных постройки (этажи, площади и т.п.)
        cout << "\n\t\tПоэтажный ввод данных постройки\n";
        for (int f = 0; f < building.floorNumbers; f++) {
            BuildingFloor floor;
            cout << "\t\tВведите высоту " << f + 1 << "-го этажа: ";
            cin >> floor.floorHeight;
            cout << "\t\tВведите количество комнат на этаже: ";
            cin >> floor.roomNumbers;
            site.buildings[b].floors.push_back(floor);
            cout << "\n\t\t\tВвод данных по каждой комнате\n";
            for (int r = 0; r < floor.roomNumbers; r++) {
                BuildingRoom room;
                room.name = static_cast<RoomType>(rand() % 10);
                cout << "\t\t\tВведите площадь комнаты: " << room.name << " : ";
                cin >> room.roomArea;
                site.buildings[b].floors[f].rooms.push_back(room);
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "\n\n";
    cout << "Участок № " << site.siteNumber << endl;
    cout << "Общая площадь участка: " << site.siteArea << " квадратных метров" << endl;
    cout << "Количество построек на участке: " << site.buildingNumbers << endl;
    cout << "Информация о постройках на участке:\n\n";
    for (int b = 0; b < site.buildingNumbers; b++) {
        cout << "\tПостройка № " << b + 1<< endl;
        cout << "\tНазвание постройки: " << site.buildings[b].name << endl;
        cout << "\tПлощадь постройки в ландшафте: " << site.buildings[b].occupiedArea << " квадратных метров" << endl;
        cout << "\tНаличие печей, котлов, дымоходов: " << (site.buildings[b].heatingSystem ? "да" : "нет") << endl;
        cout << "\tКоличество этажей постройки: " << site.buildings[b].floorNumbers << endl;
        cout << "\t\tПоэтажная информация о постройке\n\n";
        for (int f = 0; f < site.buildings[b].floorNumbers; f++) {
            cout << "\t\tЭтаж № " << f + 1;
            cout << " высота потолка: " << site.buildings[b].floors[f].floorHeight;
            cout << " :: количество комнат " << site.buildings[b].floors[f].roomNumbers << endl;
            cout << "\t\t\tИнформация о комнатах на этаже\n";
            for (int r = 0; r < site.buildings[b].floors[f].roomNumbers; r++) {
                cout << "\t\t\tКомната № " << r + 1 << " ";
                cout << site.buildings[b].floors[f].rooms[r].name << " ";
                cout << " :: площадь = " << site.buildings[b].floors[f].rooms[r].roomArea << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
