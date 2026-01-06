#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "DynamicQueue.hpp"
#include <iostream>
#include <functional>

template <typename T>
class HashTable {
private:
    T* table;
    bool* occupied;
    int size;

    DynamicQueue<T> collisionQueue;

    int hash1(const T& key) const {
        return std::hash<T>{}(key) % size;
    }

    int hash2(const T& key) const {
        return 1 + (std::hash<T>{}(key) % (size - 1));
    }

public:
    HashTable(int size) : size(size) {
        table = new T[size];
        occupied = new bool[size];

        for(int i = 0; i < size; i++)
            occupied[i] = false;
    }

    ~HashTable() {
        delete[] table;
        delete[] occupied;
    }

    void insert(const T& value) {
        std::size_t idx = hash1(value);
        std::size_t step = hash2(value);

        if(!occupied[idx]) {
            table[idx] = value;
            occupied[idx] = true;
            return;
        }

        for(int i = 1; i < size; i++) {
            int newIdx = (idx + i * step) % size;
            if(!occupied[newIdx]) {
                table[newIdx] = value;
                occupied[newIdx] = true;
                return;
            }
        }

        collisionQueue.pushBack(value);
    }

    void printTable() const {
        std::cout << "\nTabela Hash:" << std::endl;
        for(int i = 0; i < size; i++) {
            std::cout << "[" << i << "] ";
            if(occupied[i]) std::cout << table[i];
            else std::cout << "EMPTY";
            std::cout << std::endl;
        }
    }

    void printCollisionQueue() const {
        std::cout << "\nFila de colisoes:" << std::endl;
        collisionQueue.printQueue();
    }
};

#endif
