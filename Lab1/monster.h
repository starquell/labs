#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include "TextTable.h"

using std::cout;
using std::cin;

class Monster {

    std::string name;
    int hp;                  // health points
    int ap;                  // attack points
    double attackChance;
    std::string attackType;

public:

    Monster(std::string name, int hp, int ap, double attackChance, std::string attackType){

        this->name = name;
        this->hp = hp;
        this->ap = ap;
        this->attackChance = attackChance;
        this->attackType = attackType;
    }

    Monster() {

        static const std::array<std::string, 9> monsterNames = {

                "Agnesha", "Skyrdos",
                "Morrowind", "Pneumothorax",
                "Serpentoid", "Gemafilios",
                "Ilabeas", "Gavresh",
                "Paradontax"
        };

        static const std::array<std::string, 4> attackTypes = {
                "Double damage",
                "Repeat attack",
                "Heal",
                "Paralyse enemy"
        };

        name = monsterNames[rand() % monsterNames.size()];
        hp = rand() % 50000 + 1;
        ap = rand() % 1001;
        attackChance = (rand() % 100) / 100.;
        attackType = attackTypes[rand() % attackTypes.size()];

    };


    void addTableInfo(TextTable &t) {

        t.add(" "  + name + " ");
        t.add(" " + std::to_string (hp) + " ");
        t.add(" " + std::to_string (ap) + " ");
        t.add(" " + std::to_string (attackChance) + " ");
        t.add(" " + attackType + " ");
        t.endOfRow();
    }
};

void addMonster(std::vector <Monster> &monsters){

    std::string name;
    int hp;
    int ap;
    double attackChance;
    int attacktype;
    std::string attackType;

    cout << "Enter monster's name:   ";
    cin >> name;

    cout << "Set health (0 - 50000):   ";
    do {
        cin >> hp;
    } while (hp < 0 || hp > 50000);

    cout << "Set attack (0 - 1000):   ";
    do {
        cin >> ap;
    } while (ap < 0 || ap > 1000);

    cout << "Set chance of special attack (0 - 1):   ";
    do{
        cin >> attackChance;
    } while (attackChance < 0 || attackChance > 1);

    cout << "Choose type of special ability :   1. Double damage\n"
         << "                                   2. Repeat attack\n"
         << "                                   3. Heal\n"
         << "                                   4. Paralyse enemy\n";

    cin >> attacktype;

    switch (attacktype){

        case 1: attackType = "Double damage";
            break;
        case 2: attackType = "Repeat attack";
            break;
        case 3: attackType = "Heal";
            break;
        case 4: attackType = "Paralyse enemy";
            break;
    }

    Monster m(name, hp, ap, attackChance, attackType);
    monsters.push_back(m);
}