#ifndef LAB6_TWOTHREE_HPP
#define LAB6_TWOTHREE_HPP

class TwoThreeNode {

    Point key[2];
    TwoThreeNode *parent, *child[3];


    const auto getSmallest()  {

        TwoThreeNode *node = this;

        while (!node->isLeaf())
            node = node->child[0];
        return node->key[0];
    }


    void insert1Siblings (TwoThreeNode *newChild, const Point& newSmallest) {

        auto newKey = newChild->key[0];
        newChild->parent = this;

        if (newKey < child[0]->key[0]) {

            child[1] = child[0];
            child[0] = newChild;
            key[0] = child[1]->getSmallest();
        }
        else {

            child[1] = newChild;
            key[0] = newSmallest;
        }
    }


    void insert2Siblings (TwoThreeNode *newChild, const Point& newSmallest) {

        auto newKey = newChild->key[0];
        newChild->parent = this;

        if (newKey < child[0]->key[0]) {
            child[2] = child[1];
            child[1] = child[0];
            child[0] = newChild;

            key[1] = key[0];
            key[0] = child[1]->getSmallest();
            updateParentSmallest (newSmallest);
        }
        else if (newKey < child[1]->key[0]) {
            child[2] = child[1];
            child[1] = newChild;

            key[1] = key[0];
            key[0] = newSmallest;
        }
        else {

            child[2] = newChild;
            key[1] = newSmallest;
        }
    }

    // Insert into a node with 3 children
    void insert3Siblings (TwoThreeNode *newChild, const Point& newSmallest) {

        auto newKey = newChild->key[0];

        Point splitSmallest {};
        auto splitNode = new TwoThreeNode();
        splitNode->parent = parent;

        if (newKey < child[0]->key[0] || newKey < child[1]->key[0]) {

            splitSmallest = key[0];
            splitNode->child[0] = child[1];
            splitNode->child[1] = child[2];
            splitNode->key[0] = key[1];

            child[1]->parent = splitNode;
            child[2]->parent = splitNode;
            newChild->parent = this;

            if (newKey < child[0]->key[0]) {

                child[1] = child[0];
                child[0] = newChild;

                key[0] = child[1]->getSmallest();
                updateParentSmallest (newSmallest);
            }
            else {

                child[1] = newChild;
                key[0] = newSmallest;
            }
        }
        else {

            child[2]->parent = splitNode;
            newChild->parent = splitNode;

            if (newKey < child[2]->key[0]) {

                splitSmallest = newSmallest;
                splitNode->child[0] = newChild;
                splitNode->child[1] = child[2];
                splitNode->key[0] = key[1];
            }
            else {

                splitSmallest = key[1];
                splitNode->child[0] = child[2];
                splitNode->child[1] = newChild;
                splitNode->key[0] = newSmallest;
            }
        }

        child[2] = nullptr;
        key[1] = {-1, -1, -1};

        if (!parent->parent) {

            auto newNode = new TwoThreeNode {};

            parent->child[0] = newNode;
            newNode->parent = parent;
            newNode->child[0] = this;
            parent = newNode;
        }

        parent->insert(splitNode, splitSmallest);
    }

    void updateParentSmallest (const Point& data) {

        switch (sibNumber()) {
            case 0:
                if (parent->parent)
                    parent->updateParentSmallest(data);
                break;
            case 1:
                parent->key[0] = data;
                break;
            case 2:
                parent->key[1] = data;
                break;
        }
    }

public:


    friend class TwoThreeTree;
    friend class TwoThreeIterator;

    TwoThreeNode (const Point& data = {-1, -1, -1}) {

        key[0] = data;
        key[1] = {-1, -1, -1};
        parent = child[0] = child[1] = child[2] = nullptr;
    }

    bool isLeaf() const {
        return !child[0];
    }


    int sibNumber() const {
        for (int i = 0; i < 3; ++i) {
            if (this == parent->child[i])
                return i;
        }
        return -1;
    }


    void insert (TwoThreeNode *newChild, const Point& newSmallest) {

        if (!child[1])
            insert1Siblings(newChild, newSmallest);
        else if (!child[2])
            insert2Siblings(newChild, newSmallest);
        else
            insert3Siblings(newChild, newSmallest);
    }
};

class TwoThreeIterator {

    size_t cur;
    std::vector <TwoThreeNode*> nodes;

    void fillStack (TwoThreeNode *node) {

        if (!node)
            return;

        if (node->isLeaf())
            nodes.push_back (node);

        fillStack (node->child [0]);
        fillStack (node->child [1]);
        fillStack (node->child [2]);
    }

public:

    TwoThreeIterator (TwoThreeNode *node, bool end = false)

            : cur (0)

    {
        fillStack (node);

        if (end)
            cur = nodes.size();
        else
            cur = 0;
    }

    TwoThreeIterator& operator++ () {

        ++cur;
        return *this;
    }

    TwoThreeIterator& operator-- () {

        --cur;
        return *this;
    }

    TwoThreeIterator& operator+ (int i) {

        cur += i;
        return *this;
    }

    size_t operator- (const TwoThreeIterator& other) {

        return cur - other.cur;
    }

    size_t operator+ (const TwoThreeIterator& other) {

        return cur + other.cur > nodes.size() ? 0 : cur + other.cur;
    }


    TwoThreeIterator& operator- (int i) {

        cur -= i;
        return *this;
    }

    const auto& operator* () {
        return nodes [cur]->key[0];
    }

    bool operator< (const TwoThreeIterator &other) {
        return cur < other.cur;
    }

    bool operator!= (const TwoThreeIterator &other) {
        return cur != other.cur;
    }
};


class TwoThreeTree {

    TwoThreeNode *root;


    TwoThreeNode* findSpot (TwoThreeNode *node, const Point& data) const {

        if (!node)
            return nullptr;

        while (!node->isLeaf()) {

            if (node->key[0] == data || node->key[1] == data)
                return nullptr;
            if (node->key[0] == Point {-1, -1, -1} || data < node->key[0])
                node = node->child[0];
            else if (node->key[1] == Point {-1, -1, -1} || data < node->key[1])
                node = node->child[1];
            else
                node = node->child[2];
        }

        if (node->key[0] == data)
            return nullptr;
        return node->parent;
    }


public:


    TwoThreeTree() : root (new TwoThreeNode {})

    {
        root->child[0] = new TwoThreeNode();
        root->child[0]->parent = root;
    }

    explicit TwoThreeTree (unsigned n)
        : root (new TwoThreeNode {})

    {
        root->child[0] = new TwoThreeNode();
        root->child[0]->parent = root;

        for (auto i = 0; i < n; ++i)
            push(Point{});
    }

    void push(const Point &data) {

        auto newNode = new TwoThreeNode {data};
        TwoThreeNode *spot = root->child[0];

        if (!spot->child[0]) {

            newNode->parent = spot;
            spot->child[0] = newNode;
        }
        else {
            spot = findSpot(spot, data);
            if (!spot)
                return;

            spot->insert (new TwoThreeNode(data), data);
        }
    }


    bool empty() {

        return !root;
    }

    TwoThreeIterator begin () {

        return root;
    }

    TwoThreeIterator end () {

        return {root, true};
    }

    const Point& operator[] (size_t n) {

        return *(begin() + n);
    }
};


#endif //LAB6_TWOTHREE_HPP
