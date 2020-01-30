#include "jobScheduler.h"
#include <map>
#include <functional>


void schedule(JobScheduler &j, bool showmode) {

     static std::map <int, std::function<void()>> userFunc = {

            {1, [&j, showmode] {
                std::string task;
                int time;
                std::cout << "\n  Enter task: ";
                std::cin >> task;

                if (showmode){
                      std::cout << task;
                      sleep_for(1s);
                }
                std::cout << "  Set task time: ";
                std::cin >> time;

                if (showmode) {
                    std::cout << time;
                    sleep_for(1s);
                }
                j.push(task, time);
            } },

            {2, [&j] {
                j.pop();
                std::cout << "\n___Terminated!__\n";
            } },

            {3, [&j] {
                std::cout << "\n_______________________\n"
                          << "Active task is " << j.getFront()->task << ".\n";
            }},

            {4, []{
                exit(0);
            }}
    };

    if (showmode)
        sleep_for(1s);

    std::cout << "\n\n 1. Add task to queue\n"
              << " 2. Terminate active task\n"
              << " 3. Show active task\n"
              << " 4. Exit   ";

    int choice;

    do
    std::cin >> choice;
    while (choice < 1 || choice > 4);

    if (showmode){
        std::cout << choice;
        sleep_for(1s);
    }

    userFunc[choice]();
}

