#ifndef LAB1_CIDR_HPP
#define LAB1_CIDR_HPP

#include <type_traits>
#include <cmath>
#include <bitset>

#include "IPv6.hpp"
#include "IPV4.hpp"
#include "IpUtils.hpp"

template <class IP>
class CIDR {

    IP mIP;
    unsigned short mSubnetBits;

public:

    CIDR (const IP &ip, unsigned short subnetBits) {

        static_assert (std::is_same<IP, IPv6>::value
                   || std::is_same<IP, IPv4>::value, "CIDR bases on IPv4 or IPv6.");

        mIP = ip;
        mSubnetBits = subnetBits;
    }

    [[nodiscard]] std::string address() const {
        return mIP.address() + '/' + mSubnetBits;
    }

    auto& ip() const {
        return mIP;
    }

    bool isInSubnet (const IP &ip) const {              // little pretty method

        constexpr auto bitsNumber = IP::bitsNumber();
        constexpr auto octetsNum = bitsNumber == 128? 8 : 4;

        std::string ipOctets;
        std::string strSubnetMask (mSubnetBits, "1");
        strSubnetMask.reserve(bitsNumber - mSubnetBits);

        for (auto i = 0; i < bitsNumber - mSubnetBits; ++i)
            strSubnetMask += "0";
        for (auto &octet : mIP.octets())
            ipOctets += utils::inBinary(octet);

        std::bitset <bitsNumber> subnetMask (strSubnetMask),
                                        ipbinary (ipOctets);

        auto subnetAddress = subnetMask & ipbinary;


        if constexpr (bitsNumber == 128) {
            std::vector <uint16_t> hexs;
            for (auto i = 0; i < bitsNumber; i += 16)
                hexs.push_back(utils::to_hex(std::to_string(subnetMask[i]) + std::to_string(subnetMask[i + 1])
                             + std::to_string(subnetMask[i + 2]) + std::to_string(subnetMask[i + 3]
       /*      :)     */     + std::to_string(subnetMask[i + 4]) + std::to_string(subnetMask[i + 5])
                             + std::to_string(subnetMask[i + 6]) + std::to_string(subnetMask[i + 7])
                             + std::to_string(subnetMask[i + 8]) + std::to_string(subnetMask[i + 9])
                             + std::to_string(subnetMask[i + 10]) + std::to_string(subnetMask[i + 11])
                             + std::to_string(subnetMask[i + 12]) + std::to_string(subnetMask[i + 13])
                             + std::to_string(subnetMask[i + 14]) + std::to_string(subnetMask[i + 15]))));
            IPv6 subnet (hexs.begin());
            auto lastAddress = subnet + pow(2, bitsNumber - mSubnetBits) - 1;
            return ip < lastAddress and ip > subnet;
        }
        else {
            std::vector <uint8_t> octets;
            for (auto i = 0; i < bitsNumber; i += 8)
                octets.push_back(utils::fromBinary<uint8_t>
                        (std::to_string(subnetMask[i]) + std::to_string(subnetMask[i + 1])
                        + std::to_string(subnetMask[i + 2]) + std::to_string(subnetMask[i + 3])
                        + std::to_string(subnetMask[i + 4]) + std::to_string(subnetMask[i + 5])
                        + std::to_string(subnetMask[i + 6]) + std::to_string(subnetMask[i + 7])));
            IPv6 subnet (octets.begin());
            auto lastAddress = subnet + pow(2, bitsNumber - mSubnetBits) - 1;
            return ip < lastAddress and ip > subnet;
        }
    }
};

#endif //LAB1_CIDR_HPP
