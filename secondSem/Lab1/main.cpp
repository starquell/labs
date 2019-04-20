#include "monster.h"
#include "databaseFunctions.h"
#include "benchmarkFunctions.h"

using namespace std::chrono;

void presentation(),
     benchmark(),
     interactive();

void Selector(std::vector <Monster> &monsters);


int main(int argc, char** argv) {

    if (argc > 1) {
        std::string parameter(argv[1]);

        if (parameter == "--benchmark") {

            if (argc > 2 && strcmp (argv[2], "--sort") == 0)
                benchSort();
            else
            benchmark();
        }

        if (parameter == "--presentation")
            presentation();
    }

    interactive();

    return 0;
}

void interactive(){

    std::vector <Monster> monsters;

   while (true) {
       Selector(monsters);
       sleep_for(1s);
   }
}

void benchmark(){

    size_t elements;

    TextTable vectorresults( '-', '|', '+', 'b');

    cout << "\nBenchmarking via vector...  \n";

    for (elements = 2; ; elements *= 5)
        if (vectorTest(vectorresults, elements) >= 10)
            break;


    for (; ; elements *= 2)
        if (vectorTest(vectorresults, elements) >= 100)
            break;

    cout << vectorresults

         << "\n\nBenchmarking via text file...  \n";

    TextTable textresults( '-', '|', '+', 'b');

    for (elements = 2; ; elements *= 5)
        if (TextTest(textresults, elements) >= 10)
            break;


    for (; ; elements *= 2)
        if (TextTest(textresults, elements) >= 100)
            break;

    cout << textresults

         << "\n\nBenchmarking via binary file...  \n";

    TextTable binaryresults( '-', '|', '+', 'b');

    for (elements = 2; ; elements *= 5)
        if (BinaryTest(binaryresults, elements) >= 10)
            break;


    for (; ; elements *= 2)
        if (BinaryTest(binaryresults, elements) >= 100)
            break;

    cout << binaryresults;
    exit(0);
}

void presentation(){

    cout << "Creating random monsters...\n";
    sleep_for(1s);

    std::vector<Monster> monsters{10};

    cout << "Adding monsters to table...\n\n";
    sleep_for(1s);

    monstersOut(monsters);

    std::remove("database.txt");
    cout << "Saving monsters to file...\n";
    sleep_for(1s);
    saveToFile(monsters);
    cout << "Monsters saved to database.txt!\n";

    cout << "Deleting monster with name " << monsters[2].name << "...\n\n\n";
    sleep_for(1s);
    deleteMonster(monsters, monsters[2].name);

    monstersOut(monsters);

    std::string n = monsters.back().name;
    n.erase(0, 3);

    cout << "Let's find monster with last letters of name: " << n << " ...\n\n\n";
    sleep_for(1s);
    cout << findMonster(monsters, n);
    sleep_for(0.5s);

    cout << "Finding monster with special attack :" << Monster::attackTypes[1] << "...\n\n\n";
    sleep_for(0.5s);
    cout << findByAttack(monsters, 1);
    sleep_for(0.75s);

    cout << "Removing all monsters from memory...\n\n";
    sleep_for(1s);

    monsters.clear();
    monstersOut(monsters);

    cout << "Restoring data from file...\n\n";
    sleep_for(1s);
    readFromFile(monsters);
    sleep_for(1s);
    monstersOut(monsters);

    cout << "nice job dude\n";

        exit(0);
}

void Selector (std::vector <Monster> &monsters) {

    tm lhs, rhs;
    std::string name;
    int choice, specialAttack;
    double attackChance;

    menuOut("bof", "    17. Show database");

    cout << '\n';
    cin >> choice;

    switch (choice){

        case 1: {
            addMonster(monsters);
            cout << "\nDone!\n" << "__________________________________________________\n";
            break;
        }

        case 2: {
            saveToFile(monsters);
            cout << "\nDone!\n" << "__________________________________________________\n";
            break;
        }

        case 3:  {
            std::remove("database.txt");
            cout << "\nDone!\n______________________________________\n";
            break;
        }

        case 4: {
            readFromFile(monsters);
            cout << "\nDone!\n" << "__________________________________________________\n";
            break;
        }

        case 5:  {
            saveToBinary(monsters);
            cout << "\nDone!\n" << "__________________________________________________\n";
            break;
        }

        case 6: {
            readFromBinary(monsters);
            cout << "\nDone!\n" << "__________________________________________________\n";
            break;
        }

        case 7:  {
            std::remove("binarystorage.txt");
            cout << "\nDone!\n______________________________________\n";
            break;
        }

        case 8: {
            cout << "Enter name of monster to modify   ";
            cin >> name;

               modifyMonster(monsters, name);
            break;
        }

        case 9: {
            cout << "Enter name of monster to delete   ";
            cin >> name;

              deleteMonster(monsters, name);
            break;
        }

        case 10: {
            cout << "Enter end of monster's name to find   ";
            cin >> name;

            cout << findMonster(monsters, name);
            break;
        }

        case 11: {

            menuOut("- special attack selection", "-                                     4. Paralyse enemy");

            cin >> specialAttack;

            cout << findByAttackType(monsters, specialAttack);
            break;
        }

        case 12: {
            cout << "Enter chance of special attack to find monsters with higher chance   ";
            cin >> attackChance;

            cout << findByAttack(monsters, attackChance);
            break;
        }

        case 13: {
            cout << "Enter time in this style :  hours minutes seconds day month year\n"
                 << "                 Example : 17 43 32  04 08 2001\n\n"
                 << "      From ";
            cin >> lhs.tm_hour >> lhs.tm_min >> lhs.tm_sec >> lhs.tm_mday >> lhs.tm_mon >> lhs.tm_year;
            cout << " to ";
            cin >> rhs.tm_hour >> rhs.tm_min >> rhs.tm_sec >> rhs.tm_mday >> rhs.tm_mon >> rhs.tm_year;

            cout << findByTime(monsters, lhs, rhs);
            break;
        }

        case 14:    countingSort(monsters);
                    break;

        case 15:    radixSort (monsters);
                    break;

        case 16:    customSort (monsters);
        case 17:    monstersOut(monsters);
                    break;

          default:
              return;
        }
}