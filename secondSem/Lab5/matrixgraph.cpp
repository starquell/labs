#include "matrixgraph.hpp"
#include "structureGraph.hpp"


void MatrixGraph::addEdge (int m, int n) {

    mMatrix [m][n] = true;
    if (!oriented)
        mMatrix [n][m] = true;
}

MatrixGraph::MatrixGraph (const StructureGraph &graph)

        : mMatrix (graph.mList.size(), std::vector <int> (graph.mList.size(), false)),
          oriented (graph.oriented)

{
    auto size = graph.mList.size();

    for (int i = 0; i < size; ++i)

        for (auto &j : graph.mList [i])
             mMatrix[i][j] = true;
}

MatrixGraph::MatrixGraph (int n, bool isOriented)

        : mMatrix (n, std::vector <int> (n)),
          oriented (isOriented)
{}


