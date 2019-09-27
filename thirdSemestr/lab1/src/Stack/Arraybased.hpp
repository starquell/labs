#ifndef LAB1_STACK_ARRAYBASED_HPP
#define LAB1_STACK_ARRAYBASED_HPP

namespace Stack {

    template <typename T, size_t N>
    class Arraybased {

        T a[N];
        size_t size;

    public:

        using value_type = T;

        Arraybased() : size(0) {
        }

        void push(const value_type &data) {
            if (size >= N)
                std::cout << "Out of array!";
            else
                a[size++] = data;
        }

        void pop() {
            if (empty())
                return;

            for (auto i = 0; i <= size; ++i)
                a[i] = a[i + 1];

            --size;
        }

        T &front() const {
            return a[0];
        }

        [[nodiscard]] bool empty() const {
            return size == 0;
        }
    };
}

#endif