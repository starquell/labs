#include "GraphAlgo.hpp"
#include "StructureGraph.hpp"
#include "Matrixgraph.hpp"

#include <random>

StructureGraph::StructureGraph (size_t n, bool isOriented, bool random)

        : mList (random ? StructureGraph (MatrixGraph {int (n), isOriented, random}).mList : list (n)),
          oriented (isOriented)
{}

StructureGraph::StructureGraph (const MatrixGraph &graph)

        : mList (graph.mMatrix.size()),
          oriented (graph.oriented)

{
    auto size = graph.mMatrix.size();

    for (size_t i = 0; i < size; ++i)

        for (size_t j = 0; j < size; ++j)

            if (graph.mMatrix[i][j] != 0)
                mList[i].emplace_back (j, graph.mMatrix[i][j]);
}


void StructureGraph::addEdge(size_t n, size_t m, unsigned coeficient) {

    mList[n].emplace_back(m, coeficient);

    if (!oriented)
        mList[m].emplace_back(n, coeficient);
}