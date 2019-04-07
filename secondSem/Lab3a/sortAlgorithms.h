#include <algorithm>
#include <chrono>
#include <thread>
#include "stringComparison.h"

using namespace std::chrono_literals;
using std::this_thread::sleep_for;
using std::cout;

namespace mySort {

    template<class T>
    void selectionSort(T *arr, int beg, int end, bool show = false) {

        int min;

        for (int i = beg; i < end; ++i) {

            min = i;

            for (int j = i + 1; j <= end; ++j)
                if (arr[j] < arr[min])
                    min = j;

            std::swap(arr[min], arr[i]);

            if (show) {

                cout << "Selected minimal element on this step: "
                     << arr[i] << ".\n";

                cout << "Rest of array : {";

                for (int j = i + 1; j < end; ++j)
                    cout << arr[j] << ' ';
                cout << "}\n\n";

                sleep_for(1s);
            }
        }
    }


    template<class T>
    void quickSort(T *arr, int beg, int end, bool show = false, bool combined = false) {

        int l = beg,
            r = end;

        T mid = arr[(l + r) / 2];

        if (show) {
            cout << "Sorting subarray: {";

            for (int i = l; i < r; ++i)
                cout << arr[i] << ' ';

            cout << "}\n";

            sleep_for(1s);
        }

        while (l < r) {

            while (arr[l] < mid)
                ++l;

            while (arr[r] > mid)
                --r;

            if (l <= r) {
                std::swap(arr[l++], arr[r--]);
            }
        }


        if (r > beg) {

            if (r - beg < 10 && combined)
                selectionSort(arr, beg, r, show);
            else
                quickSort(arr, beg, r, show);
        }

        if (l < end) {

            if (end - l < 10 && combined)
                selectionSort(arr, l, end, show);
            else
                quickSort(arr, l, end, show);
        }
    }

    template<class T>
    void merge(T *arr, int left, int mid, int right, bool show = false) {

        int leftSize = mid - left + 1;
        int rightSize = right - mid;

         T tempLeft[leftSize],      // temporary arrays for merge
           tempRight[rightSize];

        for (int i = 0; i < leftSize; ++i)        // filling temps by halfs of out interval [left, right]
            tempLeft[i] = arr[left + i];

        for (int j = 0; j < rightSize; ++j)
            tempRight[j] = arr[mid + 1 + j];

        if (show) {

            cout << "Arrays to merge : {";

            for (int i = 0; i < leftSize; ++i)
                cout << tempLeft[i] << ' ';

            cout << "} , { ";

            for (int i = 0; i < rightSize; ++i)
                cout << tempRight[i] << ' ';

            cout << "}\n\n";
            sleep_for(1s);
        }

        int i = 0,          // indexes for merge
                j = 0;
        int k = left;       // starting index of arr[]

        while (i < leftSize && j < rightSize) {

            if (tempLeft[i] <= tempRight[j])

                arr[k] = tempLeft[i++];

            else
                arr[k] = tempRight[j++];

            ++k;
        }

        while (i < leftSize)             // filling arr[] by rest
            arr[k++] = tempLeft[i++];


        while (j < rightSize)
            arr[k++] = tempRight[j++];
    }

    template<class T>
    void mergeSort(T *arr, int left, int right, bool show = false) {

        if (left < right) {

            int mid = left + (right - left) / 2;

            if (show && right - left != 1) {

                cout << "Subarray to sort: {";

                for (int i = left; i < right; ++i)
                    cout << arr[i] << ' ';

                cout << "}\n";

                sleep_for(1s);
            }

            mergeSort(arr, left, mid, show);
            mergeSort(arr, mid + 1, right, show);

            merge(arr, left, mid, right, show);
        }
    }


    template <class T>
    void combinedSort(T *arr, size_t size, bool show = false) {

        if (size > 10)
            quickSort (arr, 0, size - 1, show, true);
        else
            selectionSort (arr, 0, size - 1, show);
    }
}