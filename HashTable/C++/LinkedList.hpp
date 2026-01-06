#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <iostream>

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while(head != nullptr) {
            Node<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void pushFront(const T& value) {
        Node<T>* n = new Node<T>(value);

        if(isEmpty()) {
            head = tail = n;
        } else {
            n->setNext(head);
            head->setPrev(n);
            head = n;
        }
    }

    void pushBack(const T& value) {
        Node<T>* n = new Node<T>(value);

        if(isEmpty()) {
            head = tail = n;
        } else {
            tail->setNext(n);
            n->setPrev(tail);
            tail = n;
        }
    }

    bool popFront(T& value) {
        if(isEmpty())
            return false;

        Node<T>* temp = head;
        value = temp->getData();

        if(head == tail) {
            head = tail = nullptr;
        } else {
            head = head->getNext();
            head->setPrev(nullptr);
        }

        delete temp;
        return true;
    }

    bool popBack(T& value) {
        if(isEmpty())
            return false;

        Node<T>* temp = tail;
        value = temp->getData();

        if(head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->getPrev();
            tail->setNext(nullptr);
        }

        delete temp;
        return true;
    }

    void printList() const {
        Node<T>* cur = head;
        while(cur != nullptr) {
            std::cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        std::cout << std::endl;
    }
};

#endif
