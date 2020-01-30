#include <thread>
#include <vector>
#include <cassert>
#include <functional>

using namespace std::chrono_literals;
using std::this_thread::sleep_for;

void menuOut (const std::string& begin, const std::string& end){        // reading and cout menu from "selector.txt"

    std::ifstream selector("../selector.txt");
    if (!selector.is_open())
        throw std::runtime_error {"\"selector.txt\" is needed for interactive mode."};

    std::string s;
    bool ourtext{};

    if (begin == "bof")
        ourtext = true;

    while (!selector.eof()) {

        if (s == end)
            break;

        getline(selector, s);

        if (ourtext)
            cout << s << '\n';      // start reading from defined position

        if (s == begin)
            ourtext = true;
    }
}

void monstersOut(std::vector <Monster> &monsters){

    TextTable t('-', '|', '+');

    for (auto &i : monsters)
        i.addTableInfo(t);

    cout << t;
    sleep_for(1.25s);
}

void saveToFile (std::vector <Monster> &monsters,  const std::string &path = "../databases/database.txt"){

    std::ofstream file(path, std::ofstream::app);

    for (auto& i: monsters){

        file << i.name << ' ';
        file << i.hp << ' ';
        file << i.ap << ' ';
        file << i.attackChance << ' ';
        file << i.timeInSec << ' ';
        file << i.ID << ' ';
        file << i.attackType << '\n';
    }
}

void readFromFile (std::vector <Monster> &monsters, const std::string &path = "../databases/database.txt"){

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error {"\"../databases/database.txt\" is needed for reading from file"};

    std::string name, attackType;
    int hp, ap, ID;
    double attackChance;
    char trash;
    time_t timeInSec;

    while (!file.eof()){

        file >> name;
        file >> hp;
        file >> ap;
        file >> attackChance;
        file >> timeInSec;
        file >> ID;
        file.get(trash);
        getline(file, attackType);

        monsters.emplace_back(name, hp, ap, attackChance, attackType, timeInSec, ID);
    }
    monsters.pop_back();  // deleting trash
}

Monster findInFile (int key, const std::string &path = "../databases/benchmark.txt"){        //benchmark function

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error {"\"../databases/benchmark.txt\" is needed for reading from file"};

    std::string name, attackType;
    int hp, ap, ID;
    double attackChance;
    char trash;
    time_t timeInSec;

    while (!file.eof()) {
        file >> name;
        file >> hp;
        file >> ap;
        file >> attackChance;
        file >> timeInSec;
        file >> ID;
        file.get(trash);
        getline(file, attackType);

        if (attackType == Monster::attackTypes[key])
            return {name, hp, ap, attackChance, attackType, timeInSec, ID};
    }
}

void saveToBinary(std::vector <Monster> &monsters, const std::string &path = "../databases/binarystorage.txt"){

    std::ofstream binary(path, std::ios::binary | std::ios::out);

    for (auto& i : monsters){

        binary.write(i.name, sizeof(i.name));
        binary.write(reinterpret_cast<char*> (&i.hp), sizeof(i.hp));
        binary.write(reinterpret_cast<char*> (&i.ap), sizeof(i.ap));
        binary.write(reinterpret_cast<char*> (&i.attackChance), sizeof(i.attackChance));
        binary.write(reinterpret_cast<char*> (&i.timeInSec) , sizeof(i.timeInSec));
        binary.write(reinterpret_cast<char*> (&i.ID) , sizeof(i.ID));
        binary.write(i.attackType , sizeof(i.attackType));
    }
}

void readFromBinary(std::vector <Monster> &monsters, const std::string &path = "../databases/binarystorage.txt") {

    std::ifstream binary(path, std::ios::binary | std::ios::out);

    if (!binary.is_open())
        throw std::runtime_error {"\"../databases/binarystorage.txt\" is needed for reading from binary file"};


    char name[20], attackType[20];
    int hp, ap, ID;
    double attackChance;
    time_t timeInSec;

    binary.seekg(0, binary.end);
    long int length = binary.tellg();
    binary.seekg(0, binary.beg);       //detecting file size


    while (binary.tellg() < length) {

        binary.read(name, sizeof(name));
        binary.read(reinterpret_cast<char *>(&hp), sizeof(hp));
        binary.read(reinterpret_cast<char *>(&ap), sizeof(ap));
        binary.read(reinterpret_cast<char *>(&attackChance), sizeof(attackChance));
        binary.read(reinterpret_cast<char *>(&timeInSec), sizeof(timeInSec));
        binary.read(reinterpret_cast<char *>(&ID), sizeof(ID));
        binary.read(attackType, sizeof(attackType));

           monsters.emplace_back(name, hp, ap, attackChance, attackType, timeInSec, ID);
    }
}

Monster findInBinary(int key, const std::string &path = "../databases/binarybenchmark.txt"){     //benchmark function

    std::ifstream binary(path, std::ios::binary | std::ios::out);
    if (!binary.is_open())
        throw std::runtime_error {"\"../databases/binarybenchmark.txt\" is needed for reading from binary file"};

    char name[20], attackType[20];
    int hp, ap, ID;
    double attackChance;
    time_t timeInSec;

    binary.seekg(0, binary.end);
    long int length = binary.tellg();
    binary.seekg(0, binary.beg);

    while (binary.tellg() < length) {

        binary.read(name, sizeof(name));
        binary.read(reinterpret_cast<char *>(&hp), sizeof(hp));
        binary.read(reinterpret_cast<char *>(&ap), sizeof(ap));
        binary.read(reinterpret_cast<char *>(&attackChance), sizeof(attackChance));
        binary.read(reinterpret_cast<char *>(&timeInSec), sizeof(timeInSec));
        binary.read(reinterpret_cast<char *>(&ID), sizeof(ID));
        binary.read(attackType, sizeof(attackType));


        if (attackType == Monster::attackTypes[key])
            return {name, hp, ap, attackChance, attackType, timeInSec, ID};
    }
}

void addMonster(std::vector <Monster> &monsters){

    std::string name, attackType;
    int hp, ap;
    double attackChance;

    cout << "Enter monster's name:   ";
    cin >> name;

    cout << "Set health (0 - 50000):   ";

    do
        cin >> hp;
    while (hp < 0 || hp > 50000);

    cout << "Set attack (0 - 1000):   ";

    do
        cin >> ap;
    while (ap < 0 || ap > 1000);

    cout << "Set chance of special attack (0 - 1):   ";

    do
        cin >> attackChance;
    while (attackChance < 0 || attackChance > 1);

    menuOut("- special attack selection", "- sort first");

    int choice;

    do
        cin >> choice;
    while (choice < 1 || choice > 4);

    monsters.emplace_back(name, hp, ap, attackChance, Monster::attackTypes[choice]);
}

void deleteMonster(std::vector <Monster> &monsters,  const std::string &name){

    for (auto &i : monsters)
        if (strcmp(i.name, name.c_str()) == 0){
            std::swap(i, monsters.back());
            monsters.pop_back();
        }
}


void modifyMonster(std::vector <Monster> &monsters, std::string &name){

    for (auto& i : monsters)
        if (strcmp(i.name, name.c_str()) == 0) {

            menuOut("- monster modify", "                            5. Type of special attack");

            int choice;

            do
                cin >> choice;
            while (choice < 1 || choice > 5);

            switch (choice){

                case 1: {

                    cout << "Choose new name for monster   ";
                    cin >> name;
                    strcpy(i.name, name.c_str());
                    break;
                }

                case 2: {

                    cout << "Set new health points for monster   ";
                    int hp;
                    cin >> hp;
                    i.hp = hp;
                    break;
                }

                case 3: {

                    cout << "Set new attack points for monster   ";
                    int ap;
                    cin >> ap;
                    i.ap = ap;
                    break;
                }

                case 4: {

                    cout << "Set new special attack chance for monster   ";
                    int attackChance;
                    cin >> attackChance;
                    i.attackChance = attackChance;
                    break;
                }

                case 5: {

                    menuOut("- special attack selection", "eof");

                    cout << "Choose new special attack for monster   ";
                    int attackType;
                    cin >> attackType;

                    strcpy(i.attackType, Monster::attackTypes[attackType]);
                    break;
                }
                default:
                    modifyMonster(monsters, name);
            }
            break;
        }
}

TextTable findMonster(std::vector <Monster> &monsters, const std::string &name){

    TextTable t( '-', '|', '+' );
    int count{};

    for (auto& i : monsters) {
        for (size_t a = 0; a < name.size(); ++a)
            if (name[name.size() - 1 - a] == i.name[strlen(i.name) - 1 - a])
                ++count;

        if (count == name.size())
            i.addTableInfo(t);

        count = 0;
    }

    return t;
}

TextTable findByAttackType(std::vector <Monster> &monsters, int specialAttack){

    TextTable t( '-', '|', '+' );

    for (auto& i : monsters)
        if (strcmp(i.attackType, Monster::attackTypes[specialAttack]) == 0)
            i.addTableInfo(t);

    return t;
}

TextTable findByAttack(std::vector <Monster> &monsters, double attackChance) {

    TextTable t('-', '|', '+');

    for (auto &i : monsters)
        if (i.attackChance >= attackChance)
            i.addTableInfo(t);

    return t;
}

TextTable findByTime(std::vector <Monster> &monsters, struct tm &lhs, struct tm &rhs){

    lhs.tm_year -= 1900;        //fixing structure bug
    rhs.tm_year -= 1900;

    time_t totalleft = mktime(&lhs);
    time_t totalright = mktime(&rhs);

    TextTable t('-', '|', '+');

    for (auto& i : monsters)
        if (i.timeInSec >= totalleft && i.timeInSec <= totalright)
            i.addTableInfo(t);

    return t;
}