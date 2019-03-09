#include "Arraybased.h"
#include "Vectorbased.h"
#include "Listbased.h"
#include "texttable/TextTable.h"
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std::chrono_literals;
using namespace std::chrono;
using std::cout;
using std::cin;
using std::this_thread::sleep_for;

struct Point{
    double x, y, z;
};

template <class T>
void interactive(T queue);
template <class T>
void presentation(T q);
template <class T>
void benchmark(T &q);

void selector(),
     benchmarkSet();

int main(int argc, char** argv) {

    if (argc > 1) {
        std::string parameter(argv[1]);

        if (parameter == "--benchmark") {
            benchmarkSet();
            return 0;
        }

        if (parameter == "--presentation") {

            cout << "Creating queue by array...\n";
            sleep_for(0.5s);
            presentation(Arraybased <Point, 5> {});

            cout << "Creating queue by vector...\n";
            sleep_for(0.5s);
            presentation(Vectorbased <Point> {});

            cout << "Creating queue by list...\n";
            sleep_for(0.5s);
            presentation(Listbased <Point> {});
            return 0;
        }
    }

    selector();

    return 0;
}

void selector(){

    cout << " Choose type of queue:\n"
              << " 1.Arraybased\n"
              << " 2.Vectorbased\n"
              << " 3.Listbased\n";
    int choice;
    do
    cin >> choice;
    while (choice < 1 || choice > 3);

    switch (choice) {
        case 1:
            interactive (Arraybased<Point, 100> {});
            break;
        case 2:
            interactive(Vectorbased<Point> {});
            break;
        case 3:
            interactive(Listbased<Point> {});

        default: break;
    }
    selector();
}

template <class T>
void interactive(T queue){

    cout << "\n 1. Add point to queue\n"
         << " 2. Delete point from queue\n"
         << " 3. Show top point\n"
         << " 4. Return to previous menu\n";

    int choice;
    do
        cin >> choice;
    while (choice < 1 || choice > 4);

    switch (choice) {
        case 1: {
            std::cout << "Enter point's coordinates in this format: x y z";
            Point p;
            cin >> p.x >> p.y >> p.z;
            queue.push(p);
            cout << "* Done *\n";
            break;
        }
        case 2: {
            queue.pop();
            cout << "* Done *\n";
            break;
        }
        case 3: {
            const auto p = queue.getFront();
            cout << "\n(" << p.x << ", " << p.y << ", " << p.z << ")\n";
            break;
        }
        default:  return;
    }
    interactive(queue);
};

template <class T>
void presentation(T q){

    cout << "Pushing point (3, 6, 2) to queue...\n";
    q.push({3, 6, 2});
    sleep_for(1s);

    cout << "Pushing point (9, 3, 1) to queue...\n";
    q.push({9, 3, 1});
    sleep_for(1s);

    cout << "Pushing point (2, 3, 11) to queue...\n";
    q.push({2, 3, 11});
    sleep_for(1s);

    cout << "\nTop point in queue: (" << q.getFront().x << ", "
         << q.getFront().y << ", " << q.getFront().x << ").\n";

    sleep_for(1.2s);

    cout << "Our queue: " << '(' << q.getFront().x << ", " << q.getFront().y << ", " << q.getFront().z << ")  ";
    q.pop();
    cout << '(' << q.getFront().x << ", " << q.getFront().y << ", " << q.getFront().z << ")  ";
    q.pop();
    cout << '(' << q.getFront().x << ", " << q.getFront().y << ", " << q.getFront().z << ")\n"
         << "               ^\n"
         << "        First in queue\n\n\n";
}

void benchmarkSet(){

    srand(time(nullptr));

    {
        cout << "Benchmarking in array...\n";

        auto begin = steady_clock::now();
        Arraybased<Point, 200000> a;
        auto end = steady_clock::now();

        time_t elapsed = duration_cast<milliseconds>(end - begin).count();
        cout << "Queue created in " << elapsed << " ms.\n";

        benchmark(a);

    }
    {
        cout << "Benchmarking in vector...\n";

        auto begin = steady_clock::now();
        Vectorbased<Point> v;
        auto end = steady_clock::now();

        time_t elapsed = duration_cast<milliseconds>(end - begin).count();
        cout << "Queue created in " << elapsed << " ms.\n";

        benchmark(v);
    }

    {
        cout << "Benchmarking in list...\n";

        auto begin = steady_clock::now();
        Listbased <Point> l;
        auto end = steady_clock::now();

        time_t elapsed = duration_cast<milliseconds>(end - begin).count();
        cout << "Queue created in " << elapsed << " ms.\n";

        benchmark(l);
    }
}

template <class T>
void benchmark (T &queue){

    TextTable t;

    for (size_t elem = 5;  elem < 100000; elem *= 5) {

        t.add(" " + std::to_string(elem) + " ");    // adding something to table

        auto begin = steady_clock::now();
        for (int i = 0; i < elem; ++i)
            queue.push({(rand() % 10) * 0.1, (rand() % 10) * 0.1, (rand() % 10) * 0.1});

        auto end = steady_clock::now();
        time_t elapsed = duration_cast<milliseconds>(end - begin).count();
        t.add(" " + std::to_string(elapsed) + " ");

        begin = steady_clock::now();
        while (!queue.isEmpty())
            queue.pop();

        end = steady_clock::now();
        elapsed = duration_cast<milliseconds>(end - begin).count();
        t.add(" " + std::to_string(elapsed) + " ");

        begin = steady_clock::now();
        if (queue.isEmpty() || !queue.isEmpty())
            end = steady_clock::now();

        elapsed = duration_cast<milliseconds>(end - begin).count();
        t.add(" " + std::to_string(elapsed) + " ");
        t.endOfRow();
    }

    cout << t << '\n';
}