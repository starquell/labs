#ifndef LAB1_ARRAYBASED_HPP
#define LAB1_ARRAYBASED_HPP

namespace Deque{

    template <class T, std::size_t N>
    class Arraybased {

        class Iterator {
        public:
            explicit Iterator(T* begin, std::size_t size)
                    : mBegin(begin), mArraySize(size), mPos(0)
            {}

            Iterator& operator++() {
                if (mPos == mArraySize)
                    throw std::out_of_range("");
                ++mPos;
                return *this;
            }

            Iterator& operator--() {
                if (mPos == 0)
                    throw std::out_of_range("");
                --mPos;
                return *this;
            }

            bool operator== (const Iterator &other) const {
                return mBegin == other.mBegin and mPos == other.mPos;
            }

            bool operator!= (const Iterator &other) const {
                return !(*this == other);
            }

            Iterator operator+ (std::size_t index) const {
                if (mPos + index > mArraySize)
                    throw std::out_of_range("");

                Iterator temp (*this);
                temp.mPos += index;
                return temp;
            }

            Iterator operator- (std::size_t index) const {
                if (mPos - index <= 0)
                    throw std::out_of_range("");

                Iterator temp (*this);
                temp.mPos -= index;
                return temp;
            }

            T& operator* () {
                return *(mBegin + mPos);
            }

        private:
            T* mBegin;
            std::size_t mArraySize;
            std::size_t mPos;
        };

    public:

        using value_type = T;

        Arraybased() : mSize(0) {
        }

        void push (const T &data) {
            if (mSize == N)
                throw std::out_of_range("Max capacity is reached.");
            else
                mStorage[mSize++] = data;
        }

        void pushFront (const T& data) {
            if (mSize == N)
                throw std::out_of_range("Max capacity is reached.");

            for (auto i = mSize; i > 0; --i)
                mStorage[i] = mStorage[i - 1];

            mStorage[0] = data;
            ++mSize;
        }

        void popBack() {
            if (mSize == 0)
                return;
            --mSize;
        }

        void popFront(){

            if (mSize == 0)
                return;

            for (auto i = 0; i < mSize - 1; ++i)
                mStorage[i] = mStorage[i + 1];
            --mSize;
        }

        T front() const {
            return mStorage[0];
        }

        T top() const {
            return mStorage[mSize - 1];
        }

        auto size() const {
            return mSize;
        }

        T& operator[] (std::size_t index) {
            return mStorage[index];
        }

        Iterator begin() {
            return Iterator(mStorage, mSize);
        }

        Iterator end() {
            return Iterator(mStorage, mSize) + mSize;
        }

        bool empty() const {
            return mSize == 0;
        }
    private:
        T mStorage[N];
        std::size_t mSize;
    };
}
#endif //LAB1_ARRAYBASED_HPP
