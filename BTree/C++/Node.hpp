#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node {
private:
    int t;
    int n;
    int* keys;
    Node** children;
    bool leaf;

public:
    Node(int t, bool leaf)
        : t(t), n(0), leaf(leaf) {
        keys = new int[2 * t - 1];
        children = new Node*[2 * t];
        for(int i = 0; i < 2 * t; i++) children[i] = nullptr;
    }

    ~Node() {
        delete[] keys;
        delete[] children;
    }

    int getT() const { return t; }

    int getN() const { return n; }
    void setN(int val) { n = val; }

    int* getKeys() const { return keys; }
    void setKey(int i, int val) { keys[i] = val; }

    Node** getChildren() const { return children; }
    void setChild(int i, Node* child) { children[i] = child; }

    bool isLeaf() const { return leaf; }
    void setLeaf(bool val) { leaf = val; }

    void printNode(int level = 0) const {
        std::cout << "Level " << level << ": ";
        for(int i = 0; i < n; i++)
            std::cout << keys[i] << " ";
        std::cout << std::endl;
        if(!leaf) {
            for(int i = 0; i <= n; i++) {
                if(children[i] != nullptr)
                    children[i]->printNode(level + 1);
            }
        }
    }
};

#endif
