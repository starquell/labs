#ifndef LAB6_AVL_HPP
#define LAB6_AVL_HPP

#include "Point.hpp"

#include <iostream>
#include <functional>

template <class T>
class AVLTree {

    using Node = AVLNode <T>;

    Node *root;

    static bool findHelper (Node* root, const T& value) {

        if (!root)
            return false;

        if (root->data > value)
            return findHelper (root->left, value);

        else if (root->data < value)
            return findHelper (root->right, value);

        else
            return true;
    }

    static void deleter (Node *root) {

        if (!root)
            return;

        deleter (root->left);
        deleter (root->right);

        delete root;
    }

    static Node* leftRotate (Node *node) {

        auto temp = node->right;
        node->right = node->right->left;
        temp->left = node;

        node->fixHeight();
        temp->fixHeight();

        return temp;
    }

    static Node* rightRotate (Node *node) {

        auto temp = node->left;
        node->left = node->left->right;
        temp->right = node;

        node->fixHeight();
        temp->fixHeight();

        return temp;
    }

    static Node* balance (Node* root) {

      root->fixHeight();
      auto balanceFactor = root->balanceFactor();

            if (balanceFactor > 1 && root->left->balanceFactor() >= 0)  // left - left
                root = rightRotate (root);

            else if (balanceFactor > 1) {  // left - right
                root->left = leftRotate (root->left);
                root = rightRotate (root);
            }

            else if (balanceFactor < -1 && root->right->balanceFactor() <= 0)  // right - right
                root = leftRotate (root);

            else if (balanceFactor < -1) {  // right - left
                root->right = rightRotate (root->right);
                root = leftRotate (root);
            }

        return root;
    }

    static Node* eraseHelper (Node *node, const T& data, std::vector <Node*> &path) {

        if (!node)
            return node;

        if (data == node->data) {

            if (node->left && node->right) {

                Node *minNode = getHighestNodeFromRight (node->right);

                node->data = minNode->data;
                node->right = eraseHelper (node->right, minNode->data, path);
            }

            else if (!node->left) {

                if (node->right)
                    path.push_back (node->right);
                return node->right;
            }

            else {
                if (node->left)
                    path.push_back(node->left);
                return node->left;
            }
        }

        else if (data > node->data)
            node->right = eraseHelper (node->right, data, path);
        else
            node->left = eraseHelper (node->left, data, path);

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

    static Node* pushToRoot (Node *root, const T &data) {

        if (!root)
            return new Node {data};

        else if (root->data > data) {
            root->left = pushToRoot(root->left, data);
            root = balance(root);
        }
        else {
            root->right = pushToRoot (root->right, data);
            root = balance(root);
        }

        return root;
    }

public:

    explicit AVLTree (size_t n = 0)
            : root (nullptr)

    {
        if constexpr (std::is_same_v <T, Point>) {

            for (size_t i = 0; i < n; ++i) {

                push (Point {});
            }
        }
    }

    bool empty () const {
        return !root;
    }


    void push (const T &data){

        root = pushToRoot (root, data);
    }

    Iterator <Node> begin () {

        return root;
    }

    Iterator <Node> end () {

        return {root, true};
    }

    void erase (Iterator <Node> it) {

        auto data = *it;
        std::vector <Node*> path;
        root = eraseHelper (root, data, path);

        std::reverse (path.begin(), path.end());
        for (auto i : path)
            balance (i);
    }

    bool find (const T& value) const {

        return findHelper (root, value);
    }

    ~AVLTree() {

        deleter (root);
    }
};
#endif //LAB6_AVL_HPP
