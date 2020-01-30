#include <vector>
#include <algorithm>
#include <functional>

template <class T>
class ArrayTree;

template <class T>
class BinaryTree {      // task 18

    struct BinaryNode {

        T data;
        BinaryNode *left,
                   *right;

    };

    BinaryNode *root;

    friend std::vector <ArrayTree <T>> transformToArray (const BinaryTree <T> &tree);

    friend void transformHelper (const BinaryNode *root, std::vector <T> &arr);

    static void pushToRoot (BinaryNode *&root, const T &data) {

        if (!root) {
            root = new BinaryNode {data};
            return;
        }

        else if (root->data > data)
            pushToRoot (root->left, data);

        else
            pushToRoot (root->right, data);
    }

    static void printWithIndent (BinaryNode *root, size_t tab) {

        if (!root)
            return;

        ++tab;

        printWithIndent (root->left, tab);

        for (size_t i = 0; i < tab; ++i)
            std::cout << "\t";

        std::cout << root->data << '\n';


        printWithIndent (root->right, tab);

        --tab;
    }

    static void deleter (BinaryNode *root) {

        if (!root)
            return;

        deleter (root->left);
        deleter (root->right);

        delete root;
    }

public:

    BinaryTree () = default;

    explicit BinaryTree (const T &data)

            : root (new BinaryNode {data})
    {}

    void push (const T &data) {

       pushToRoot (root, data);
    }

    void print () const {

        printWithIndent (root, 0);
    }

    ~BinaryTree() {

        deleter (root);
    }
};

template <class T>
struct ArrayTree {

    T data;
    size_t right;
    bool left;
};

template <class T>
void transformHelper (const typename BinaryTree <T>::BinaryNode *&root, std::vector <T> &arr) {  // part of task 21

    if (!root)
        return;

    transformHelper (root->left);
    transformHelper (root->right);

    arr.emplace_front (root->data,
                       0,
                       bool (root->left));

    if (root->right)
        arr.front().right = std::find (arr.begin(), arr.end(), root->right->data);
}

template <class T>
std::vector <ArrayTree <T>> transformToArray (const BinaryTree <T> &tree) {         // task 21

    std::vector <T> arr;

    transformHelper (tree.root);

    return arr;
}