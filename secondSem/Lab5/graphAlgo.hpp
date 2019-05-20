#ifndef ALGOT_HPP
#define ALGOT_HPP

#include "structureGraph.hpp"

#include <vector>



class algorithm {


    static void dfs (int v, std::vector<bool> &used,  std::vector<int> &comp) {

        used [v] = true;
        comp.push_back (v);

        for (auto &i : mStructure [v]) {
            int to = i.first;
            if (!used[to])
                dfs (to, used, comp);
        }
    }

public:

    static std::vector <std::vector <unsigned>> components (const StructureGraph &graph) {

        const auto size = graph.mList.size();

        std::vector <bool> used(size, false);
        std::vector <unsigned> comp;
        std::vector <std::vector <unsigned>> components;

        for (int i = 0; i < size; ++i)

            if (!used[i]) {

                comp.clear();
                dfs (i, used, comp);
                components.push_back (comp);
            }
    }

};

#endif

