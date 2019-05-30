#ifndef LAB6_BST_HPP
#define LAB6_BST_HPP

#include "TreeIterator.hpp"

#include <stack>
#include <random>

template <class T>
class BinaryTree {

    using Node = BinaryNode <T>;
    Node *root;

    static Node *pushToRoot (Node *root, const T &data) {

        if (!root)

            return new Node {data};


        else if (root->data > data)
            root->left = pushToRoot (root->left, data);

        else
           root->right = pushToRoot (root->right, data);

        return root;
    }


    static void deleter (Node *root) {

        if (!root)
            return;

        deleter (root->left);
        deleter (root->right);

        delete root;
    }

    static Node* eraseHelper (Node *node, const T& data) {

        if (!node)
            return node;

        if (data == node->data) {

            if (node->left && node->right) {

                Node *minNode = getHighestNodeFromRight (node->right);

                node->data = minNode->data;
                node->right = eraseHelper (node->right, minNode->data);
            }
            else if (!node->left)
                return node->right;

            else
                return node->left;

        }
        else if (data > node->data)
            node->right = eraseHelper (node->right, data);
        else
            node->left = eraseHelper (node->left, data);

        return node;
    }

    static Node* getHighestNodeFromRight (Node *node) {

        if (!node->left)
            return node;

        else {
            Node *n = getHighestNodeFromRight (node->left);
            return n;
        }
    }


public:

    explicit BinaryTree (size_t n = 0)
            : root (nullptr)

    {
        if (std::is_same_v <T, Point>)

            for (size_t i = 0; i < n; ++i) {

                push (Point {});
            }
    }

    bool empty() {

        return root;
    }

    void push (const T &data) {

        root = pushToRoot (root, data);
    }

    void erase (Iterator <Node> it) {

        auto data = *it;
        root = eraseHelper (root, data);
    }

    Iterator <Node> begin () {

        return root;
    }

    Iterator <Node> end () {

        return {root, true};
    }

    const T& operator[] (size_t n) {

        return *(begin() + n);
    }


    ~BinaryTree () {

        deleter (root);
    }
};
#endif //LAB6_BST_HPP
