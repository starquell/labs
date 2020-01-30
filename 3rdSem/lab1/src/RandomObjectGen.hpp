#ifndef LAB1_RANDOMOBJECTGEN_HPP
#define LAB1_RANDOMOBJECTGEN_HPP

#include <random>
#include <string>
#include <vector>
#include <limits>

#include "Stack/Arraybased.hpp"
#include "Stack/Listbased.hpp"
#include "Stack/LibImpl.hpp"
#include "Queue/Arraybased.hpp"
#include "Queue/Listbased.hpp"
#include "Queue/LibImpl.hpp"
#include "IPs/IPV4.hpp"
#include "IPs/IPv6.hpp"
#include "IPs/CIDR.hpp"
#include "Deque/Listbased.hpp"
#include "Deque/LibImpl.hpp"


template <typename R, typename Something, class... Args>
auto randomObject() -> R;

template <typename T, T from = std::numeric_limits<T>::min(),
         T to = std::numeric_limits<T>::max(),
         typename = std::enable_if_t<std::is_integral_v<T> || std::is_same_v<T, double>>>

auto randomObject() {

    static std::mt19937 gen(std::random_device{}());

    if constexpr (std::is_integral_v<T>) {
        static std::uniform_int_distribution<T> dis(from, to);
        return dis(gen);
    }
    else {
        static std::uniform_real_distribution<double> dis(from, to);
        return dis(gen);
    }

}

template<typename T, typename Container>
constexpr inline bool hasPush = std::is_same_v<Container, Stack::Listbased<T>>
                             || std::is_same_v<Container, Stack::STLImpl<T>>
                             || std::is_same_v<Container, Queue::Listbased<T>>
                             || std::is_same_v<Container, Queue::STLImpl<T>>;


template <typename Container>
constexpr inline bool hasPushBack = std::is_same_v <Container, std::vector<typename Container::value_type>>
                                 || std::is_same_v<Container, Deque::Listbased<typename Container::value_type>>
                                 || std::is_same_v<Container, Deque::STLImpl<typename Container::value_type>>;



template <typename Container, std::size_t size,
          typename = std::enable_if_t <std::is_same_v <Container, std::string>
                                       || hasPush<Container>
                                       || hasPushBack <Container>>>
auto randomObject() {

    Container result;
    if constexpr (hasPush <Container>) {

        for (auto i = 0; i < size; ++i)
            result.push(randomObject<typename Container::value_type>());
        return result;
    }
    else if constexpr (hasPushBack <Container>) {
        for (auto i = 0; i < size; ++i)
            result.pushBack(randomObject<typename Container::value_type>());
        return result;
    }
    else {
        static std::string alphabet = "qwertyuiopasdfghjklzxcvbnm1234567890";

        for (auto i = 0; i < alphabet.size() - 1; ++i)
            result += alphabet[randomObject <size_t, 0, 24>()];
        return result;
    }
}



template <typename IP,
          typename = std::enable_if_t <std::is_same_v<IP, IPv4>
                                    || std::is_same_v<IP, IPv6>>>
auto randomObject () {

    if constexpr (std::is_same_v<IP, IPv4>) {
        return IPv4 (randomObject<uint8_t, 0, 255> (),
                     randomObject<uint8_t, 0, 255> (),
                     randomObject<uint8_t, 0, 255> (),
                     randomObject<uint8_t, 0, 255> ());
    }
    else {
        return IPv6 (randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> (),
                     randomObject<uint16_t, 0, std::numeric_limits<uint16_t>::max()> ());
    }
};

template <typename ParCIDR, typename IP,
          typename = std::enable_if_t <std::is_same_v<CIDR<IP>>>>
auto randomObject () {
    if constexpr (std::is_same<IP, IPv4>::value)
        return CIDR<IP> (randomObject<IPv4>(),
                         randomObject<int, 0, IPv4::bitsNumber()/2> ());
    else
        return  CIDR<IP> (randomObject<IPv6>(),
                          randomObject<int, 0, IPv6::bitsNumber()/2> ());
};

#endif //LAB1_RANDOMOBJECTGEN_HPP
