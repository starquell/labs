#ifndef LAB1_QUEUE_LIBIMPL_HPP
#define LAB1_QUEUE_LIBIMPL_HPP

#include <queue>

namespace Queue {

    template <class T>
    class STLImpl {

        std::queue <T> mStorage;

    public:

        using value_type = T;

        void push (const T& data) {
            mStorage.push(data);
        }

        void pop() {
            mStorage.pop();
        }

        T front() const {
            return mStorage.front();
        }

        auto size() const {
            return mStorage.size();
        }
    };
}
#endif //LAB1_LIBIMPL_HPP
