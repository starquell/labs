#ifndef LAB1_QUEUE_ARRAYBASED_HPP
#define LAB1_QUEUE_ARRAYBASED_HPP

namespace Queue {
    template<typename T, std::size_t N>
    class Arraybased {

        T mStorage[N];
        std::size_t mSize;

    public:

        Arraybased() : mSize(0) {
        }

        void push (const T &data) {
            if (mSize == N)
                throw std::out_of_range("Out of range");
            else
                mStorage[mSize++] = data;
        }

        void pop() {
            if (empty())
                return;

            for (auto i = 0; i < mSize - 1; ++i)
                mStorage[i] = mStorage[i + 1];

            --mSize;
        }

        const T& front() {
            return mStorage[0];
        }

        [[nodiscard]] bool empty() const {
            return mSize == 0;
        }

        auto size() const {
            return mSize;
        }
    };
}
#endif //LAB1_ARRAYBASED_HPP
