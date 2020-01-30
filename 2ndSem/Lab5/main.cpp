#include "src/GraphAlgo.hpp"
#include "src/Matrixgraph.hpp"
#include "src/StructureGraph.hpp"
#include "texttable/TextTable.h"

#include <iostream>
#include <functional>
#include <chrono>
#include <cstring>


void benchmarkInit ();

int main (int argc, char** argv) {

    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0)
        benchmarkInit();

    else {

        /*
         *   Graph creates by constructor with 3 parameters (number of points, bool oriented, bool random) :
         *          example : MatrixGraph (10, false, true);
         *                    StructureGraph (4, true);
         *
         *   All algorithm implemented as for matrix graph, as for structure.
         *   Algorithms can be called from class algorithm as static methods
         *
         *          example :
         *                      StructureGraph graph (8, false, true);
         *                      StructureGraph tree = algorithm::spanningTree (graph);
         *                      std::cout << tree;
         *
         *
         *
         */
    }

    return 0;
}

time_t benchAlgorithm (std::function <void ()> const &someSort) {

    using namespace std::chrono;

    auto begin = steady_clock::now();
    someSort ();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

void benchmarkInit () {

    TextTable t;

    t.add ("            ");
    t.add (" Components ");
    t.add ("  DFS  ");
    t.add (" DFS by coefficients ");
    t.add (" Dijkstra ");
    t.add (" Topological sort ");
    t.add ("Spanning tree");
    t.add (" Minimal spanning tree ");
    t.endOfRow();

    auto benchmark = [&t] (auto &graph) {

            auto elapsed = benchAlgorithm ([&graph] {
                algorithm::components (graph);
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::dfs (graph, 0, [] (auto &i) {});
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::dfsByCoefficients (graph, 0, [] (auto &i) {});
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::distance (graph, 0, 1);
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::topologicalSort (graph);
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::spanningTree (graph);
            });

            t.add (" " + std::to_string(elapsed) + " ");

            elapsed = benchAlgorithm ([&graph] {
                algorithm::minSpanningTree (graph);
            });

            t.add (" " + std::to_string(elapsed) + " ");

            t.endOfRow();
    };

    for (size_t size = 20; size < 20000; size *= 20) {


        std::cout << "Benchmarking for " << size << " elements...\n";

        StructureGraph notOrientedStructure (size, false, true);
        MatrixGraph notOrientedMatrix (size, false, true);
        StructureGraph orientedStructure (size, true, true);
        MatrixGraph orientedMatrix (size, true, true);


        t.add ("Structure, " + std::to_string (size) + " el");
        benchmark (notOrientedStructure);
        t.add ("Matrix, " + std::to_string (size) + " el");
        benchmark (notOrientedMatrix);
        t.add ("Oriented, structure, " + std::to_string (size) + " el");
        benchmark (orientedStructure);
        t.add ("Oriented, matrix, " + std::to_string (size) + " el");
        benchmark (orientedMatrix);
    }

    std::cout << t;
}