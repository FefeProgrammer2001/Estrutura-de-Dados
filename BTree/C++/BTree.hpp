#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"
#include <iostream>

class BTree {
private:
    Node* root;
    int t;

public:
    explicit BTree(int t) : t(t) {
        root = new Node(t, true);
    }

    ~BTree() {
        delete root;
    }

    void insert(int key) {
        Node* r = root;
        if(r->getN() == 2 * t - 1) {
            Node* s = new Node(t, false);
            s->setChild(0, r);
            root = s;
            splitChild(s, 0, r);
            insertNonFull(s, key);
        } else {
            insertNonFull(r, key);
        }
    }

private:
    void insertNonFull(Node* x, int key) {
        int i = x->getN() - 1;
        int* keys = x->getKeys();

        if(x->isLeaf()) {
            while(i >= 0 && key < keys[i]) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            x->setN(x->getN() + 1);
        } else {
            while(i >= 0 && key < keys[i]) i--;
            i++;
            Node** children = x->getChildren();
            if(children[i]->getN() == 2 * t - 1) {
                splitChild(x, i, children[i]);
                if(key > x->getKeys()[i]) i++;
            }
            insertNonFull(children[i], key);
        }
    }

    void splitChild(Node* x, int i, Node* y) {
        Node* z = new Node(t, y->isLeaf());
        z->setN(t - 1);

        int* yKeys = y->getKeys();
        int* zKeys = z->getKeys();
        for(int j = 0; j < t - 1; j++)
            zKeys[j] = yKeys[j + t];

        if(!y->isLeaf()) {
            Node** yChildren = y->getChildren();
            Node** zChildren = z->getChildren();
            for(int j = 0; j < t; j++)
                zChildren[j] = yChildren[j + t];
        }

        y->setN(t - 1);

        Node** xChildren = x->getChildren();
        for(int j = x->getN(); j >= i + 1; j--)
            xChildren[j + 1] = xChildren[j];
        xChildren[i + 1] = z;

        int* xKeys = x->getKeys();
        for(int j = x->getN() - 1; j >= i; j--)
            xKeys[j + 1] = xKeys[j];
        xKeys[i] = yKeys[t - 1];
        x->setN(x->getN() + 1);
    }

public:
    Node* search(Node* x, int key) const {
        int i = 0;
        int* keys = x->getKeys();
        while(i < x->getN() && key > keys[i]) i++;
        if(i < x->getN() && key == keys[i])
            return x;
        if(x->isLeaf())
            return nullptr;
        return search(x->getChildren()[i], key);
    }

    bool contains(int key) const {
        return search(root, key) != nullptr;
    }

    void remove(int key) {
        if(!root) {
            std::cout << "Empty tree!" << std::endl;
            return;
        }
        remove(root, key);
        if(root->getN() == 0 && !root->isLeaf())
            root = root->getChildren()[0];
    }

private:
    int findKey(Node* x, int key) {
        int idx = 0;
        int* keys = x->getKeys();
        while(idx < x->getN() && keys[idx] < key) idx++;
        return idx;
    }

    void remove(Node* x, int key) {
        int idx = findKey(x, key);
        int* keys = x->getKeys();

        if(idx < x->getN() && keys[idx] == key) {
            if(x->isLeaf())
                removeFromLeaf(x, idx);
            else
                removeFromNonLeaf(x, idx);
        } else {
            if(x->isLeaf()) {
                std::cout << "Key " << key << " was not found\n";
                return;
            }

            bool lastChild = (idx == x->getN());
            Node** children = x->getChildren();
            if(children[idx]->getN() < t)
                fill(x, idx);

            if(lastChild && idx > x->getN())
                remove(children[idx - 1], key);
            else
                remove(children[idx], key);
        }
    }

    void removeFromLeaf(Node* x, int idx) {
        int* keys = x->getKeys();
        for(int i = idx + 1; i < x->getN(); i++)
            keys[i - 1] = keys[i];
        x->setN(x->getN() - 1);
    }

    void removeFromNonLeaf(Node* x, int idx) {
        int* keys = x->getKeys();
        int key = keys[idx];
        Node** children = x->getChildren();

        if(children[idx]->getN() >= t) {
            int pred = getPred(x, idx);
            keys[idx] = pred;
            remove(children[idx], pred);
        } else if(children[idx + 1]->getN() >= t) {
            int succ = getSucc(x, idx);
            keys[idx] = succ;
            remove(children[idx + 1], succ);
        } else {
            merge(x, idx);
            remove(children[idx], key);
        }
    }

    int getPred(Node* x, int idx) {
        Node* cur = x->getChildren()[idx];
        while(!cur->isLeaf())
            cur = cur->getChildren()[cur->getN()];
        return cur->getKeys()[cur->getN() - 1];
    }

    int getSucc(Node* x, int idx) {
        Node* cur = x->getChildren()[idx + 1];
        while(!cur->isLeaf())
            cur = cur->getChildren()[0];
        return cur->getKeys()[0];
    }

    void fill(Node* x, int idx) {
        Node** children = x->getChildren();
        if(idx != 0 && children[idx - 1]->getN() >= t)
            borrowFromPrev(x, idx);
        else if(idx != x->getN() && children[idx + 1]->getN() >= t)
            borrowFromNext(x, idx);
        else {
            if(idx != x->getN())
                merge(x, idx);
            else
                merge(x, idx - 1);
        }
    }

    void borrowFromPrev(Node* x, int idx) {
        Node* child = x->getChildren()[idx];
        Node* sibling = x->getChildren()[idx - 1];

        for(int i = child->getN() - 1; i >= 0; i--)
            child->getKeys()[i + 1] = child->getKeys()[i];

        if(!child->isLeaf()) {
            for(int i = child->getN(); i >= 0; i--)
                child->getChildren()[i + 1] = child->getChildren()[i];
        }

        child->getKeys()[0] = x->getKeys()[idx - 1];
        if(!x->isLeaf())
            child->getChildren()[0] = sibling->getChildren()[sibling->getN()];

        x->getKeys()[idx - 1] = sibling->getKeys()[sibling->getN() - 1];

        child->setN(child->getN() + 1);
        sibling->setN(sibling->getN() - 1);
    }

    void borrowFromNext(Node* x, int idx) {
        Node* child = x->getChildren()[idx];
        Node* sibling = x->getChildren()[idx + 1];

        child->getKeys()[child->getN()] = x->getKeys()[idx];
        if(!child->isLeaf())
            child->getChildren()[child->getN() + 1] = sibling->getChildren()[0];

        x->getKeys()[idx] = sibling->getKeys()[0];

        for(int i = 1; i < sibling->getN(); i++)
            sibling->getKeys()[i - 1] = sibling->getKeys()[i];

        if(!sibling->isLeaf()) {
            for(int i = 1; i <= sibling->getN(); i++)
                sibling->getChildren()[i - 1] = sibling->getChildren()[i];
        }

        child->setN(child->getN() + 1);
        sibling->setN(sibling->getN() - 1);
    }

    void merge(Node* x, int idx) {
        Node* child = x->getChildren()[idx];
        Node* sibling = x->getChildren()[idx + 1];

        child->getKeys()[t - 1] = x->getKeys()[idx];

        for(int i = 0; i < sibling->getN(); i++)
            child->getKeys()[i + t] = sibling->getKeys()[i];

        if(!child->isLeaf()) {
            for(int i = 0; i <= sibling->getN(); i++)
                child->getChildren()[i + t] = sibling->getChildren()[i];
        }

        for(int i = idx + 1; i < x->getN(); i++)
            x->getKeys()[i - 1] = x->getKeys()[i];

        for(int i = idx + 2; i <= x->getN(); i++)
            x->getChildren()[i - 1] = x->getChildren()[i];

        child->setN(child->getN() + sibling->getN() + 1);
        x->setN(x->getN() - 1);
    }

public:
    void print() const {
        if(root != nullptr)
            root->printNode(0);
    }
};

#endif
