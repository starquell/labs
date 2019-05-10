#ifndef LAB5_MATRIXGRAPH_HPP
#define LAB5_MATRIXGRAPH_HPP

#include "structureGraph.hpp"

#include <vector>

class MatrixGraph {

    using matrix = std::vector <std::vector <bool>>;

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



#endif
