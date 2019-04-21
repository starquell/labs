#include "Filesystem.h"
#include <thread>
#include <iostream>


int main() {


    Filesystem f("shit");

    f.root()->createDir("here");

    std::cout << f.root()->children.front()->name;

    f.root()->children.front()->createDir("we");

    f.findDirectory("/here/we")->name = "lelius";

    std::cout << ' ' << f.findDirectory("/here/lelius")->name;

    f.createFile("/here/lelius", "gk", 43);

  //  std::cout << f.findDirectory("/here/lelius/gk")->name;
  //
 //   std::cout << f.findDirectory("/here/lelius")->files.front()->name();

    f.findFile ("/here/lelius/gk")->rename("renamed");

    std::cout << f.findFile ("/here/lelius/renamed")->name();


    std::cout << "\n\n\n";

  //  f.root()->showAll();


    return 0;
}