#include <iostream>
#include "src/All.hpp"

int main() {

//    auto a = IPv4::fromString("122.222.121.111");
//    std::cout << a.address();
//
//    auto b = IPv6::fromString("1111:A22:3F3:4444::FF66:A777:88E8");
//    std::cout << '\n' << b.address();
//
//    std::cout << "\n\n " << utils::to_hex(34454) << " " << utils::to_int("1A8");
//
//    auto c = MAC::fromString("52:74:f2:b1:a8:7f");
//    std::cout << '\n' << c.address();
//    std::cout << "\n\n" << IPv6::fromIPv4(a).address();
//    std::cout << "\n\n" << IPv6::fromMAC(c).address();

    Stack::Listbased <std::string> a;
    Stack::Arraybased <std::string, 100> b;
    Stack::STLImpl <std::string> f;
    Queue::Listbased <std::string> c;
    Queue::Arraybased <std::string, 100> d;
    Queue::STLImpl <std::string> e;



    return 0;
}
