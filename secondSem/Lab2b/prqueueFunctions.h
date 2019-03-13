#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <chrono>
#include <thread>
#include "priorityqueue.h"

using namespace std::chrono_literals;
using std::this_thread::sleep_for;

void queue (Queue <std::string> &l, bool showmode){

    if (showmode)
        sleep_for(1s);

    std::cout << "\n\n 1. Add data\n"
              << " 2. Delete data with highest priority\n"
              << " 3. Show top in queue\n"
              << " 4. Check queue length\n"
              << " 5. Exit   "
              << "____________________________________________\n";

    int choice;
    do
        std::cin >> choice;
    while (choice < 1 || choice > 5);

    if (showmode) {
        std::cout << choice << '\n';
        sleep_for(1s);
    }

    switch (choice){
        case 1: {

            std::string data;
            int priority;

            std::cout << "Enter data: ";
            std::cin >> data;
            if (showmode) {
                std::cout << data;
                sleep_for(1s);
            }

            std::cout << ".  Set priority: ";
            std::cin >> priority;
            if (showmode) {
                std::cout << priority;
                sleep_for(1s);
            }

            l.push(data, priority);
            break;
        }
        case 2: l.popByHighest();
            break;
        case 3: std::cout << "Top is '" << l.getFront() << "'\n";
            break;
        case 4: std:: cout << "There are " << l.length() << " elements in queue\n";
            break;
        case 5: exit(0);
    }
}