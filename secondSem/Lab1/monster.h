#include <iostream>
#include <string>
#include <random>
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

        std::ifstream idread("databases/idstorage.txt");

        idread >> ID;
        ++ID;
        idread.close();

        std::ofstream idwrite("databases/idstorage.txt", std::ofstream::trunc);
        idwrite << ID;
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

        std::mt19937 gen(clock());
        std::uniform_int_distribution<> r1(0, monsterNames.size() - 1),
                r2(1, 50000), r3(0, 1000), r5(1, 4);

        strcpy(name,  monsterNames[r1(gen)]);

        hp = r2(gen);
        ap = r3(gen);

        std::uniform_real_distribution<float> r4(0.00, 1.00);

        attackChance = r4(gen);
        strcpy(attackType, attackTypes[r5(gen)]);

        timeInSec = system_clock::to_time_t(system_clock::now());
        std::string converttime = std::ctime(&timeInSec);
        converttime.pop_back();

        strcpy(time, converttime.c_str());

        std::ifstream idread("databases/idstorage.txt");

        idread >> ID;
        ++ID;
        idread.close();

        std::ofstream idwrite("databases/idstorage.txt", std::ofstream::trunc);
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