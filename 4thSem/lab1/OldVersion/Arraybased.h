#include <iostream>

template <typename T, size_t N>
class Arraybased {

    T a[N];
    size_t size;

public:

    Arraybased() : size(0) {}

    void push(const T &data) {
        if (size >= N)
            std::cout << "Out of array!";
        else
        a[size++] = data;
    }

    void pop() {
        if (isEmpty())
            return;

        for (auto i = 0; i <= size; ++i)
            a[i] = a[i + 1];

        --size;
    }

    T getFront() {
        return a[0];
    }

    bool isEmpty() {
        return size == 0;
    }
};