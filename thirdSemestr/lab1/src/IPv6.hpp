#ifndef LAB1_IPV6_HPP
#define LAB1_IPV6_HPP

#include <array>
#include <string_view>
#include <algorithm>
#include <regex>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string.hpp>

#include "IpDetail.hpp"


class IPv6 {

    std::array <unsigned short int, 8> hexs;

public:

    explicit IPv6 (std::string ip) {

        static const std::regex ipPattern ("([0-9a-fA-F]{0,4}:){7}[0-9a-fA-F]{0,4}");
        if (!std::regex_match(ip, ipPattern))
            throw std::logic_error("Incorrect IPv6 address");

        std::vector <std::string> splited;
        boost::split(splited, ip, boost::is_any_of(":"));

        for (auto &hex : splited)
            if (hex.empty())
                hex = "0";

        hexs = {detail::to_int(splited[0]), detail::to_int(splited[1]),
                detail::to_int(splited[2]), detail::to_int(splited[3]),
                detail::to_int(splited[4]), detail::to_int(splited[5]),
                detail::to_int(splited[6]), detail::to_int(splited[7])};
    }

     std::string address() const {
        return detail::join(hexs, ":",
                [](unsigned short el) { return detail::to_hex(el);});
    }
};
#endif //LAB1_IPV6_HPP
