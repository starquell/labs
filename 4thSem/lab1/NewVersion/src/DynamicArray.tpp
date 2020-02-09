#ifndef LAB1_DYNAMICARRAY_TPP
#define LAB1_DYNAMICARRAY_TPP

#include "DynamicArray.hpp"

#include <stdexcept>
#include <algorithm>

namespace lab::impl {

    template <typename T>
    void DynamicArrayQueue<T>::push (T&& value) {
        m_container.push_back(std::move(value));
    }

    template <typename T>
    void DynamicArrayQueue<T>::push (const T& value) {
        m_container.push_back(value);
    }

    template <typename T>
    T DynamicArrayQueue<T>::pop () {
        if (empty())
            throw std::logic_error{"Max capacity reached."};

        if (m_begin == MAX_UNUSED_MEMORY - 1) {
            /// Moving elements to beginning of vector to save space.
            const auto size = std::distance(m_container.begin() + m_begin, m_container.end());

            auto end_of_new_range = std::move(m_container.begin() + m_begin,
                                              m_container.end(),
                                              m_container.begin());
            m_container.resize(size);
            m_begin = 0;
        }

        T to_return = std::move(m_container[m_begin]);
        ++m_begin;
        return to_return;
    }

    template <typename T>
    const T& DynamicArrayQueue<T>::front () const {
        if (empty())
            throw std::logic_error{"Max capacity reached."};
        return m_container[m_begin];
    }

    template <typename T>
    bool DynamicArrayQueue<T>::empty () const noexcept {
        return m_container.size() == m_begin;
    }

    template <typename T>
    DynamicArrayQueue<T>::DynamicArrayQueue ()
            : m_container(),
              m_begin(0)
    {}

    template <typename T>
    template <typename... Ts>
    DynamicArrayQueue<T>::DynamicArrayQueue (Ts&&... args)
            : m_container({args...}),
              m_begin(0)
    {}
}

#endif


