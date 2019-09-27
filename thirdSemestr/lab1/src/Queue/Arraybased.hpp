#ifndef LAB1_ARRAYBASED_HPP
#define LAB1_ARRAYBASED_HPP

namespace Queue {
    template<typename T, size_t N>
    class Arraybased {

        T a[N];
        size_t size;

    public:

        using value_type = T;

        Arraybased() : size(0) {
        }

        void push(const value_type &data) {
            if (size >= N)
                throw std::out_of_range("Out of range");
            else
                a[size++] = data;
        }

        void pop() {
            if (empty())
                return;

            --size;
        }

        T &front() const {
            return a[size - 1];
        }

        [[nodiscard]] bool empty() const {
            return size == 0;
        }
    };
}
#endif //LAB1_ARRAYBASED_HPP
