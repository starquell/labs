#ifndef LAB5_MATRIXGRAPH_HPP
#define LAB5_MATRIXGRAPH_HPP


#include "structureGraph.hpp"
#include <vector>


class MatrixGraph {

    using matrix = std::vector <std::vector <int>>;

    matrix mMatrix;
    bool oriented;


    template <class Stream>
    friend Stream& operator<< (Stream &stream, MatrixGraph &graph);

    friend class StructureGraph;

public:

    explicit MatrixGraph (int n, bool isOriented = false);

    explicit MatrixGraph (const StructureGraph &graph);

    void addEdge (int m, int n);
};

template <class Stream>
Stream& operator<< (Stream &stream, MatrixGraph &graph) {

    for (const auto &i : graph.mMatrix) {

        for (const auto &j : i)
            stream << j << ' ';
        stream << '\n';
    }
    return stream;
}


#endif
