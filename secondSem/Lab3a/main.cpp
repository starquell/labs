#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include "sortAlgorithms.h"

using std::cout;

void benchmark(),
     show();

int main (int argc, char **argv) {

    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0) {

//        benchmark();
        return 0;
    }

    try {
     //   std::ifstream showfile("../showtext.txt");

     //   if (!showfile.is_open())
       //     throw std::logic_error ("Show file isn't in source directory");


        show();
    }

    catch (std::exception &ex) {
        std::cout << ex.what() << '\n';
    }

    return 0;
}

void show() {



}