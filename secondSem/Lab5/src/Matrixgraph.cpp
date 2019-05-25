#include "Matrixgraph.hpp"
#include "StructureGraph.hpp"

#include <random>

void MatrixGraph::addEdge (int m, int n, unsigned coeficient) {

    mMatrix [m][n] = coeficient;
    if (!oriented)
        mMatrix [n][m] = coeficient;
}

MatrixGraph::MatrixGraph (const StructureGraph &graph)

        : mMatrix (graph.mList.size(), std::vector <int> (graph.mList.size(), 0)),
          oriented (graph.oriented)

{
    auto size = graph.mList.size();

    for (int i = 0; i < size; ++i)

        for (auto &j : graph.mList [i])
             mMatrix[i][j.first] = j.second;
}

MatrixGraph::MatrixGraph (int n, bool isOriented, bool random)

        : mMatrix (n, std::vector <int> (n)),
          oriented (isOriented)
{

    if (random) {

        static std::vector coefStorage = {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5
        };

        static std::mt19937 gen (std::random_device{}());
        static std::uniform_int_distribution <int> dis (0, coefStorage.size() - 1);

        for (int i = 0; i < mMatrix.size(); ++i)
            for (int j = 0; j < mMatrix[i].size(); ++j) {
                if (oriented && mMatrix[j][i] == 0)
                    mMatrix[i][j] = coefStorage [dis(gen)];
                else if (!oriented)
                    mMatrix[j][i] = mMatrix[i][j] = coefStorage [dis(gen)];
                if (i == j)
                    mMatrix[i][j] = 0;
            }
    }
}


