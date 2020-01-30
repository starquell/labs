#ifndef LAB1_DYNAMICARRAY_TPP
#define LAB1_DYNAMICARRAY_TPP

#include "DynamicArray.hpp"
#include <stdexcept>

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
        return m_container.size() - m_begin == 0;
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


