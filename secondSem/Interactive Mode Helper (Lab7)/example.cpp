#include "Interactive.hpp"

#include <iostream>

class Example {

	int data;

public:

	Example (int _data) : data (_data) {}
};

int main (int argc, char** argv) {


    auto helpers =  Helper {"Name", "Age"}
                   |  Helper {"Enter your str", "gw"}
                   |  Helper {""};


    auto func = [] (std::string x, int y) { std::cout << x << ' '; };


    helpers.bind (func, [] (std::string x, std::string y) { std::cout << "Your street : " << x; },

                 [] {std::cout << "std::cout";});



   helpers.launchAll();

}