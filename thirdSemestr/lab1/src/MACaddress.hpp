#ifndef LAB1_MACADDRESS_HPP
#define LAB1_MACADDRESS_HPP

#include <array>
#include <regex>

#include "IpDetail.hpp"

class MAC {

    std::array <unsigned short, 6> hexs;

public:

    explicit MAC (const std::string &macAddress){

        static const std::regex macPattern("([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}");
        if (!std::regex_match(macAddress, macPattern))
            throw std::logic_error ("Incorrect MAC address");

        std::vector <std::string> splited;
        boost::algorithm::split(splited, macAddress, boost::algorithm::is_any_of(":"));

        hexs = {detail::to_int(splited[0]), detail::to_int(splited[1]),
                detail::to_int(splited[2]), detail::to_int(splited[3]),
                detail::to_int(splited[4]), detail::to_int(splited[5])};
    }

    std::string address() const {
        return detail::join(hexs, ":",
                            [](unsigned short el) { return detail::to_hex(el);});
    }
};
#endif //LAB1_MACADDRESS_HPP
