#ifndef LAB7_HELPER_HPP
#define LAB7_HELPER_HPP


#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <initializer_list>
#include "../boost_callable_traits/include/boost/callable_traits/args.hpp"

class Helper {

public:

    Helper (std::initializer_list <std::string> commands)

            : mNames (commands)
    {}

    template <typename T>
    struct GetArity : GetArity <decltype (&T::operator())> {};

    template <typename R, typename... Args>
    struct GetArity <R(*)(Args...)> : std::integral_constant <unsigned, sizeof...(Args)> {};

    template <typename R, typename C, typename... Args>
    struct GetArity <R(C::*)(Args...)> : std::integral_constant <unsigned, sizeof...(Args)> {};

    template <typename R, typename C, typename... Args>
    struct GetArity <R(C::*)(Args...) const> : std::integral_constant <unsigned, sizeof...(Args)> {};

    template <class Func>
    void bind (Func &&func) {

        mFunc = [&] {

            if constexpr (GetArity <std::decay_t <Func>> {} != 0) {

                using ArgsTuple = boost::callable_traits::args_t <Func>;

                if (std::tuple_size <ArgsTuple>::value != mNames.size())
                    throw std::logic_error {"Number of function arguments must be equal to asked arguments"};

                ArgsTuple arguments{};
                read <0> (arguments);

                std::apply (std::forward <Func> (func), arguments);
            }

            else
                func ();
        };
    }


    void operator () () {

        mFunc ();
    }


private:

    template <int N, class Tuple>
    void read (Tuple &tuple) {

        auto size = mNames.size();

        std::cout << mNames [N] << ": ";
        std::cin >> std::get <N> (tuple);

        if constexpr (N + 1 < std::tuple_size <Tuple>::value)
            read <N + 1> (tuple);
    }


private:

    std::function <void ()> mFunc;
    std::vector <std::string> mNames;
};




#endif //LAB7_HELPER_HPP
