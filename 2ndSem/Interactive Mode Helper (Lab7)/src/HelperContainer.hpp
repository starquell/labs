#ifndef LAB7_HELPERCONTAINER_HPP
#define LAB7_HELPERCONTAINER_HPP

#include "Helper.hpp"


class HelperContainer {

private:

    std::vector<Helper> mHelpers;
    unsigned counter = 0;

    friend HelperContainer operator| (HelperContainer &&container, Helper helper);
    friend HelperContainer operator| (Helper lhs, Helper rhs);

public:

    HelperContainer (Helper helper) {

        mHelpers.push_back(std::move (helper));
    }

    HelperContainer (std::initializer_list<Helper> list)
            : mHelpers(list) {
    }

    template <class... Funcs>
    void bind (Funcs &&... funcs) {

        if (sizeof... (funcs) > mHelpers.size())
            throw std::logic_error {"Number of callable functions can't be bigger than number of helpers."};

        bindImpl(std::forward<Funcs> (funcs)...);
    }

private:

    void push (Helper &&helper) {

        mHelpers.push_back (std::forward <Helper>(helper));
    }

    template<class Func>
    void bindImpl (Func &&func) {

        mHelpers[counter++].bind(std::forward<Func>(func));
    }

    template<class FuncHead, class... Funcs>
    void bindImpl (FuncHead &&funcHead, Funcs &&... funcs) {

        mHelpers[counter++].bind(std::forward<FuncHead>(funcHead));
        bindImpl(std::forward<Funcs>(funcs)...);
    }

public:

    void operator[] (unsigned n) {

        if (n < 0 || n >= mHelpers.size())
            throw std::out_of_range{"Invalid index"};

        mHelpers[n]();
    }

    void launchAll () {

        for (auto &i : mHelpers)
            i();
    }

};

using Helpers = HelperContainer;

HelperContainer operator| (Helper lhs, Helper rhs) {

    HelperContainer container (std::move (lhs));
    container.push (std::move (rhs));

    return container;
}

HelperContainer operator| (HelperContainer &&container, Helper helper) {

    container.push (std::move (helper));
    return container;
}



#endif //LAB7_HELPERCONTAINER_HPP
