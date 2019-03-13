#include "prqueueFunctions.h"
#include "schedulerFunc.h"


int main(int argc, char** argv) {

    bool showmode = false;

    if (argc > 1 && strcmp(argv[1], "--priority_queue") == 0) {

        std::ifstream file("../queueShow.txt");

        if (argc > 2 && strcmp(argv[2], "--presentation") == 0) {

            std::cin.rdbuf(file.rdbuf());
            showmode = true;
        }

        Queue<std::string> l;
        while (true)
        queue(l, showmode);
    }

    if (argc > 1 && strcmp(argv[1], "--scheduler") == 0){

        std::ifstream file("../scheduleShow.txt");

        if (argc > 2 && strcmp(argv[2], "--presentation") == 0) {

            std::cin.rdbuf(file.rdbuf());
            showmode = true;
        }

        JobScheduler s;
        while (true)
        schedule(s, showmode);
    }
}


