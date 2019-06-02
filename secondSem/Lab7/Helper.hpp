#ifndef LAB7_HELPER_HPP
#define LAB7_HELPER_HPP

#include <array>
#include <tuple>
#include <iostream>
#include <functional>
#include <initializer_list>
#include <any>
#include <memory>
#include <boost/callable_traits.hpp>
#include <type_traits>


template <class... Ts>
class Helper {


public:

    template <class... T, class... Args>
    Helper <T...> (std::function <void (Ts...)> func)

            : mFunc (std::move (func))
    {}


    auto operator [] (std::string_view arg) {

        mNames.push_back (arg.data ());
        return *this;
    }

    void operator () () {

        if (mNames.size() != sizeof... (Ts))
            throw std::logic_error {"idy v pizdu"};

             read <0> ();

        std::apply (mFunc, mValues);
    }


private:

    template <int N>
    void read() {

        std::cout << mNames [N] << ": ";
        std::cin >> std::get <N> (mValues);

        if constexpr (N + 1 < sizeof... (Ts))
            read <N + 1> ();
    }

private:

    std::vector <std::string> mNames;
    std::tuple <Ts...> mValues;
    std::function <void (Ts...)> mFunc;
};

template <class... Args>
Helper (std::function <void (Args...)>) -> Helper <Args...>;



class HelperContainer {

private:

    std::vector <std::any> mHelpers;


public:

    template <class... Ts>
    HelperContainer (Helper <Ts...> && helper) {

        mHelpers.push_back (std::any (std::move (helper)));
    }


    template <class... Ts>
    void push (Helper <Ts...> && helper) {

        mHelpers.push_back (std::any (std::move (helper)));
    }

    template <class... Ts>
    auto get (unsigned n) {

        return std::any_cast <Helper <Ts...>> (mHelpers[n]) ();
    }


};

template <class... lhsTs, class... rhsTs>
HelperContainer operator | (Helper <lhsTs...> && lhs, Helper <rhsTs...> && rhs) {

    HelperContainer container (std::move (lhs));
    container.push (std::move (rhs));

    return container;
}

template <class... Ts>
HelperContainer operator | (HelperContainer&& container, Helper <Ts...> && helper) {

    container.push (std::move (helper));
    return container;
}




#endif //LAB7_HELPER_HPP
