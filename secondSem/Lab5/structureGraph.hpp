#ifndef LAB5_STRUCTUREGRAPH_HPP
#define LAB5_STRUCTUREGRAPH_HPP

#include "graphAlgo.hpp"
#include <vector>
#include <utility>

class MatrixGraph;

class StructureGraph {


    using list = std::vector <std::vector <std::pair <unsigned, unsigned>>>;  // pair <Point, Cofficient>

    list mList;
    bool oriented;


    template <class Stream>
    friend Stream& operator<< (Stream &stream, StructureGraph &graph);
    friend class algorithm;
    friend class MatrixGraph;

public:

    explicit StructureGraph (size_t n, bool isOriented = false, bool random = false);

    explicit StructureGraph (const MatrixGraph &graph);

    void addEdge (size_t n, size_t m, unsigned coeficient = 0);
};

template <class Stream>
Stream& operator<< (Stream &stream, StructureGraph &graph) {

    stream << "{Neighbour, Coefficient}\n";

    for (size_t i = 0; i < graph.mList.size(); ++i) {

        stream << i << " : ";

        for (const auto &j : graph.mList[i])
            stream << '{' << j.first << ", " << j.second << "}  ";
        stream << '\n';
    }

    return stream;
}


#endif //LAB5_STRUCTUREGRAPH_HPP