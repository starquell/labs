#ifndef LAB1_DYNAMICARRAY_HPP
#define LAB1_DYNAMICARRAY_HPP

#include "QueueInterface.hpp"

#include <vector>
#include <initializer_list>

namespace lab::impl {

    template <typename T>
    class DynamicArrayQueue : public IQueue<T> {
    public:

        explicit DynamicArrayQueue();

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
        std::size_t m_begin;
    };
}

#include "DynamicArray.tpp"
#endif //LAB1_DYNAMICARRAY_HPP
