#ifndef LAB1_MACADDRESS_HPP
#define LAB1_MACADDRESS_HPP

#include <array>
#include <regex>
#include <cstdint>

#include "IpUtils.hpp"

class MAC {

    std::array <uint16_t , 6> hexs;

public:

    explicit MAC (uint16_t hex0, uint16_t hex1, uint16_t hex2,
                  uint16_t hex3, uint16_t hex4, uint16_t hex5)
                  : hexs ({hex0, hex1, hex2, hex3,
                          hex4, hex5})
    {}

    [[nodiscard]] std::string address() const {
        return utils::join(hexs, ":",
                           [](unsigned short el) { return utils::to_hex(el);});
    }

    [[nodiscard]] auto& octets() const {
        return hexs;
    }

    static MAC fromString (const std::string &macAddress){

        static const std::regex macPattern("([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}");
        if (!std::regex_match(macAddress, macPattern))
            throw std::logic_error ("Incorrect MAC address");

        std::vector <std::string> splited;
        boost::algorithm::split(splited, macAddress, boost::algorithm::is_any_of(":"));

        return MAC (utils::to_int(splited[0]), utils::to_int(splited[1]),
                utils::to_int(splited[2]), utils::to_int(splited[3]),
                utils::to_int(splited[4]), utils::to_int(splited[5]));
    }
};
#endif //LAB1_MACADDRESS_HPP
