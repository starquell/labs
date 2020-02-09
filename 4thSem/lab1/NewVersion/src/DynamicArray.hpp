#ifndef LAB1_DYNAMICARRAY_HPP
#define LAB1_DYNAMICARRAY_HPP

#include "QueueInterface.hpp"

#include <vector>

namespace lab::impl {

    /**
     * @brief Class that holds queue implementation based on std::vector
     *      \b Operations complexity:
     *      \li Push - O(1)
     *      \li Pop - O(1)
     */
    template <typename T>
    class DynamicArrayQueue : public IQueue<T> {
    public:

        explicit DynamicArrayQueue();

        /**
        *  @brief Constructs queue from arbitary number of args
        *  @param Args must be same type
        */
        template <typename... Ts>
        DynamicArrayQueue(Ts&&... args);

        void push (const T& value) override;

        void push (T&& value) override;

        T pop() override;

        const T& front() const override;

        [[nodiscard]]
        bool empty() const noexcept override;

        ~DynamicArrayQueue () noexcept override = default;

    private:
        std::vector<T> m_container;
        std::size_t m_begin;              /// Index of first element of queue in vector
        static constexpr std::size_t MAX_UNUSED_MEMORY = 100;  /// Max possible unused indexes in front of vector

    };
}

#include "DynamicArray.tpp"
#endif //LAB1_DYNAMICARRAY_HPP
