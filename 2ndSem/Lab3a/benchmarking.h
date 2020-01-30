#include <chrono>
#include <thread>
#include <functional>
#include "texttable/TextTable.h"

template <class T>
void arraySet (T *arr, size_t size, bool show = false, std::string_view setting = "random");

time_t benchAlgorithm (std::function <void ()> const &someSort) {

    using namespace std::chrono;

    auto begin = steady_clock::now();
    someSort ();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

template <class T>
void benchmark (TextTable &t, T *arr, int size, std::string_view setting) {

    t.add (" " + std::to_string(size) + " " + "(" + setting.data() + ")");

    arraySet (arr, size, false, setting);

    cout << "Benchmark in selection sort...\n";

    auto elapsed = benchAlgorithm ([arr, size] {
        mySort::selectionSort (arr, 0, size);
        });

    t.add (" " + std::to_string(elapsed) + " ");

    arraySet (arr, size, false, setting);

    cout << "Benchmark in quick sort...\n";

    elapsed = benchAlgorithm ([arr, size] {
        mySort::quickSort (arr, 0, size);
    });

    t.add (" " + std::to_string(elapsed) + " ");

    arraySet (arr, size, false, setting);

    cout << "Benchmark in merge sort...\n";

    elapsed = benchAlgorithm ([arr, size] {
        mySort::mergeSort (arr, 0, size - 1);
    });

    t.add (" "  + std::to_string(elapsed) + " " );

    arraySet (arr, size, false, setting);

    cout << "Benchmark in combined sort...\n";

    elapsed = benchAlgorithm ([arr, size] {
        mySort::combinedSort (arr, size);
    });

    t.add (" " + std::to_string(elapsed) + " ");

    arraySet (arr, size, false, setting);

    cout << "Benchmark in sort in <algorithm> ...\n";

    elapsed = benchAlgorithm ([arr, size] {
        std::sort (arr, arr + size);
        std::sort (arr, arr + size, comp);
    });

    t.add (" " + std::to_string(elapsed) + " ");
    t.endOfRow();
}

void benchmarkSet (){

    std::string_view settings [] = {"random",
                                    "mostly-sorted",
                                    "reverse"};
    TextTable t;

    for (auto &i : settings) {

        cout << "Creating " << i << " array with size 20...\n";

        std::string arr0 [20];

        benchmark(t, arr0, std::size(arr0), i);

        cout << "Creating " << i << " array with size 1500...\n";

        std::string arr[1500];

        benchmark(t, arr, std::size(arr), i);

        cout << "Creating " << i << " array with size 15000...\n";

        std::string arr1[15000];

        benchmark(t, arr1, std::size(arr1), i);
    }

    cout << '\n' << t;
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

        if (show)

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