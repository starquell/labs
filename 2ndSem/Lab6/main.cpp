#include "src/OrderedVector.hpp"
#include "src/OrderedList.hpp"
#include "src/BST.hpp"
#include "src/AVL.hpp"
#include "src/Point.hpp"
#include "src/TwoThree.hpp"
#include "texttable/TextTable.h"

#include <iostream>
#include <cstring>
#include <chrono>

void benchmarkInit ();

int main (int argc, char **argv) {


    if (argc > 1 && strcmp (argv[1], "--benchmark") == 0)
        benchmarkInit();

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

       const Point toFind = {5, 2, 1};

       twoThreeTree.push (toFind);
       avlTree.push (toFind);
       bst.push (toFind);
       list.push (toFind);
       vec.push (toFind);

       std::cout << std::boolalpha << (bool) twoThreeTree.find (toFind)

                           << '\n' << avlTree.find (toFind)
                           << '\n' << bst.find (toFind)
                           << '\n' << list.find (toFind)
                           << '\n' << vec.find (toFind);



    return 0;
}

time_t benchAlgorithm (std::function <void ()> const &someSort) {

    using namespace std::chrono;

    auto begin = steady_clock::now();
    someSort ();
    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

void benchmarkInit () {

    TextTable t;

    t.add ("            ");
    t.add (" Push 10 elems ");
    t.add (" Find  ");
    t.add (" Delete ");
    t.add (" Iterate by iterator ");
    t.endOfRow();

    const Point findAndDelete = {4, 1.8, 4.43};

    auto benchmark = [&] (auto &dataStructure) mutable {

        auto elapsed = benchAlgorithm ( [&dataStructure] () mutable {

                for (int i = 0; i < 10; ++i)
                dataStructure.push (Point {});
        });

        t.add (" " + std::to_string(elapsed) + " ");

        elapsed = benchAlgorithm ([&dataStructure, &findAndDelete] {

               dataStructure.find (findAndDelete);

        });

        t.add (" " + std::to_string(elapsed) + " ");

        elapsed = benchAlgorithm ([&dataStructure, &findAndDelete] () mutable {

                dataStructure.erase (dataStructure.begin());
        });

        t.add (" " + std::to_string(elapsed) + " ");

        elapsed = benchAlgorithm ([&dataStructure] {

                auto end = dataStructure.end();
                for (auto it = dataStructure.begin(); it != end; ++it);

        });

        t.add (" " + std::to_string(elapsed) + " ");

        t.endOfRow();
    };

    for (size_t size = 400; size < 4000000;  size *= 20) {

        std::cout << "Benchmarking for " << size << " elements...\n";

        OrderedVector <Point> orderedVector (size);
        OrderedList <Point> orderedList (size);
        BinaryTree <Point> bst (size);
        AVLTree <Point> avlTree (size);
        TwoThreeTree twoThreeTree (size);

        orderedVector.push (findAndDelete);
        orderedList.push (findAndDelete);
        bst.push (findAndDelete);
        avlTree.push (findAndDelete);
        twoThreeTree.push (findAndDelete);


        t.add ("Ordered vector, " + std::to_string (size) + " el");
        benchmark (orderedVector);
        t.add ("Ordered list, " + std::to_string (size) + " el");
        benchmark (orderedList);
        t.add ("BST, " + std::to_string (size) + " el");
        benchmark (bst);
        t.add ("AVL Tree, " + std::to_string (size) + " el");
        benchmark (avlTree);
        t.add ("Two-Three Tree, " + std::to_string (size) + " el");
        benchmark (twoThreeTree);
    }

    std::cout << t;
    exit (0);
}