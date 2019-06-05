#ifndef LAB7_HELPERCONTAINER_HPP
#define LAB7_HELPERCONTAINER_HPP


#include "Helper.hpp"
#include "Method.hpp"


//class Helpers {
//
//private:
//
//    std::vector <std::function <void ()>> mFuncs;
//    std::vector <Helper> mHelpers;
//    int counter = 0;
//
//public:
//
//
//    Helpers (Helper&& helper) {
//
//        mHelpers.push_back (std::forward <Helper> (helper));
//    }
//
//
//    void push (Helper&& helper) {
//
//        mHelpers.push_back (std::forward <Helper> (helper));
//    }
//
//    template <class Func>
//    void bind (Func&& func) {
//
//        mFuncs.push_back ([&, counter = counter] {mHelpers [counter] (func);});
//        ++counter;
//    }
//
//    template <class FuncHead, class... Funcs>
//    void bind (FuncHead &&funcHead, Funcs &&... funcs) {
//
//        mFuncs.push_back ([&, counter = counter] {mHelpers [counter] (funcHead);});
//        ++counter;
//        bind (std::forward <Funcs> (funcs)...);
//    }
//
//    template <class HeadMethod, class HeadObj, class... MethodType,  class...ObjType>
//    void bind (Method <HeadMethod, HeadObj>&& headMethod, Method <MethodType, ObjType>&&... method) {
//
//        auto notMember = std::mem_fn (&headMethod.method());
//        auto binding = std::bind (notMember, &headMethod.object(), )
//    }
//
//
//
//    void operator [] (unsigned n) {
//
//        mFuncs [n] ();
//    }
//};

class Helpers {

private:

    std::vector <Helper> mHelpers;
    unsigned counter = 0;

public:


    Helpers (Helper&& helper) {

        mHelpers.push_back (std::forward <Helper> (helper));
    }


    void push (Helper&& helper) {

        mHelpers.push_back (std::forward <Helper> (helper));
    }

    template <class Func>
    void bind (Func&& func) {

        mHelpers [counter++].bind (std::forward <Func> (func));
    }

    template <class FuncHead, class... Funcs>
    void bind (FuncHead &&funcHead, Funcs &&... funcs) {

        if (sizeof... (funcs) + 1 > mHelpers.size())
            throw ()
        mHelpers [counter++].bind (std::forward <FuncHead> (funcHead));
        bind (std::forward <Funcs> (funcs)...);
    }


    void operator [] (unsigned n) {

        if (n < 0 || n >= mHelpers.size())
            throw std::out_of_range {"Invalid index"};

        mHelpers [n] ();
    }
};


Helpers operator | (Helper&& lhs, Helper&& rhs) {

    Helpers container (std::move (lhs));
    container.push (std::move (rhs));

    return container;
}


Helpers operator | (Helpers && container, Helper&& helper) {

    container.push (std::move (helper));
    return container;
}


#endif //LAB7_HELPERCONTAINER_HPP
