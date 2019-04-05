
bool operator< (const std::string &lhs, const std::string &rhs) {

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    for (int i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return lhs[i] <  rhs[i];
    }

    return false;
}

template <class T>
void selectionSort (T *arr, size_t n) {

    int min;

    for (int i = 0; i < n - 1; ++i) {

        min = i;

        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[min])
                min = j;

        std::swap(arr[min], arr[i]);
    }
}

