#include "monster.h"
#include <chrono>
#include <vector>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;
using std::this_thread::sleep_for;


void presentation();
//void benchmark();
void defaultCase();

void addMonster(std::vector <Monster> &monsters),
     modifyMonster(std::vector <Monster> &monsters, std::string name),
     deleteMonster(std::vector <Monster> &monsters, std::string name),
     findMonster(std::vector <Monster> &monsters, std::string name),
     findByAttack(std::vector <Monster> &monsters, std::string specialAttack),
     findByAttack(std::vector <Monster> &monsters, double attackChance);

void Selector(std::vector <Monster> &monsters);


int main(int argc, char** argv) {

    if (argc > 1) {
        std::string parameter(argv[1]);

      //  if (parameter == "--benchmark")
      //      benchmark();
        if (parameter == "--presentation")
            presentation();
    }

    defaultCase();

    return 0;
}

void defaultCase(){

    std::vector <Monster> monsters;
    TextTable t( '-', '|', '+' );

  //  addMonster(monsters);
   // monsters[0].addTableInfo(t);

    Selector(monsters);
}

void presentation(){

    srand(time(nullptr));

    cout << "Creating random monsters...\n";
    sleep_for(1s);
    cout << "Creating table...\n";
    sleep_for(1s);

    std::vector<Monster> monsters{5};
    TextTable t( '-', '|', '+' );

    cout << "Adding monsters to table...\n\n";
    sleep_for(1s);

    for (auto& i : monsters)
        i.addTableInfo(t);

        cout << t;

        exit(0);
}

void Selector (std::vector <Monster> &monsters) {

    std::string s, name, specialAttack;
    int choice;
    double attackChance;

    std::ifstream selector;
    selector.open("selector.txt");

    if (selector.is_open())
      while (!selector.eof()){

        getline (selector, s);
        cout << s << '\n';
      }

    cout << '\n';
    cin >> choice;

    switch (choice){

        case 1: addMonster(monsters);
                break;
       // case 2:
        case 3: {
            cout << "Enter name of monster to modify   ";
            cin >> name;

         //   modifyMonster(monsters, name);
            break;
        }

        case 4: {
            cout << "Enter name of monster to delete   ";
            cin >> name;

         //   deleteMonster(monsters, name);
            break;
        }

        case 5: {
            cout << "Enter end of monster's name to find   ";
            cin >> name;

          //  findMonster(monsters, name);
        }

        case 6: {
            cout << "Enter monster's special attack to find   ";
            cin >> specialAttack;

          //  findByAttack(monsters, specialAttack);
        }

        case 7: {
            cout << "Enter chance of special attack to find monsters with higher chance   ";
            cin >> attackChance;

          //  findByAttack(monsters, attackChance);

            default:
                Selector(monsters);
        }
    }

}