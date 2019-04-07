#include <iostream>
#include <cstring>
#include <random>
#include <map>
#include <functional>
#include "sortAlgorithms.h"
#include "benchmarking.h"

void showSet ();

template <class T>
void show (T *arr, size_t size, std::string_view setting);


int main (int argc, char **argv) {

    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0)

       benchmarkSet();

    else
        showSet();

    return 0;
}

void showSet() {

    cout << "Set array size: ";

        size_t size;
        std::cin >> size;

        if (size < 2) {
            cout << "Nothing to sort :(\n";
            return;
        }

        if (size > 300000) {
            cout << "Dont joke with mr Segmentation Fault\n"
            return;
        }

        cout << "Creating random array with size " << size << "...\n";

        std::string arr [size];

        arraySet(arr, size);

        cout << "\n Created!\n"
             << "_________________________\n";

        show(arr, size, "random");
        show(arr, size, "mostly-sorted");
        show(arr, size, "reverse");
}

template <class T>
void show (T *arr, size_t size, std::string_view setting) {

    sleep_for(1.2s);

    cout << "Sorting by selection sort...\n";
    sleep_for(1.75s);

    mySort::selectionSort(arr, 0, size - 1, true);

    arraySet (arr, size, true, setting);

    cout << "Sorting by quick sort...\n";
    sleep_for(1.2s);

    mySort::quickSort(arr, 0, size - 1, true);

    arraySet (arr, size, true, setting);

    cout << "Sorting by merge sort...\n";
    sleep_for(1.2s);

    mySort::mergeSort(arr, 0, size - 1, true);

    arraySet (arr, size, true, setting);

    cout << "Sorting by combined sort...\n";
    sleep_for(1.2s);

    mySort::combinedSort(arr, size, true);

    arraySet (arr, size, true, setting);

    cout << "Sorting by quick sort from <algorithm> ...\n";
    sleep_for(1.2s);

    std::sort (arr, arr + size);              //  sorting lexicographically ar first
    std::sort (arr, arr + size, comp);       //  then sort by length by custom comparator

    arraySet (arr, size, true, "just array out");       // cout sorted array
}