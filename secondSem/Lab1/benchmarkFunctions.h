#include <experimental/filesystem>
#include <algorithm>
#include "sort.h"

time_t benchAlgorithm (std::function <void ()> const &someSort) {

    using namespace std::chrono;

    auto begin = steady_clock::now();
    someSort ();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

void benchSort () {

    TextTable t ('-', '|', '+', 's');

    cout << "\n*****************************\n\n"
         << "  Benchmarking sort algorithms...\n";

    for (size_t i = 50; i < 10000000; i *= 50) {

        std::vector <Monster> testMonsters (i);

        auto seed = system_clock::now().time_since_epoch().count();
        std::default_random_engine random (seed);

        t.add (" " + std::to_string (i) + " ");

        auto elapsed = benchAlgorithm ([&testMonsters] () mutable {
            countingSort (testMonsters);
        } );

        t.add(" " + std::to_string (elapsed) + " ms ");

        std::shuffle (testMonsters.begin(), testMonsters.end(), random);

        elapsed = benchAlgorithm ([&testMonsters] () mutable {
            radixSort (testMonsters);
        } );

        t.add (" " + std::to_string (elapsed) + " ms ");

        std::shuffle (testMonsters.begin(), testMonsters.end(), random);

        elapsed = benchAlgorithm ([&testMonsters] () mutable {

            std::stable_sort (testMonsters.begin(), testMonsters.end(),
                    [] (const Monster &lhs, const Monster &rhs) {
                        return lhs.hp < rhs.hp;
            });
        } );

        t.add (" " + std::to_string (elapsed) + " ms ");

        std::shuffle (testMonsters.begin(), testMonsters.end(), random);

        elapsed = benchAlgorithm ([&testMonsters] () mutable {
            std::stable_sort (testMonsters.begin(), testMonsters.end(),

                    [] (const Monster &lhs, const Monster &rhs) {
                if (strcmp (lhs.attackType, rhs.attackType) != 0)
                    return strcmp (lhs.attackType, rhs.attackType) < 0;
                else
                    return lhs.hp < rhs.hp;
            });
        });

        t.add (" " + std::to_string (elapsed) + " ms ");
        t.endOfRow();
    }

    cout << t;

    exit(0);
}

time_t vectorTest(TextTable &t, size_t n){

    time_t limit{};
    t.add(" " + std::to_string(n) + " ");
    std::vector <Monster> base{n};

    auto begin = steady_clock::now();
    std::vector <Monster> monsters(base);       //benchmarking speed of writing to vector
    auto end = steady_clock::now();

    time_t elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed >= 10)
    limit = elapsed;

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
        for (auto& j : monsters)
            if (strcmp (j.attackType, Monster::attackTypes[i]) == 0)        //finding be attack type
                continue;


    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed >= 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");

    begin = steady_clock::now();

    monsters.resize(n/2);               //deleting half of elements
    monsters.shrink_to_fit();

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    t.add(" " + std::to_string(elapsed) + " ms ");
    t.endOfRow();

    if (elapsed > 10)
        limit = elapsed;

    return limit;
}

time_t TextTest(TextTable &t, size_t n){

    time_t limit = 0;
    t.add(" " + std::to_string(n) + " ");

    std::vector <Monster> monsters{n};

    auto begin = steady_clock::now();

    saveToFile(monsters, "databases/benchmark.txt");
    monsters.clear();                            //benchmarking speed of writing and reading from file

    readFromFile(monsters, "databases/benchmark.txt");

    auto end = steady_clock::now();
    time_t elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
       findInFile(i);

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");

    std::ofstream benchmark("databases/benchmark.txt", std::ofstream::trunc);     //reseting file to write half of elements

    begin = steady_clock::now();

    for (size_t i = 0; i < monsters.size()/2; ++i) {

        benchmark << monsters[i].name << ' ';
        benchmark << monsters[i].hp << ' ';
        benchmark << monsters[i].ap << ' ';
        benchmark << monsters[i].attackChance << ' ';
        benchmark << monsters[i].timeInSec << ' ';
        benchmark << monsters[i].ID << ' ';
        benchmark << monsters[i].attackType << '\n';
    }

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");
    t.endOfRow();

    return limit;
}

time_t BinaryTest(TextTable &t, size_t n){

    time_t limit{};
    t.add(" " + std::to_string(n) + " ");

    std::vector <Monster> monsters{n};

    auto begin = steady_clock::now();

    saveToBinary(monsters, "databases/binarybenchmark.txt");
    monsters.clear();
    readFromBinary(monsters, "databases/binarybenchmark.txt");

    auto end = steady_clock::now();
    time_t elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
        findInBinary(i);

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");

    std::ifstream b("databases/binarybenchmark.txt", std::ios::binary | std::ios::out);
    b.seekg (0, std::ios::end);
    auto size = b.tellg();

    begin = steady_clock::now();
    std::experimental::filesystem::resize_file("databases/binarybenchmark.txt", size/2);      //removing half
    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 10)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ms ");
    t.endOfRow();

    return limit;
}