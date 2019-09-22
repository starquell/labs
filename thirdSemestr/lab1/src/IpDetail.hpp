#ifndef LAB1_IPDETAIL_HPP
#define LAB1_IPDETAIL_HPP

#include <sstream>

namespace detail {

    template <class Container, class Unary>
    std::string join(const Container &cont, const std::string &sep, const Unary &transform) {

        std::string result;
        for (auto it = cont.begin(); it != cont.end() - 1; ++it) {
            result += transform(*it) + sep;
        }

        return result + transform(*(cont.end() - 1));
    }

    template<class Integer>
    std::string to_hex(const Integer &dec) {
        std::stringstream stream;
        stream << std::uppercase << std::hex << dec;
        return stream.str();
    }

    unsigned short to_int(const std::string &hex) {
        unsigned short x;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> x;
        return x;
    }
}

#endif