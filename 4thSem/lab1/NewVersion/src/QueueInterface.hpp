#ifndef LAB1_QUEUEINTERFACE_HPP
#define LAB1_QUEUEINTERFACE_HPP

namespace lab::impl{

    /**
     *  @brief Interface for queue implementations
     */
    template <typename T>
    class IQueue {

    protected:
        explicit IQueue () = default;
    public:
        using value_type = T;

        /**
         * @brief Inserts value to end of the queue
         */
        virtual void push (const T& value) = 0;

        /**
         * @brief Inserts value to end of the queue
         */
        virtual void push (T&& value) = 0;

        /**
         *  @brief Removes first element in queue
         */
        virtual T pop() = 0;

        /**
         *  @brief Returns first element in queue
         */
        virtual const T& front() const = 0;

        /**
         *  @brief Returns true if queue is empty
         */
        [[nodiscard]]
        virtual bool empty() const noexcept = 0;

        virtual ~IQueue() noexcept = default;
    };
}
#endif //LAB1_QUEUEINTERFACE_HPP
