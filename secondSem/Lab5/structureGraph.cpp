#include "structureGraph.hpp"
#include "matrixgraph.hpp"

template<class Stream>
Stream &operator<<(Stream &stream, StructureGraph &graph) {

    for (size_t i = 0; i < graph.mList.size(); ++i) {

        stream << i << " : ";

        for (const auto &j : graph.mList[i])
            stream << j << ' ';
        stream << '\n';
    }

    return stream;
}

StructureGraph::StructureGraph(size_t n, bool isOriented)

        : mList(n),
          oriented (isOriented)
{}

void StructureGraph::addEdge(size_t n, size_t m) {

    mList[n].push_back(m);

    if (!oriented)
        mList[m].push_back(n);
}