#ifndef LAB1_QUEUEINTERFACE_HPP
#define LAB1_QUEUEINTERFACE_HPP

namespace lab::impl{

    template <typename T>
    class IQueue {

    protected:
        explicit IQueue () = default;
    public:
        using value_type = T;

        virtual void push (const T& value) = 0;
        virtual void push (T&& value) = 0;
        virtual T pop() = 0;
        virtual const T& front() const = 0;

        [[nodiscard]]
        virtual bool empty() const noexcept = 0;

        virtual ~IQueue() noexcept = default;
    };
}
#endif //LAB1_QUEUEINTERFACE_HPP
