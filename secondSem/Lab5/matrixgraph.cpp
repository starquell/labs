#include "matrixgraph.hpp"
#include "structureGraph.hpp"

StructureGraph::StructureGraph(const MatrixGraph &graph)

        : mList (graph.mMatrix.size()),
          oriented (graph.oriented)

{
    auto size = graph.mMatrix.size();

    for (size_t i = 0; i < size; ++i)

        for (size_t j = 0; j < size; ++j)

            if (graph.mMatrix[i][j])
                mList[i].push_back(j);
}


template <class Stream>
Stream& operator<< (Stream &stream, MatrixGraph &graph) {

    for (const auto &i : graph.mMatrix) {

        for (const auto &j : i)
            stream << j << ' ';
        stream << '\n';
    }
    return stream;
}

void MatrixGraph::addEdge(int m, int n) {

    mMatrix [m][n] = true;
    if (!oriented)
        mMatrix [n][m] = true;
}

explicit MatrixGraph::MatrixGraph (const StructureGraph &graph)

        : mMatrix (graph.mList.size();, std::vector <bool> (graph.mList.size();, false)),
          oriented (graph.oriented)

{
    auto size = graph.mList.size();

    for (int i = 0; i < size; ++i)

        for (auto &j : i)
            mMatrix[i][j] = true;
}