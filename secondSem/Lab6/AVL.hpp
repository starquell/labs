#ifndef LAB6_AVL_HPP
#define LAB6_AVL_HPP

#include "point.hpp"

template <class T>
class AVLTree {

    using Node = AVLNode <T>;

    Node *root;

    static void deleter (Node *root) {

        if (!root)
            return;

        deleter (root->left);
        deleter (root->right);

        delete root;
    }

    void balance (std::vector <Node*> path) {

        for (auto &indirect: path) {
            indirect->fixHeight();

            if (indirect->balanceFactor() >= 2 && indirect->left->balanceFactor() >= 0)   // left - left
                indirect = indirect->rightRotate();

            else if (indirect->balanceFactor() >= 2) {  // left - right
                indirect->left = indirect->left->leftRotate();
                indirect = indirect->rightRotate();
            }

            else if (indirect->balanceFactor() <= -2 && indirect->right->balanceFactor() <= 0)  // right - right
                indirect = indirect->leftRotate();

            else if (indirect->balanceFactor() <= -2) {  // right - left
                indirect->right = indirect->right->rightRotate();
                indirect = indirect->leftRotate();
            }
        }
    }

    static Node* eraseHelper (Node *node, const T& data, std::vector <Node*> &path) {

        if (!node)
            return node;

        if (data == node->data) {

            path.push_back (node);

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

public:

    bool empty () {
        return !root;
    }


    void push (const T &data){

        Node **indirect = &root;  // to generalize insertion
        std::vector <Node*> path;  // to update height values

        while (*indirect) {
            path.push_back(*indirect);

            if ((*indirect)->data > data)
                indirect = &((*indirect)->left);
            else
                indirect = &((*indirect)->right);
        }

        *indirect = new Node (data);
        path.push_back (*indirect);

        balance (path);
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
        balance (path);
    }

    ~AVLTree() {

        deleter (root);
    }
};
#endif //LAB6_AVL_HPP
