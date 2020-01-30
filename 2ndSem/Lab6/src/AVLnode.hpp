#ifndef LAB6_AVLNODE_HPP
#define LAB6_AVLNODE_HPP

template <class T>
struct AVLNode {

    T data;
    int height;

    AVLNode* left;
    AVLNode* right;

    explicit AVLNode (const T& _key)

            : data (_key),
              height (1),
              left (nullptr),
              right (nullptr)
    {}

    void fixHeight () {

        int hl = left? left->height: 0;
        int hr = right? right->height : 0;

        height = ((hl > hr)? hl : hr) + 1;
    }


    int balanceFactor () {

        return (left ? left->height : 0) - (right ? right->height: 0);
    }


};

#endif //LAB6_AVLNODE_HPP
