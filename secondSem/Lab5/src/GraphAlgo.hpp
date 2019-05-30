#ifndef ALGOT_HPP
#define ALGOT_HPP

#include <vector>
#include <stack>
#include <algorithm>
#include <set>

#include "StructureGraph.hpp"
#include "Matrixgraph.hpp"


class algorithm {

    static std::vector <int> dijkstra (const StructureGraph &graph, unsigned point);


public:

    static std::vector <std::vector <unsigned>> components (const StructureGraph &graph);   //task 6

    static std::vector <std::vector <unsigned>> components (const MatrixGraph &graph);

    template <class Pred>
    static void dfs (const MatrixGraph &graph, unsigned from, Pred predicate);  // task 12

    template <class Pred>
    static void dfs (const StructureGraph &graph, unsigned from, Pred predicate);

    template <class Pred>
    static void dfsByCoefficients (const StructureGraph &graph, unsigned from, Pred predicate);

    template <class Pred>
    static void dfsByCoefficients (const MatrixGraph &graph, unsigned from, Pred predicate);

    static std::vector <unsigned> distance (const StructureGraph &graph, unsigned from, unsigned to);  // task 14
    static std::vector <unsigned> distance (const MatrixGraph &graph, unsigned from, unsigned to);

    static bool cycled (const StructureGraph &graph);

    static std::vector <unsigned> topologicalSort (const StructureGraph &graph);  // task 18
    static std::vector <unsigned> topologicalSort (const MatrixGraph &graph);

    static StructureGraph spanningTree (const StructureGraph &graph);       // task 19
    static MatrixGraph spanningTree (const MatrixGraph &graph);

    static MatrixGraph minSpanningTree (const MatrixGraph &graph);      // task 22
    static StructureGraph minSpanningTree (const StructureGraph &graph);

    static unsigned weight (const StructureGraph &graph);

};


template <class Pred>
void algorithm::dfs (const MatrixGraph &graph, unsigned from, Pred predicate) {

    std::stack <unsigned> stack;
    std::vector <bool> used (graph.mMatrix.size(), false);
    used [from] = true;
    stack.push (from);

    while (!stack.empty()) {

        auto cur = stack.top();
        stack.pop();

        for (int i = 0; i < graph.mMatrix[cur].size(); ++i)

            if (graph.mMatrix[cur][i] != 0 && !used[i]) {

                predicate (i);
                stack.push(i);
                used[i] = true;
            }
    }
}


template <class Pred>
void algorithm::dfs (const StructureGraph &graph, unsigned from, Pred predicate) {

    std::stack <unsigned> stack;
    std::vector <bool> used (graph.mList.size(), false);
    used [from] = true;
    stack.push (from);

    while (!stack.empty()) {

        auto cur = stack.top();
        stack.pop();

        for (auto &i : graph.mList[cur])
            if (!used [i.first]) {

                predicate (i);
                stack.push(i.first);
                used [i.first] = true;
            }

    }
}

template <class Pred>
void algorithm::dfsByCoefficients (const StructureGraph &graph, unsigned from, Pred predicate) {

    std::stack <unsigned> stack;
    std::vector <bool> used (graph.mList.size(), false);
    used [from] = true;
    stack.push (from);

    auto temp (graph.mList);

    for (auto &i : temp)
         std::sort (i.begin(), i.end(),
               [] (auto &lhs, auto &rhs) {
                   return lhs.second < rhs.second;
               });

    while (!stack.empty()) {

        auto cur = stack.top();
        stack.pop();

        for (auto &i : temp[cur])
            if (!used [i.first]) {

                predicate (i);
                stack.push(i.first);
                used [i.first] = true;
            }

    }
}

template <class Pred>
void algorithm::dfsByCoefficients (const MatrixGraph &graph, unsigned from, Pred predicate) {

    StructureGraph temp (graph);
    dfsByCoefficients (temp, from, predicate);
}

#endif

