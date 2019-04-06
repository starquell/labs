#include <iostream>
#include <cstring>
#include <random>
#include "sortAlgorithms.h"

void benchmark(),
     show();

int main (int argc, char **argv) {

    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0) {

//        benchmark();
    }

    else
        show();

    return 0;
}

void show() {

    static std::string stringStorage [] = {"part", "partt",
                                           "aart", "aaart",
                                           "rart", "parrrtition",
                                           "pvrt", "pqer",
                                           "partition", "party",
                                           "aert", "parts",
                                           "partitition", "artition"};

    cout << "Set array size: ";

    size_t size;
    std::cin >> size;

    cout << "Creating random array with size " << size << "...\n";

    std::string arr [size];

    std::mt19937 gen (std::random_device {} ());
    std::uniform_int_distribution <int> rand (0, std::size(stringStorage) - 1);

    for (auto &i: arr)
        i = stringStorage [rand(gen)];

    cout << "\n Created!\n";

    sleep_for(1.2s);

    cout << "Sorting by selection sort...\n";
    sleep_for (1.75s);

    mySort::selectionSort(arr, size, true);

    sleep_for (1s);
    cout << "Sorted array: {";

    for (auto &i : arr)
        cout << i << ' ';

    cout << "}\n"
         << "_________________________________________\n"
         << "Randomizing elements in array...\n";

    for (auto &i: arr)
        i = stringStorage [rand(gen)];

    cout << "Sorting by quick sort...\n";
    sleep_for(1.2s);

    mySort::quickSort(arr, 0, size - 1, true);

    cout << "Sorted array: {";

    for (auto &i : arr)
        cout << i << ' ';

    cout << "}\n"
         << "_________________________________________\n"
         << "Randomizing elements in array...\n";

    for (auto &i: arr)
        i = stringStorage [rand(gen)];

    cout << "Sorting by merge sort...\n";
    sleep_for(1.2s);

    mySort::mergeSort(arr, 0, size - 1, true);

    cout << "Sorted array: {";

    for (auto &i : arr)
        cout << i << ' ';

    cout << "} \n";
}