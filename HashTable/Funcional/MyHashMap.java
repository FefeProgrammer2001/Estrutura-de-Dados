package HashMap;

import java.util.Optional;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;

public class MyHashMap<K, V> {

    private static final int TABLE_SIZE = 101;
    private final LinkedList<K, V>[] table;
    private final ReentrantLock lock = new ReentrantLock();

    private static class LinkedList<K, V> {

        private Node<K, V> head;

        private static class Node<K, V> {
            final K key;
            V value;
            Node<K, V> next;

            Node(K key, V value) {
                this.key = key;
                this.value = value;
            }
        }

        void insert(K key, V value) {
            head = insertRec(head, key, value);
        }

        private Node<K, V> insertRec(Node<K, V> node, K key, V value) {
            if(node == null) return new Node<>(key, value);
            if(node.key.equals(key)) {
                node.value = value;
                return node;
            }
            node.next = insertRec(node.next, key, value);
            return node;
        }

        Optional<V> get(K key) {
            return find(head, key).map(n -> n.value);
        }

        private Optional<Node<K, V>> find(Node<K, V> node, K key) {
            if(node == null) return Optional.empty();
            if(node.key.equals(key)) return Optional.of(node);
            return find(node.next, key);
        }

        void remove(K key) {
            head = removeRec(head, key);
        }

        private Node<K, V> removeRec(Node<K, V> node, K key) {
            if(node == null) return null;
            if(node.key.equals(key)) return node.next;
            node.next = removeRec(node.next, key);
            return node;
        }

        boolean isEmpty() {
            return head == null;
        }

        int size() {
            return sizeRec(head);
        }

        private int sizeRec(Node<K, V> node) {
            return node == null ? 0 : 1 + sizeRec(node.next);
        }

        void clear() {
            head = null;
        }
    }

    @SuppressWarnings("unchecked")
    public MyHashMap() {
        table = new LinkedList[TABLE_SIZE];
        IntStream.range(0, TABLE_SIZE)
                 .forEach(i -> table[i] = new LinkedList<>());
    }

    private int hash(K key) {
        return Math.abs(key.hashCode()) % TABLE_SIZE;
    }

    public void put(K key, V value) {
        lock.lock();
        try {
            table[hash(key)].insert(key, value);
        } finally {
            lock.unlock();
        }
    }

    public Optional<V> get(K key) {
        lock.lock();
        try {
            return table[hash(key)].get(key);
        } finally {
            lock.unlock();
        }
    }

    public void remove(K key) {
        lock.lock();
        try {
            table[hash(key)].remove(key);
        } finally {
            lock.unlock();
        }
    }

    public boolean isEmpty() {
        lock.lock();
        try {
            return IntStream.range(0, TABLE_SIZE)
                            .allMatch(i -> table[i].isEmpty());
        } finally {
            lock.unlock();
        }
    }

    public int size() {
        lock.lock();
        try {
            return IntStream.range(0, TABLE_SIZE)
                            .map(i -> table[i].size())
                            .sum();
        } finally {
            lock.unlock();
        }
    }

    public void clear() {
        lock.lock();
        try {
            IntStream.range(0, TABLE_SIZE)
                     .forEach(i -> table[i].clear());
        } finally {
            lock.unlock();
        }
    }
}
