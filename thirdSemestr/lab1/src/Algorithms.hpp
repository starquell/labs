#ifndef LAB1_ALGORITHMS_HPP
#define LAB1_ALGORITHMS_HPP

#include <bitset>
#include <algorithm>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "IpDetail.hpp"
#include "IPV4.hpp"
#include "IPv6.hpp"
#include "MACaddress.hpp"

namespace algorithm {

    IPv6 convertToIPv6 (const IPv4& ipv4) {

        auto address = ipv4.address();
        std::vector <std::string> octets;
        boost::split(octets, address, boost::is_any_of("."));
        std::string ipv6;

        for (auto octet = octets.begin(); octet != octets.end(); octet += 2){
            ipv6 += detail::to_hex(std::stoi(*octet)) + detail::to_hex(std::stoi(*(octet + 1))) + ":";
        }
        ipv6.pop_back();

        return IPv6 ("0:0:0:0:0:0:" + ipv6);
    }

    IPv6 convertToIPv6 (const MAC &mac){

        auto address = mac.address();
        address.insert(9, "ff:fe:");
        std::vector <std::string> octets;
        boost::split(octets, address, boost::is_any_of(":"));

        std::bitset<8> firstoctet (detail::to_int(octets.front()));
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
        return IPv6 ("FE80:0:0:0:" + detail::join(octets, ":", [] (const std::string &elem) { return elem;}));
    }
}
#endif //LAB1_ALGORITHMS_HPP
