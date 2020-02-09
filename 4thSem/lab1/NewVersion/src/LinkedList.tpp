#ifndef LAB1_LINKEDLIST_TPP
#define LAB1_LINKEDLIST_TPP

#include "LinkedList.hpp"

namespace lab::impl {

    template <typename T>
    void LinkedListQueue<T>::push (const T& value) {
        m_container.push_back(value);
    }

    template <typename T>
    void LinkedListQueue<T>::push (T&& value) {
        m_container.push_back(std::move(value));
    }

    template <typename T>
    T LinkedListQueue<T>::pop () {
        T temp = std::move(*m_container.begin());
        m_container.erase(m_container.begin());
        return temp;
    }

    template <typename T>
    const T& LinkedListQueue<T>::front () const {
        if (empty())
            throw std::logic_error{"Max capacity reached."};
        return *m_container.begin();
    }

    template <typename T>
    bool LinkedListQueue<T>::empty () const noexcept {
        return m_container.empty();
    }

    template <typename T>
    template <typename... Ts>
    LinkedListQueue<T>::LinkedListQueue (Ts&&... args)
            : m_container({args...})
    {}
}

#endif