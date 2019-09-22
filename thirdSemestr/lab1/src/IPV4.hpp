#ifndef LAB1_IPV4_HPP
#define LAB1_IPV4_HPP

#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <regex>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "IpDetail.hpp"


class IPv4 {

    std::array <unsigned long, 4> mOctets;

    template <class Stream>
    friend Stream& operator<< (Stream &stream, const IPv4 &iPv4);

public:

    explicit IPv4 (unsigned long first, unsigned long second,
                   unsigned long third, unsigned long fourth)
    {
        if (first > 255 || second > 255 || third > 255 || fourth > 255)
            throw std::logic_error("Incorrect IPv4 address");

        mOctets = {first, second, third, fourth};
    }

    explicit IPv4 (const std::string &ip) {

        static const std::regex ipPattern ("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}");
        if (!std::regex_match(ip, ipPattern))
            throw std::logic_error("Incorrect IPv4 address");

        std::vector <std::string> splited;
        boost::split (splited, ip, boost::is_any_of("."));

        mOctets = {stoul(splited[0]),
                   stoul(splited[1]),
                   stoul(splited[2]),
                   stoul(splited[3])};
    }

     std::string address() const {

        return detail::join(mOctets, ".",
                [](unsigned long el){ return std::to_string(el);});
    }
};

template <class Stream>
Stream& operator<< (Stream &stream, const IPv4 &iPv4){

    stream << iPv4.address();

    return stream;
}

#endif //LAB1_IPV4_HPP
