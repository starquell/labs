#include "orderedVector.hpp"

#include <iostream>

int main() {

    OrderedVector <int> vec;

    vec.push (43);
    vec.push (23);
    vec.push (2);
    vec.push (34);

    std::cout << std::boolalpha << vec.empty();

    for (auto &i : vec)
        std::cout << i << ' ';


}