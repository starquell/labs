#ifndef LAB1_IPV6_HPP
#define LAB1_IPV6_HPP

#include <array>
#include <string_view>
#include <algorithm>
#include <regex>
#include <cstdint>


#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string.hpp>

#include "IpUtils.hpp"
#include "MACaddress.hpp"
#include "IPV4.hpp"


class IPv6 {

    std::array <uint16_t , 8> hexs;

public:

    template <class It>
    explicit IPv6 (It begin)
        : hexs ({(uint16_t)*begin, (uint16_t)*(begin + 1),
                 (uint16_t)*(begin + 2), (uint16_t)*(begin + 3),
                 (uint16_t)*(begin + 4), (uint16_t)*(begin + 5),
                 (uint16_t)*(begin + 6), (uint16_t)*(begin + 7)})
    {}

    explicit IPv6 (uint16_t hex0, uint16_t hex1, uint16_t hex2, uint16_t hex3,
                   uint16_t hex4, uint16_t hex5, uint16_t hex6, uint16_t hex7)
                   : hexs ({hex0, hex1, hex2, hex3,
                           hex4, hex5, hex6, hex7})
    {}

    [[nodiscard]] std::string address() const {
        return utils::join(hexs, ":",
                           [](uint16_t el) { return utils::to_hex(el);});
    }

    [[nodiscard]] auto octets() const {
        return hexs;
    }

public:

    static IPv6 fromString (std::string ip) {

        static const std::regex ipPattern ("([0-9a-fA-F]{0,4}:){7}[0-9a-fA-F]{0,4}");
        if (!std::regex_match(ip, ipPattern))
            throw std::logic_error("Incorrect IPv6 address");

        std::vector <std::string> splited;
        boost::split(splited, ip, boost::is_any_of(":"));

        for (auto &hex : splited)
            if (hex.empty())
                hex = "0";

        return IPv6 (utils::to_int <uint16_t> (splited[0]), utils::to_int <uint16_t> (splited[1]),
                utils::to_int <uint16_t> (splited[2]), utils::to_int <uint16_t> (splited[3]),
                utils::to_int <uint16_t> (splited[4]), utils::to_int <uint16_t> (splited[5]),
                utils::to_int <uint16_t> (splited[6]), utils::to_int <uint16_t> (splited[7]));
    }

    static IPv6 fromMAC (const MAC &mac){

        auto address = mac.address();
        address.insert(9, "ff:fe:");
        std::vector <std::string> octets;
        boost::split(octets, address, boost::is_any_of(":"));

        std::bitset<8> firstoctet (utils::to_int <uint16_t> (octets.front()));
        firstoctet.flip(6);
        octets[0] = std::to_string((unsigned short)firstoctet.to_ulong());

        for (auto octet = octets.begin(); octet != octets.end(); octet += 2)
            *octet += *(octet + 1);

        for (auto it = octets.begin(); it != octets.end();){
            if ((*it).size() == 2)
                it = octets.erase(it);
            else
                ++it;
        }
        return IPv6::fromString ("FE80:0:0:0:" + utils::join(octets, ":",
                [] (const std::string &elem) { return elem;}));
    }

    static IPv6 fromIPv4 (const IPv4& ipv4) {

        auto address = ipv4.address();
        std::vector <std::string> octets;
        boost::split(octets, address, boost::is_any_of("."));
        std::string ipv6;

        for (auto octet = octets.begin(); octet != octets.end(); octet += 2){
            ipv6 += utils::to_hex(std::stoi(*octet)) + utils::to_hex(std::stoi(*(octet + 1))) + ":";
        }
        ipv6.pop_back();

        return IPv6::fromString ("0:0:0:0:0:0:" + ipv6);
    }

    constexpr static auto bitsNumber() {
        return 128;
    }

    IPv6 operator+ (int i) {
        auto copied = hexs;
        for (auto it = copied.end() - 1; it >= copied.begin(); --it)
            if ((unsigned) *it < UINT16_MAX) {
                if (i == 0)
                    break;
                ++(*it);
                break;
            }
            else {
                if (i == 0)
                    break;
                i -= UINT16_MAX - *it;
                *it = 0;
            }
        return IPv6(copied.begin());
    }
    bool operator< (const IPv6 &other) const{
        return std::lexicographical_compare(hexs.begin(), hexs.end(),
                                            other.hexs.begin(), other.hexs.end());
    }

    bool operator== (const IPv6 &other) const{
        return std::equal(hexs.begin(), hexs.end(), other.hexs.begin());
    }

    bool operator> (const IPv6 &other) const {
        return !(*this < other or *this == other);
    }
};
#endif //LAB1_IPV6_HPP
