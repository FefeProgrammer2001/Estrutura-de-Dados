#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;

public:
    Node(const T& value)
        : data(value), next(nullptr), prev(nullptr) {}

    T getData() const { return data; }

    Node<T>* getNext() const { return next; }
    Node<T>* getPrev() const { return prev; }

    void setNext(Node<T>* n) { next = n; }
    void setPrev(Node<T>* p) { prev = p; }
};

#endif
