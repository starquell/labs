#ifndef LAB1_IPV4_HPP
#define LAB1_IPV4_HPP

#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <regex>
#include <cstdint>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "IpUtils.hpp"


class IPv4 {

    std::array <uint8_t , 4> mOctets;

public:

    template <class Stream>
    friend Stream& operator<< (Stream &stream, const IPv4 &iPv4);

    explicit IPv4 (uint8_t first, uint8_t second,
                   uint8_t third, uint8_t fourth)
                   :  mOctets ({first, second, third, fourth})
    {}

    [[nodiscard]] std::string address() const {
        return utils::join(mOctets, ".",
                           [](uint8_t el){ return std::to_string(int(el));});
    }

    [[nodiscard]] auto& octets() const {
        return mOctets;
    }

    constexpr static auto bitsNumber() {
        return 32;
    }

    static IPv4 fromString(const std::string &ip) {

        static const std::regex ipPattern ("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}");
        if (!std::regex_match(ip, ipPattern))
            throw std::logic_error("Incorrect IPv4 address");

        std::vector <std::string> splitted;
        boost::split (splitted, ip, boost::is_any_of("."));

        return IPv4((uint8_t) stoi(splitted[0]),
                  (uint8_t) stoi(splitted[1]),
                    (uint8_t) stoi(splitted[2]),
                   (uint8_t) stoi(splitted[3]));
    }
};

template <class Stream>
Stream& operator<< (Stream &stream, const IPv4 &iPv4){

    stream << iPv4.address();
    return stream;
}

#endif
