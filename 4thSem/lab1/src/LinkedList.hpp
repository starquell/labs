#ifndef LAB1_LINKEDLIST_HPP
#define LAB1_LINKEDLIST_HPP

#include "QueueInterface.hpp"

#include <list>

namespace lab::impl {

    /**
     * @brief Class that holds queue implementation based on std::list
     *      \b Operations complexity:
     *      \li Push - O(1)
     *      \li Pop - O(1)
     */
    template <typename T>
    class LinkedListQueue : public IQueue<T> {
    public:

        explicit LinkedListQueue() = default;

        /**
         *  @brief Constructs queue from arbitary number of args
         *  @param Args must be same type
         */
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
