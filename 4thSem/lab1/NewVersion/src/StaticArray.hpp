#ifndef LAB1_STATICARRAY_HPP
#define LAB1_STATICARRAY_HPP

#include "QueueInterface.hpp"

#include <array>

namespace lab::impl {

    /**
     * @brief Class that holds queue implementation based on std::array
     *      \b Operations complexity:
     *      \li Push - O(1)
     *      \li Pop - O(1)
     */
    template <typename T,
              std::size_t Size>
    class StaticArrayQueue : public IQueue<T> {
    public:
        explicit StaticArrayQueue();

        /**
         *  @brief Constructs queue from arbitary number of args
         *  @param Args must be same type
         */
        template <typename... Args>
        StaticArrayQueue(Args&&... args);

        void push (const T& value) override;
        void push (T&& value) override;

        T pop() override;

        const T& front() const override;

        [[nodiscard]]
        bool empty() const noexcept override;

        ~StaticArrayQueue () noexcept override = default;

    private:
        std::array<T, Size> m_container;
        std::size_t m_begin;        /// Index of first element of queue in m_container
        std::size_t m_end;          /// Index of element next to last of queue in m_container
        std::size_t m_elems_amount;
    };
}

#include "StaticArray.tpp"

#endif //LAB1_STATICARRAY_HPP
