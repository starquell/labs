#ifndef GRAPHALGO_CPP
#define GRAPHALGO_CPP

#include "structureGraph.hpp"
#include "matrixgraph.hpp"

#include <stack>

void algorithm::dfsComponents (int v, std::vector<bool> &used, std::vector<unsigned> &comp, const StructureGraph &graph) {

        used [v] = true;
        comp.push_back(v);


    for (auto &i : graph.mList [v]) {

        unsigned to = i.first;
        if (!used[to])
            dfsComponents (to, used, comp, graph);
    }
}

std::vector <std::vector <unsigned>> algorithm::components(const StructureGraph &graph) {

    const auto size = graph.mList.size();

    std::vector <bool> used(size, false);
    std::vector <unsigned> comp;
    std::vector <std::vector <unsigned>> components;

    for (int i = 0; i < size; ++i)

        if (!used[i]) {

            comp.clear();
            dfsComponents (i, used, comp, graph);
            components.push_back (comp);
        }

    return components;
}

std::vector <std::vector <unsigned>> algorithm::components (const MatrixGraph &graph) {

    StructureGraph temp (graph);
    return components (temp);
}



template <class Pred>
void algorithm::dfs (MatrixGraph &graph, unsigned from, Pred predicate) {

    std::stack <unsigned> stack;
    std::vector <bool> used (graph.mMatrix.size(), false);
    used [from] = true;
    stack.push (from);

    while (!stack.empty()) {

        auto cur = stack.top();
        stack.pop();

        for (int i = 0; i < graph.mMatrix[cur].size(); ++i)

            if (graph.mMatrix[cur][i] != 0 && !used[i]) {

                predicate(graph.mMatrix[cur][i]);
                stack.push(i);
                used[i] = true;
            }
    }
}


template <class Pred>
void algorithm::dfs (StructureGraph &graph, unsigned from, Pred predicate) {

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

#endif