#include <iostream>
#include <cstring>
#include <random>
#include <map>
#include <functional>
#include "sortAlgorithms.h"

void benchmark (),
     showSet ();

template <class T>
void show (T *arr, size_t size, std::string_view setting);

template <class T>
void arraySet (T *arr, size_t size, bool show = false, std::string_view setting = "random");


int main (int argc, char **argv) {

    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0) {

//        benchmark();
    }

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

    std::sort (arr, arr + size);
    std::sort (arr, arr + size, comp);

    arraySet (arr, size, true, "just array out");
}


template <class T>
void arraySet (T *arr, size_t size, bool show, std::string_view setting) {

    const static std::string stringStorage [] = {"part", "partt", "partr",
                                                 "aart", "aaart", "paet",
                                                 "rart", "parrrtition", "pa",
                                                 "pvrt", "pqer", "par",
                                                 "partition", "party", "patrick",
                                                 "aert", "parts", "pqqt",
                                                 "partitition", "artition"};

    if (show) {
        sleep_for(1s);
        cout << "Sorted array: {";

        for (int i = 0; i < size; ++i)
            cout << arr[i] << ' ';

        cout << "}\n"
             << "_________________________________________\n";

    }

    if (setting == "random") {

        cout << "*************************************\n"
             << "   Randomizing elements in array...\n"
             << "*************************************\n";

        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<int> rand(0, std::size(stringStorage) - 1);

        for (int i = 0; i < size; ++i)
            arr[i] = stringStorage[rand(gen)];
    }

    if (setting == "mostly-sorted") {

        if (show) {
            cout << "****************************************************************\n"
                 << "   Replacing some elements to create mostly sorted array...\n"
                 << "****************************************************************\n";
            sleep_for(1s);
        }

        mySort::quickSort(arr, 0, size - 1);
        std::swap(arr[0], arr[size / 2]);

        if (show) {
            cout << "\nArray to sort : {";

            for (int i = 0; i < size; ++i)
                cout << arr[i] << ' ';

            cout << "}\n";
        }
    }

    if (setting == "reverse") {

        if (show) {
            cout << "********************************\n"
                 << "  Changing order to reverse...\n"
                 << "********************************\n";
            sleep_for (1s);
        }

        mySort::quickSort(arr, 0, size - 1);
        std::reverse (arr, arr + size);
        std::swap (arr[0], arr[size / 2]);

        if (show) {
            cout << "\nArray to sort : {";

            for (int i = 0; i < size; ++i)
                cout << arr[i] << ' ';

            cout << "}\n";
        }
    }
}