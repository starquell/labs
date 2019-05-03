#include <fstream>
#include <cassert>

#include "filesystem.h"
#include "binarytree.h"
#include "interactive.h"


int main (int argc, char **argv) {

    bool show {};
    std::ifstream showfile ("../show.txt");
    assert (showfile.is_open());

    if (argc > 1 && std::string (argv [1]) == "--show") {

        cin.rdbuf(showfile.rdbuf());
        show = true;
    }

        int choice;

        cout << "Enter 1 to Binary tree with integers mode,"
             << "else - Filesystem mode  ";
        cin >> choice;

        if (choice == 1) {

            BinaryTree<int> btree{};
            while (true)
                binaryInteractive (btree);
        }

        else {
            Filesystem fs;
            while (true)
                interactive(fs, show);
        }

    return 0;
}