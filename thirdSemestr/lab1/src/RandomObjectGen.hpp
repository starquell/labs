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


template <class Integer>
class RandomObjectGenerator {

public:
    Integer operator()(int from = 0, int to = std::numeric_limits<Integer>::max()) {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<Integer> dis(from, to);
        return dis(gen);
    }
};

template <>
class RandomObjectGenerator <double> {

public:
    int operator ()(int from = 0, int to = 1000000){
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_real_distribution<double> dis(from, to);
        return dis(gen);
    }
};

template <>
class RandomObjectGenerator <std::string> {

public:
    std::string operator()(std::size_t size = 10){
        static std::string alphabet = "qwertyuiopasdfghjklzxcvbnm1234567890";
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_real_distribution<double> dis(0, alphabet.size() - 1);
        std::string result;
        for (auto i = 0; i <alphabet.size() - 1; ++i)
            result += alphabet[dis(gen)];
        return result;
    }
};

template <class T>
class RandomObjectGenerator <std::vector<T>> {

public:
    std::vector<T> operator()(std::size_t size = 10) {
        std::vector <T> result (size);
        RandomObjectGenerator<T> gen;
        for (auto i = 0; i < size; ++i)
            result.push_back(gen());
        return result;
    }
};

template <>
class RandomObjectGenerator <IPv4> {

public:
    IPv4 operator() () {
        RandomObjectGenerator<uint8_t> gen;
        return IPv4 (gen(), gen(), gen(), gen());
    }
};

template <>
class RandomObjectGenerator <IPv6> {

public:
    IPv6 operator() (){
        RandomObjectGenerator<uint16_t> gen;
        return IPv6(gen(), gen(), gen(), gen(),
                gen(), gen(), gen(), gen());
    }
};

template <class IP>
class RandomObjectGenerator <CIDR<IP>> {

public:
    CIDR<IP> operator ()(){
        if constexpr (std::is_same<IP, IPv4>::value)
            return CIDR<IP> (RandomObjectGenerator<IPv4>{}(),
                             RandomObjectGenerator<int>{}(0, IPv4::bitsNumber()/2));
        if constexpr (std::is_same<IP, IPv6>::value)
            return  CIDR<IP> (RandomObjectGenerator<IPv6>{}(),
                              RandomObjectGenerator<int>{}(0, IPv6::bitsNumber()/2));
    }
};

//template <class Container, class T>
//class RandomObjectGenerator <Container<T>> {
//
//public:
//    Container<T> operator()(std::size_t size = 10) {
//        Container<T> result;
//        RandomObjectGenerator<T> gen;
//        for (auto i = 0; i < size; ++i)
//            result.push(gen());
//        return result;
//    }
//};

#endif //LAB1_RANDOMOBJECTGEN_HPP
