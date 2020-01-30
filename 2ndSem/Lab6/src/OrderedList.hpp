#ifndef LAB6_ORDEREDLIST_HPP
#define LAB6_ORDEREDLIST_HPP

#include "Point.hpp"

#include <list>
#include <random>
#include <type_traits>
#include <algorithm>

template <class T>
class OrderedList {

    std::list <T> mList;

public:

    using Iterator = typename std::list <T>::iterator;

    explicit OrderedList (size_t n = 0)
            : mList ()
    {

        if constexpr (std::is_same_v <T, Point>) {

            for (size_t i = 0; i < n; ++i)
                mList.push_back (Point {});

            mList.sort();
        }
    }

    explicit OrderedList (std::list <T> other) {

        other.sort();
        mList = std::move (other);
    }

    void push (const T &data) {

        mList.insert (std::lower_bound (mList.begin(), mList.end(), data), data);
    }

    bool find (const T& value)  {

        return std::binary_search (begin(), end(), value);
    }

    void erase (Iterator it) {

        mList.erase (it);
    }

    bool empty () {

        return mList.empty();
    }

    Iterator begin() {

        return mList.begin();
    }

    Iterator end() {

        return mList.end();
    }

};

#endif //LAB6_ORDEREDLIST_HPP