#ifndef STATICARRAY_TPP
#define STATICARRAY_TPP

#include "StaticArray.hpp"

namespace lab::impl {

    template <typename T, std::size_t Size>
    void StaticArrayQueue<T, Size>::push (const T& value) {
        if (m_elems_amount == m_container.size())
            throw std::out_of_range{"Max capacity reached."};
        m_container[m_end] = value;
        ++m_end;
        ++m_elems_amount;
        if (m_end == m_container.size())
            m_end = 0;
    }

    template <typename T, std::size_t Size>
    void StaticArrayQueue<T, Size>::push (T&& value) {
        if (m_elems_amount == m_container.size())
            throw std::out_of_range{"Max capacity reached."};
        m_container[m_end] = std::move(value);
        ++m_end;
        ++m_elems_amount;
        if (m_end == m_container.size())
            m_end = 0;
    }

    template <typename T, std::size_t Size>
    const T& StaticArrayQueue<T, Size>::front () const {
        if (empty())
            throw std::logic_error{"Queue is empty."};
        return m_container[m_begin];
    }

    template <typename T, std::size_t Size>
    bool StaticArrayQueue<T, Size>::empty () const noexcept {
        return m_elems_amount == 0;
    }

    template <typename T, std::size_t Size>
    T StaticArrayQueue<T, Size>::pop () {
        if (empty())
            throw std::logic_error{"Queue is empty."};
        T to_return = std::move(m_container[m_begin]);
        ++m_begin;
        if(m_begin == m_container.size())
            m_begin = 0;
        --m_elems_amount;
        return to_return;
    }

    template <typename T, std::size_t Size>
    StaticArrayQueue<T, Size>::StaticArrayQueue ()
            : m_begin(0),
              m_end(0),
              m_elems_amount(0)
    {}

    template <typename T, std::size_t Size>
    template <typename... Args>
    StaticArrayQueue<T, Size>::StaticArrayQueue (Args&&... args)
            :   m_container({args...}),
                m_begin{0},
                m_end(0),
                m_elems_amount(sizeof...(args))
    {}
}

#endif