#ifndef LAB1_LIBIMPL_HPP
#define LAB1_LIBIMPL_HPP

#include <deque>

namespace Deque {

    template <class T>
    class STLImpl {

        std::deque <T> mStorage;

    public:

        using value_type = T;

        void pushFront(const T& data) {
            mStorage.push_front(data);
        }

        void push(const T& data) {
            mStorage.push_back(data);
        }

        void popFront() {
            mStorage.pop_front();
        }

        void popBack() {
            mStorage.pop_back();
        }

        T front() const {
            return mStorage.front();
        }

        T top() const {
            return mStorage.back();
        }

        auto size() const {
            return mStorage.size();
        }

        T& operator[](std::size_t index) {
            if (index >= mStorage.size())
                throw std::out_of_range("");
            return mStorage[index];
        }

        auto begin() const {
            return mStorage.begin();
        }

        auto end() const {
            return mStorage.end();
        }

        bool empty () const {
            return mStorage.empty();
        }
    };
}
#endif //LAB1_LIBIMPL_HPP
