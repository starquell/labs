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

        static_assert(std::is_same<IP, IPv6>::value
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

    IP subnetAddress () const {

        constexpr auto bitsNumber = IP::bitsNumber();

        std::string ipOctets;
        std::string strSubnetMask (mSubnetBits, "1");
        strSubnetMask.reserve(bitsNumber - mSubnetBits);

        for (auto i = 0; i < bitsNumber - mSubnetBits; ++i)
            strSubnetMask += "0";
        for (auto &octet : mIP.octets())
            ipOctets += utils::inBinary(octet);

        std::bitset <bitsNumber> subnetMask (strSubnetMask),
                ipbinary (ipOctets);
    }

    bool isInSubnet (const IP &ip) const {


        constexpr auto octetLength = (bitsNumber == 32) ? 8 : 16;

        IP temp (mIP + pow(2, bitsNumber - mSubnetBits) - 1);

        std::string strSubnetMask (mSubnetBits, "1");
        strSubnetMask.reserve(bitsNumber - mSubnetBits);

        for (auto i = 0; i < bitsNumber - mSubnetBits; ++i)
            strSubnetMask += "0";


        std::bitset <bitsNumber> subnetMask (strSubnetMask),
                                 ipbinary (ipOctets);
        return subnetMask & ipbinary;
    }
};
#endif //LAB1_CIDR_HPP
