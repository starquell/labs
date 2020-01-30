#define CATCH_CONFIG_MAIN
#include "src/All.hpp"
#include "src/catch/single_include/catch2/catch.hpp"


TEST_CASE("IPv4", "[ipv4]"){

   // std::cout << randomObject<std::string, 14>() << "\n\n\n\n\n";

    SECTION("IPv4 initialization and view methods") {

        REQUIRE(IPv4::fromString("122.222.121.111").octets() == std::array<uint8_t, 4>{122, 222, 121, 111});
        REQUIRE(IPv4(233, 111, 5, 1).address() == "233.111.5.1");

        std::vector octets {145, 145, 145, 145};
        REQUIRE(IPv4(octets.begin()) == IPv4(145, 145, 145, 145));
    }

    SECTION("Operators") {

        REQUIRE(IPv4::fromString("192.168.0.1") + 5 == IPv4::fromString("192.168.0.6"));
        REQUIRE(IPv4::fromString("192.168.0.254") + 2 == IPv4::fromString("192.168.1.0"));
        REQUIRE(IPv4(255, 11, 45, 1) == IPv4::fromString("255.11.45.1"));
//        REQUIRE(IPv4::fromString("145.145.145.145") > IPv4::fromString("145.145.200.145"));
    }
}

TEST_CASE("IPv6", "[ipv6]"){

    SECTION("IPv4 initialization and view methods") {

        REQUIRE(IPv6::fromString("FF:A3:E9:FF:F3:A4:A4:EE").octets()
               == std::array<uint16_t, 8>{0xFF, 0xA3, 0xE9, 0xFF, 0xF3, 0xA4, 0xA4, 0xEE});
        REQUIRE(IPv6(0xFF, 0xA3, 0xE9, 0xFF, 0xF3, 0xA4, 0xA4, 0xEE).address() == "FF:A3:E9:FF:F3:A4:A4:EE");
    }

    SECTION("Operators") {

        REQUIRE(IPv6::fromString("192:168:0:F:EE:4B:AA:122") <
                IPv6::fromString("192:168:0:F:EE:4B:AA:FFFF"));
        REQUIRE(IPv6(0x0255, 0x0011, 0x0045, 0x0001, 0x0002, 0x0005, 0xAAAF, 0x0200)
                == IPv6::fromString("255:11:45:1:2:5:AAAF:200"));
    }

    SECTION("Convertions from IPv4 and MAC address") {

        REQUIRE(IPv6::fromMAC(MAC::fromString("52:74:f2:b1:a8:7f")).octets()
                == IPv6::fromString("fe80:0:0:0:1874:f2ff:feb1:a87f").octets());
        REQUIRE(IPv6::fromIPv4(IPv4::fromString("192.168.0.1")).octets()
                == IPv6::fromString("0:0:0:0:0:0:C0A8:0001").octets());
    }
}


//TEST_CASE("CIDR", "[cidr]"){
//
//    IPv4 ip (192, 168, 0, 1);
//   // REQUIRE(CIDR (ip, 12).address() == "192.168.0.1/12");
//    REQUIRE(CIDR (ip, 12).isInSubnet(IPv4 (192, 168, 6, 29)));
//}

TEST_CASE("Queue", "[queue]") {

    SECTION("List implementation") {

        Queue::Listbased<std::string> qlist;
        qlist.push("first");
        qlist.push("second");
        qlist.push("third");
        qlist.pop();

        REQUIRE(qlist.front() == "second");
        REQUIRE(qlist.size() == 2);
        REQUIRE(!qlist.empty());
    }

    SECTION("Array implementation") {

        Queue::Arraybased<double , 100> qarray;
        qarray.push(34.3);
        qarray.push(2.3);
        qarray.push(145.145);
        qarray.pop();

        REQUIRE(qarray.front() == 2.3);
        REQUIRE(qarray.size() == 2);
        REQUIRE(!qarray.empty());
    }

    SECTION("STL implementation") {

        Queue::STLImpl<int> qstl;
        qstl.push(4);
        qstl.push(122);
        qstl.push(145);

        qstl.pop();
        qstl.pop();

        REQUIRE(qstl.front() == 145);
        REQUIRE(qstl.size() == 1);
    }
}

TEST_CASE("Stack", "[stack]") {

    SECTION("List implementation") {

        Stack::Listbased<std::string> stack;
        stack.push("first");
        stack.push("second");
        stack.push("third");
        stack.pop();

        REQUIRE(stack.top() == "second");
        REQUIRE(stack.size() == 2);
        REQUIRE(!stack.empty());
    }

    SECTION("Array implementation") {

        Stack::Arraybased<double , 10> stack;
        stack.push(34.3);
        stack.push(2.3);
        stack.push(145.145);

        stack.pop();
        stack.pop();

        REQUIRE(stack.top() == 34.3);
        REQUIRE(stack.size() == 1);
        REQUIRE(!stack.empty());
    }

    SECTION("STL implementation") {

        Stack::STLImpl<int> stack;
        stack.push(4);
        stack.push(122);
        stack.push(145);

        stack.pop();
        stack.pop();

        REQUIRE(stack.top() == 4);
        REQUIRE(stack.size() == 1);
    }
}

TEST_CASE("Deque", "[deque]") {

    SECTION("Listbased") {

        Deque::Listbased <std::string> deque;
        deque.push("first");
        deque.push("second");
        deque.push("third");
        deque.push("fourth");
        deque.push("fifth");
        deque.popBack();
        deque.popFront();

        REQUIRE(deque.top() == "fourth");
        REQUIRE(deque.size() == 3);
        REQUIRE(*deque.begin() == "second");
        REQUIRE(deque.begin() + deque.size() == deque.end());
        REQUIRE(deque[2] == "fourth");
        REQUIRE(!deque.empty());
    }

    SECTION("Arraybased") {


        Deque::Arraybased <double, 50> deque;
        deque.push(145);
        deque.push(14.5);
        deque.push(1.45);
        deque.push(1450.0);
        deque.push(0.145);
        deque.popBack();
        deque.popFront();

        REQUIRE(deque.top() == 1450);
        REQUIRE(deque.size() == 3);
        REQUIRE(*deque.begin() == 14.5);
        REQUIRE(deque.begin() + deque.size() == deque.end());
        REQUIRE(deque[1] == 1.45);
        REQUIRE(!deque.empty());
    }

    SECTION("STL implementation") {

        Deque::STLImpl <double> deque;
        deque.push(145);
        deque.push(14.5);
        deque.push(1.45);
        deque.push(1450.0);
        deque.push(0.145);
        deque.popBack();
        deque.popFront();

        REQUIRE(deque.top() == 1450);
        REQUIRE(deque.size() == 3);
        REQUIRE(*deque.begin() == 14.5);
        REQUIRE(deque.begin() + deque.size() == deque.end());
        REQUIRE(deque[0] == 14.5);
        REQUIRE(!deque.empty());
    }
}







//
//int main() {

//    auto mStorage = IPv4::fromString("122.222.121.111");
//    std::cout << mStorage.address();
//
//    auto b = IPv6::fromString("1111:A22:3F3:4444::FF66:A777:88E8");
//    std::cout << '\n' << b.address();
//
//    std::cout << "\n\n " << utils::to_hex(34454) << " " << utils::to_int("1A8");
//
//    auto c = MAC::fromString("52:74:f2:b1:a8:7f");
//    std::cout << '\n' << c.address();
//    std::cout << "\n\n" << IPv6::fromIPv4(mStorage).address();
//    std::cout << "\n\n" << IPv6::fromMAC(c).address();

//}
