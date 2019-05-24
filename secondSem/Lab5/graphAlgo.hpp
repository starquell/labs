#ifndef ALGOT_HPP
#define ALGOT_HPP

#include <vector>


class StructureGraph;
class MatrixGraph;

class algorithm {


    static void dfsComponents (int v, std::vector<bool> &used,  std::vector<unsigned> &comp, const StructureGraph &graph);

public:

    static std::vector <std::vector <unsigned>> components (const StructureGraph &graph);

    static std::vector <std::vector <unsigned>> components (const MatrixGraph &graph);

    template <class Pred>
    static void dfs (MatrixGraph &graph, unsigned from, Pred predicate);

    template <class Pred>
    static void dfs (StructureGraph &graph, unsigned from, Pred predicate);

};


#include "GraphAlgo.cpp"

#endif

