#ifndef LAB1_STACK_ARRAYBASED_HPP
#define LAB1_STACK_ARRAYBASED_HPP

namespace Stack {

    template <typename T, std::size_t N>
    class Arraybased {

        T mStorage[N];
        std::size_t mSize;

    public:

        Arraybased() : mSize(0) {
        }

        void push (const T &data) {
            if (mSize == N)
                throw std::out_of_range("Max capacity is reached.");
            else
                mStorage[mSize++] = data;
        }

        void pop() {
            if (empty())
                return;

            --mSize;
        }

        const T &top() {
            return mStorage[mSize - 1];
        }

        [[nodiscard]] bool empty() const {
            return mSize == 0;
        }

        auto size() const {
            return size;
        }


    };
}

#endif