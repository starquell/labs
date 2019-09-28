#ifndef LAB1_STACK_LIBIMPL_HPP
#define LAB1_STACK_LIBIMPL_HPP

#include <stack>

namespace Stack {

    template <class T>
    class STLImpl {

        std::stack <T> mStorage;

    public:

        void push (const T& data) {
            mStorage.push(data);
        }

        void pop() {
            mStorage.pop();
        }

        T& top() const {
            return mStorage.top();
        }

        auto size() const {
            return mStorage.size();
        }
    };
}

#endif