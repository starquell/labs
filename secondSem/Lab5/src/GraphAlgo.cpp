#include "GraphAlgo.hpp"
#include "StructureGraph.hpp"
#include "Matrixgraph.hpp"


#include <stack>
#include <limits>
#include <iostream>
#include <functional>

std::vector <std::vector <unsigned>> algorithm::components(const StructureGraph &graph) {

    const auto size = graph.mList.size();

    std::vector <bool> used(size, false);
    std::vector <unsigned> comp;
    std::vector <std::vector <unsigned>> components;

    std::function <void (int)> dfs = [&] (int v) {

        used [v] = true;
        comp.push_back(v);


        for (auto &i : graph.mList [v]) {

            unsigned to = i.first;
            if (!used[to])
                dfs (to);
        }
    };

    for (int i = 0; i < size; ++i)

        if (!used[i]) {

            comp.clear();
            dfs (i);
            components.push_back (comp);
        }

    return components;
}

std::vector <std::vector <unsigned>> algorithm::components (const MatrixGraph &graph) {

    StructureGraph temp (graph);
    return components (temp);
}

std::vector <int> algorithm::dijkstra (const StructureGraph &graph, unsigned point) {

    const int max = std::numeric_limits <int>::max();
    const auto size = graph.mList.size();

    std::vector <bool> u (size);
    std::vector <int> d (size, max),
                      paths (size);

    d[point] = 0;

    for (int i = 0; i < size; ++i) {
        int v = -1;

        for (int j = 0; j < size; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (d[v] == max)
            break;

        u[v] = true;

        for (auto &j : graph.mList[v]) {

            auto [to, len] = j;

            if (d[v] + len < d[to]) {

                d[to] = d[v] + len;
                paths [to] = v;
            }
        }
    }

    return paths;
}

std::vector <unsigned> algorithm::distance (const StructureGraph &graph, unsigned from, unsigned to) {

    auto allpath = dijkstra (graph, to);

    std::vector <unsigned> path;

    while (from != to) {

        path.push_back (from);
        from = allpath[from];
    }

    path.push_back (from);

    return path;
}

std::vector <unsigned> algorithm::distance (const MatrixGraph &graph, unsigned from, unsigned to) {

    StructureGraph temp (graph);
    return distance (temp, from, to);
}


bool algorithm::cycled (const StructureGraph &graph) {

    const auto size = graph.mList.size();

    std::vector <char> color (size, 0);
    bool cycle = false;

    std::function <bool (unsigned)> dfs = [&] (unsigned v) {

        color [v] = 1;

        for (auto &i : graph.mList[v]) {

            int to = i.first;

            if (color [to] == 0) {

                if (dfs (to))
                    return true;
            }

            else if (color [to] == 1) {

                cycle = true;
                return true;
            }
        }

        color [v] = 2;
        return false;
    };

    for (int i = 0; i < size; ++i)
        if (dfs (i))
            break;

    return cycle;
}

std::vector <unsigned> algorithm::topologicalSort (const StructureGraph &graph) {

    if (cycled (graph))
        return {};

    const auto size = graph.mList.size();

    std::vector <bool> used (size, false);
    std::vector <unsigned> order;

    std::function <void (int)> dfs = [&] (int v) {

        used [v] = true;

        for (auto &i : graph.mList[v]) {

            int to = i.first;

            if (!used[to])
                dfs (to);
        }
        order.push_back (v);
    };

    for (int i = 0; i < size; ++i)
        if (!used[i])
            dfs (i);

    reverse (order.begin(), order.end());
    return order;
}

std::vector <unsigned> algorithm::topologicalSort (const MatrixGraph &graph) {

    StructureGraph temp (graph);
    return topologicalSort (temp);
}

StructureGraph algorithm::spanningTree (const StructureGraph &graph) {

    std::vector <unsigned> path = {0};

    dfs (graph, 0, [&path] (const auto &i) {
        path.push_back (i.first);
    });


    StructureGraph spanning (path.size());

    for (int i = 1; i < path.size(); ++i) {

        int j = i - 1;
        auto found = graph.mList[path[i]].end();

        for (; found == graph.mList[path[i]].end() && j >= 0; --j)
            found = std::find_if (graph.mList[path[i]].begin(), graph.mList[path[i]].end(), [&path, j](auto &pair) {
                return pair.first == path [j];
            });

        ++j;

            spanning.addEdge (path[i], path [j], found->second);
    }

    return spanning;
}

MatrixGraph algorithm::spanningTree (const MatrixGraph &graph) {

    StructureGraph temp (graph);
    auto spanning = spanningTree (temp);
    return MatrixGraph (spanning);
}

MatrixGraph algorithm::minSpanningTree (const MatrixGraph &graph) {

    const auto size = graph.mMatrix.size();
    const unsigned max = std::numeric_limits <unsigned>::max();

    std::vector <bool> used (size);

    std::vector <int> minEdge (size, max), selEdge (size, -1);

    minEdge [0] = 0;

    for (int i = 0; i < size; ++i) {

        int v = -1;

        for (int j = 0; j < size; ++j)
            if (!used[j] && (v == -1 || minEdge[j] < minEdge[v]))
                v = j;

        if (minEdge[v] == max)
            return MatrixGraph {int (size), graph.oriented};

        used[v] = true;

        for (int to = 0; to < size; ++to)
            if (graph.mMatrix[v][to] < minEdge[to]) {

                minEdge [to] = graph.mMatrix[v][to];
                selEdge [to] = v;
            }
    }

    MatrixGraph spanning (size);

    for (int i = 0; i < selEdge.size(); ++i)
        spanning.addEdge (i, selEdge[i], minEdge[i]);

    return spanning;
}

StructureGraph algorithm::minSpanningTree (const StructureGraph &graph) {

    MatrixGraph temp (graph);
    auto spanning = minSpanningTree (temp);
    return StructureGraph (spanning);
}

unsigned algorithm::weight (const StructureGraph &graph) {

    unsigned sum {};

    for (auto &i: graph.mList)
        for (auto &j : i)
            sum += j.second;

    return graph.oriented ? sum : sum / 2;
}

