#ifndef LAB5_STRUCTUREGRAPH_HPP
#define LAB5_STRUCTUREGRAPH_HPP

#include <vector>

class MatrixGraph;

class StructureGraph {

    using list = std::vector <std::vector <unsigned>>;

    list mList;
    bool oriented;


    template <class Stream>
    friend Stream& operator<< (Stream &stream, StructureGraph &graph);

    friend class MatrixGraph;

public:

    explicit StructureGraph (size_t n, bool isOriented = false);

    explicit StructureGraph (const MatrixGraph &graph);

    void addEdge (size_t n, size_t m);
};



#endif //LAB5_STRUCTUREGRAPH_HPP