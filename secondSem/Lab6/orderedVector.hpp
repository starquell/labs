#ifndef LAB6_ORDEREDVECTOR_HPP
#define LAB6_ORDEREDVECTOR_HPP

#include "point.hpp"

#include <vector>
#include <random>
#include <algorithm>
#include <type_traits>

template <class T>
class OrderedVector {

    std::vector <T> mVec;


public:

    using Iterator = typename std::vector <T>::iterator;

    explicit OrderedVector (bool random = false, size_t n = 0)
        : mVec ()
    {

        if (random && std::is_same_v <T, Point>) {

            std::mt19937 gen;
            std::uniform_real_distribution <double> distribution (0, 1000);

            mVec.reserve (n);

            for (size_t i = 0; i < n; ++i)
                mVec.emplace_back (distribution (gen), distribution (gen), distribution (gen));

            std::stable_sort (mVec.begin(), mVec.end());
        }
    }

    explicit OrderedVector (size_t count, const T &value = T())

        : mVec (count, value)
    {}

    OrderedVector (std::vector <T> other) {

        std::stable_sort (other.begin(), other.end());
        mVec = std::move(other);
    }

    OrderedVector (const OrderedVector <T> &other) = default;

    OrderedVector (OrderedVector <T> &&other) = default;

    void push (const T &data) {

        mVec.insert (std::lower_bound (mVec.begin(), mVec.end(), data), data);
    }

    void erase (Iterator it) {

        mVec.erase (it);
    }

    void erase (Iterator beg, Iterator end) {

        mVec.erase (beg, end);
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
};


#endif //LAB6_ORDEREDVECTOR_HPP
