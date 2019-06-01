#ifndef LAB7_HELPER_HPP
#define LAB7_HELPER_HPP

#include <array>
#include <tuple>
#include <iostream>
#include <functional>
#include <initializer_list>
#include <any>


template <class... Ts>
class Helper {

    static constexpr auto argNum = sizeof...(Ts);
    static_assert (argNum > 0, "Template should have one parameter at least.");

public:


    Helper (std::initializer_list <std::string> args) {

        std::copy (args.begin(), args.end(), mNames.begin());
    }

    template <class Func>
    auto set (Func&& func) {

        mFunc = func;
        return *this;
    }

    void operator () () {

        read <0> ();
        std::apply (mFunc, mValues);
    }


private:

    template <int N>
    void read() {

        std::cout << std::get<N> (mNames) << ": ";
        std::cin >> std::get<N> (mValues);

        if constexpr (N + 1 < argNum)
            read <N + 1> ();
    }

private:

    std::array <std::string, argNum> mNames;
    std::tuple <Ts...> mValues;
    std::function <void (Ts...)> mFunc;
};


class HelperContainer {

private:

    std::vector <std::any> mHelpers;


public:

    template <class... Ts>
    HelperContainer (Helper <Ts...> && helper) {

        mHelpers.emplace_back (std::move (helper));
    }


    template <class... Ts>
    void push (Helper <Ts...> && helper) {

        mHelpers.emplace_back (std::any (std::move (helper)));
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
