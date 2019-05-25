#ifndef LAB5_MATRIXGRAPH_HPP
#define LAB5_MATRIXGRAPH_HPP


#include <vector>

class StructureGraph;

class MatrixGraph {

    using matrix = std::vector <std::vector <int>>;

    matrix mMatrix;
    bool oriented;


    template <class Stream>
    friend Stream& operator<< (Stream &stream, MatrixGraph &graph);

    friend class algorithm;
    friend class StructureGraph;

public:

    explicit MatrixGraph (int n, bool isOriented = false, bool random = false);

    explicit MatrixGraph (const StructureGraph &graph);

    void addEdge (int m, int n, unsigned coeficient);
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
