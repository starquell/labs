#include <iostream>
#include "src/All.hpp"

int main() {

    IPv4 a {"122.222.121.111"};
    std::cout << a.address();

    IPv6 b {"1111:A22:3F3:4444::FF66:A777:88E8"};
    std::cout << '\n' << b.address();

    std::cout << "\n\n " << detail::to_hex(34454) << " " << detail::to_int("1A8");

    MAC c {"52:74:f2:b1:a8:7f"};
    std::cout << '\n' << c.address();
    std::cout << "\n\n" << algorithm::convertToIPv6(a).address();
    std::cout << "\n\n" << algorithm::convertToIPv6(c).address();

    return 0;
}
