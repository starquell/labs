#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include "TextTable.h"
#include <map>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std::chrono;
using std::cout;
using std::cin;


class Monster {

public:

    char name[20];
    int hp;                  // health points
    int ap;                  // attack points
    double attackChance;
    char attackType[20];
    time_t timeInSec;
    char time[40];
    int ID;

    static std::map<int, const char*> attackTypes;


    Monster(const std::string &name, int hp, int ap, double attackChance, const std::string &attackType){

        strcpy (this->name, name.c_str());
        this->hp = hp;
        this->ap = ap;
        this->attackChance = attackChance;
        strcpy (this->attackType,  attackType.c_str());
        this->timeInSec = system_clock::to_time_t(system_clock::now());

        std::string converttime = std::ctime(&timeInSec);
        converttime.pop_back();

        strcpy (this->time, converttime.c_str());

        std::ifstream idread("idstorage.txt");

        idread >> ID;
        ++ID;
        idread.close();

        std::ofstream idwrite("idstorage.txt", std::ofstream::trunc);
        idwrite << ID;

        cout << this->timeInSec;
        cout << std::endl << this->time;
    }


    Monster(const std::string &name, int hp, int ap, double attackChance, const std::string &attackType, time_t timeInSec, int ID) {

        strcpy(this->name, name.c_str());
        this->hp = hp;
        this->ap = ap;
        this->attackChance = attackChance;
        strcpy(this->attackType, attackType.c_str());
        this->timeInSec = timeInSec;

        std::string converttime = std::ctime(&timeInSec);
        converttime.pop_back();

        strcpy(this->time, converttime.c_str());
        this->ID = ID;
    }

    Monster() {

        static const std::array<const char*, 9> monsterNames = {

                "Agnesoid", "Skyrdos",
                "Morrowind", "Pneumothorax",
                "Serpentoid", "Gemafilios",
                "Ilabeas", "Gavresh",
                "Paradontax"
        };

        static std::map<int, const char*> attackTypes = {
                {1, "Double attack"},
                {2, "Repeat attack"},
                {3, "Heal"},
                {4, "Paralyse enemy"}
        };

        strcpy(name,  monsterNames[rand() % monsterNames.size()]);
        hp = rand() % 50000 + 1;
        ap = rand() % 1001;
        attackChance = (rand() % 100) / 100.;
        strcpy(attackType, attackTypes[rand() % 4 + 1]);
        timeInSec = system_clock::to_time_t(system_clock::now());
        std::string converttime = std::ctime(&timeInSec);
        converttime.pop_back();

        strcpy(time, converttime.c_str());

        std::ifstream idread("idstorage.txt");

        idread >> ID;
        ++ID;
        idread.close();

        std::ofstream idwrite("idstorage.txt", std::ofstream::trunc);
        idwrite << ID;
    };

    void addTableInfo (TextTable &t) {

        t.add(" "  + std::string(name) + " ");
        t.add(" " + std::to_string (hp) + " ");
        t.add(" " + std::to_string (ap) + " ");
        t.add(" " + std::to_string (attackChance) + " ");
        t.add(" " + std::string(attackType) + " ");
        t.add(" " + std::string(time) + " ");
        t.endOfRow();
    }

};

decltype(Monster::attackTypes) Monster::attackTypes = {
        {1, "Double attack"},
        {2, "Repeat attack"},
        {3, "Heal"},
        {4, "Paralyse enemy"}
};