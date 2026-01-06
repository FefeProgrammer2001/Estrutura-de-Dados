#ifndef DYNAMICQUEUE_HPP
#define DYNAMICQUEUE_HPP

#include "LinkedList.hpp"

template <typename T>
class DynamicQueue {
private:
    LinkedList<T> list;

public:
    void pushFront(const T& value) {
        list.pushFront(value);
    }

    void pushBack(const T& value) {
        list.pushBack(value);
    }

    bool popFront(T& value) {
        return list.popFront(value);
    }

    bool popBack(T& value) {
        return list.popBack(value);
    }

    void printQueue() const {
        list.printList();
    }
};

#endif
