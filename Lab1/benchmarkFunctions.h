#include <experimental/filesystem>

time_t vectorTest(TextTable &t, size_t n){

    time_t limit{};
    t.add(" " + std::to_string(n) + " ");

    auto begin = steady_clock::now();
    std::vector <Monster> monsters{n};
    auto end = steady_clock::now();

    time_t elapsed = duration_cast<milliseconds>(end - begin).count();
    limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
        for (auto& j : monsters)
            if (strcmp (j.attackType, Monster::attackTypes[i]) == 0)
                continue;


    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();
    t.add(" " + std::to_string(elapsed) + " ");

    begin = steady_clock::now();

    monsters.resize(n/2);
    monsters.shrink_to_fit();

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    t.add(" " + std::to_string(elapsed) + " ");
    t.endOfRow();

    return limit;
}

time_t TextTest(TextTable &t, size_t n){

    time_t limit = 0;
    t.add(" " + std::to_string(n) + " ");

    auto begin = steady_clock::now();
    std::vector <Monster> monsters{n};

    saveToFile(monsters, "benchmark.txt");
    monsters.clear();

    readFromFile(monsters, "benchmark.txt");

    auto end = steady_clock::now();
    time_t elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 1000)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
       findInFile(i);

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 1000)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");

    std::ofstream benchmark("benchmark.txt", std::ofstream::trunc);

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

    t.add(" " + std::to_string(elapsed) + " ");
    t.endOfRow();

    return limit;
}

time_t BinaryTest(TextTable &t, size_t n){

    time_t limit{};
    t.add(" " + std::to_string(n) + " ");

    auto begin = steady_clock::now();

    std::vector <Monster> monsters{n};

    saveToBinary(monsters, "binarybenchmark.txt");
    monsters.clear();
    readFromBinary(monsters, "binarybenchmark.txt");

    auto end = steady_clock::now();
    time_t elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 1000)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");

    begin = steady_clock::now();

    for (auto i = 1; i < 3; ++i)
        findInBinary(i);

    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 1000)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");

    std::ifstream b("binarybenchmark.txt", std::ios::binary | std::ios::out);
    b.seekg (0, std::ios::end);
    auto size = b.tellg();

    begin = steady_clock::now();
    std::experimental::filesystem::resize_file("binarybenchmark.txt", size/2);
    end = steady_clock::now();
    elapsed = duration_cast<milliseconds>(end - begin).count();

    if (elapsed > 1000)
        limit = elapsed;

    t.add(" " + std::to_string(elapsed) + " ");
    t.endOfRow();

    return limit;
}