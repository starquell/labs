#ifndef LAB6_TREEITERATOR_HPP
#define LAB6_TREEITERATOR_HPP

#include "AVLnode.hpp"
#include "BinaryNode.hpp"


template <class Node>
class Iterator {

protected:

    size_t cur;
    std::vector <Node*> nodes;

    virtual void fillStack (Node *node)  {

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

    size_t operator- (const Iterator& other) {

        return cur - other.cur;
    }

    size_t operator+ (const Iterator& other) {

        return cur + other.cur > nodes.size() ? 0 : cur + other.cur;
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
