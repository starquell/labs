#include "Interactive.hpp"

#include <iostream>

int main (int argc, char** argv) {


    auto helpers =  Helper {"Name", "Age"}
                   |  Helper {"Enter your str", "gw"}
                   |  Helper {""};


    auto func = [] (std::string x, int y) { std::cout << x << ' '; };


    helpers.bind (func, [] (std::string x, std::string y) { std::cout << "Your street : " << x; },

                 [] {std::cout << "YEY";});


   helpers.launchAll();

}