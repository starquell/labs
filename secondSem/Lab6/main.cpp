#include "src/OrderedVector.hpp"
#include "src/OrderedList.hpp"
#include "src/BST.hpp"
#include "src/AVL.hpp"
#include "src/Point.hpp"
#include "src/TwoThree.hpp"

#include <iostream>


int main() {




    OrderedVector <Point> vec (15);

    std::cout << "\n\n\nVec : \n\n";
    for (auto &i : vec)
        std::cout << i;


    OrderedList <Point> list (15);

    std::cout << "\n\n\nList : \n\n";
    for (auto &i : list)
        std::cout << i;

    BinaryTree <Point> bst (15);

    std::cout << "\n\n\nBST : \n\n";
    for (auto &i : bst)
        std::cout << i;

    AVLTree <Point> avlTree (15);

    std::cout << "\n\n\nAVL Tree : \n\n";

    for (auto &i : avlTree)
        std::cout << i;

    TwoThreeTree twoThreeTree (15);

    std::cout << "\n\n\nTwo-Three Tree : \n\n";

    for (auto &i : twoThreeTree)
        std::cout << i << '\n';

    return 0;
}