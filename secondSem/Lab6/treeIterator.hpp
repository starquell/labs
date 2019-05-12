#ifndef LAB6_TREEITERATOR_HPP
#define LAB6_TREEITERATOR_HPP

#include "AVLnode.hpp"
#include "BinaryNode.hpp"


template <class Node>
class Iterator {

    size_t cur;
    std::vector <Node*> nodes;

    void fillStack (Node *node)  {

        if (!node)
            return;

        fillStack (node->left);

        nodes.push_back (node);

        fillStack (node->right);
    }

public:

    Iterator (Node *node, bool end = false) :
            cur (0)
    {
        fillStack (node);

        if (end)
            cur = nodes.size();
    }

    Iterator& operator++ () {

        ++cur;
        return *this;
    }

    Iterator& operator-- () {

        --cur;
        return *this;
    }

    Iterator& operator+ (int i) {

        cur += i;
        return *this;
    }

    Iterator& operator- (int i) {

        cur -= i;
        return *this;
    }

    const auto& operator* () {
        return nodes [cur]->data;
    }

    bool operator< (const Iterator &other) {
        return cur < other.cur;
    }

    bool operator!= (const Iterator &other) {
        return cur != other.cur;
    }
};


#endif //LAB6_TREEITERATOR_HPP
