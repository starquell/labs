#include "Interactive.hpp"

#include <iostream>
#include <mutex>

class Example {

	int data;
	std::mutex m;

public:

	Example (int _data) : data (_data) {}

	void operator()(int h) {}
};

int main (int argc, char** argv) {

    Helper h{"Input"};

    HelperContainer container (h);
    Example ex{5};
    h.bind(ex);
    container.bind(ex);
    container.launchAll();
}