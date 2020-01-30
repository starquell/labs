#ifndef LAB1_LINKEDLIST_HPP
#define LAB1_LINKEDLIST_HPP

#include "QueueInterface.hpp"

#include <list>

namespace lab::impl {

    template <typename T>
    class LinkedListQueue : public IQueue<T> {
    public:

        explicit LinkedListQueue() = default;

        template <typename... Ts>
        LinkedListQueue(Ts&&... args);

        void push (const T& value) override;

        void push (T&& value) override;

        T pop () override;

        const T& front() const override;

        [[nodiscard]]
        bool empty() const noexcept override;

        ~LinkedListQueue () noexcept override = default;

    private:
        std::list<T> m_container;
    };
}

#include "LinkedList.tpp"
#endif //LAB1_LINKEDLIST_HPP
