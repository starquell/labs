#ifndef LAB6_ORDEREDLIST_HPP
#define LAB6_ORDEREDLIST_HPP

#include "point.hpp"

#include <list>
#include <random>
#include <type_traits>

template <class T, bool Random = false>
class OrderedList {

    std::list <T> mList;

public:

    using Iterator = typename std::list <T>::iterator;

    explicit OrderedList (size_t n = 0)
            : mList ()
    {

        if constexpr (Random && std::is_same_v <T, Point>) {

            static std::mt19937 gen (std::random_device {} ());
            static std::uniform_real_distribution <double> dis (0.0, 1000.0);

            for (size_t i = 0; i < n; ++i)
                mList.push_back ({dis(gen), dis(gen), dis(gen)});

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