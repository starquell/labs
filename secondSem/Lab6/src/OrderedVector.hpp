#ifndef LAB6_ORDEREDVECTOR_HPP
#define LAB6_ORDEREDVECTOR_HPP

#include "Point.hpp"

#include <vector>
#include <random>
#include <algorithm>
#include <type_traits>

template <class T>
class OrderedVector {

    std::vector <T> mVec;

public:

    using Iterator = typename std::vector <T>::iterator;

    explicit OrderedVector (size_t n = 0)
        : mVec ()
    {

        if constexpr (std::is_same_v <T, Point>) {

            mVec.reserve (n);

            for (size_t i = 0; i < n; ++i)
                mVec.push_back (Point {});


            std::sort (mVec.begin(), mVec.end());
        }
    }

    explicit OrderedVector (std::vector <T> other) {

        std::stable_sort (other.begin(), other.end());
        mVec = std::move(other);
    }

    void push (const T &data) {

        mVec.insert (std::lower_bound (mVec.begin(), mVec.end(), data), data);
    }

    void erase (Iterator it) {

        mVec.erase (it);
    }

    bool empty () {

        return mVec.empty();
    }

    Iterator begin() {

        return mVec.begin();
    }

    Iterator end() {

        return mVec.end();
    }

    const T& operator[] (size_t n) {

        return mVec [n];
    }
};

#endif //LAB6_ORDEREDVECTOR_HPP