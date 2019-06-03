#ifndef LAB7_HELPER_HPP
#define LAB7_HELPER_HPP

#include <tuple>
#include <iostream>
#include <functional>
#include <initializer_list>
#include <boost/callable_traits.hpp>
#include <type_traits>
#include <any>
#include <memory>




template <class... Ts>
class Helper {

public:

    Helper (std::function <void (Ts...)> func)

            : mFunc (std::move (func))
    {}


    auto operator [] (std::string_view arg) {

        mNames.push_back (arg.data ());
        return *this;
    }

    void operator () () {

        if (mNames.size() != sizeof... (Ts))
            throw std::logic_error {"--------"};

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
    std::tuple <Ts...> mValues;
    std::function <void (Ts...)> mFunc;
    std::vector <std::string> mNames;

};





class Helpers {



public:




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
