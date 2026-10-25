
#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class ArrayList {
    T* tab;
    std::size_t cap;  // maksymalna liczba elementow
    std::size_t n;    // aktualna liczba elementow

public:
    explicit ArrayList(std::size_t capacity = 10)
        : tab(new T[capacity]), cap(capacity), n(0) {}

    ~ArrayList() { delete[] tab; }

    ArrayList(const ArrayList& other)
        : tab(new T[other.cap]), cap(other.cap), n(other.n) {
        std::copy(other.tab, other.tab + n, tab);
    }

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            T* new_tab = new T[other.cap];
            std::copy(other.tab, other.tab + other.n, new_tab);
            delete[] tab;
            tab = new_tab;
            cap = other.cap;
            n = other.n;
        }
        return *this;
    }

    bool empty() const { return n == 0; }
    bool full() const { return n == cap; }
    std::size_t size() const { return n; }
    std::size_t max_size() const { return cap; }

    void push_front(const T& item) {
        if (full()) throw std::length_error("push_front: list is full");
        std::copy_backward(tab, tab + n, tab + n + 1);
        tab[0] = item;
        ++n;
    }

    void push_back(const T& item) {
        if (full()) throw std::length_error("push_back: list is full");
        tab[n++] = item;
    }

    T& front() {
        if (empty()) throw std::out_of_range("front: list is empty");
        return tab[0];
    }

    T& back() {
        if (empty()) throw std::out_of_range("back: list is empty");
        return tab[n - 1];
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front: list is empty");
        std::copy(tab + 1, tab + n, tab);
        --n;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("pop_back: list is empty");
        --n;
    }

    void clear() { n = 0; }

    T& operator[](std::size_t pos) {
        if (pos >= n) throw std::out_of_range("index out of range");
        return tab[pos];
    }

    const T& operator[](std::size_t pos) const {
        if (pos >= n) throw std::out_of_range("index out of range");
        return tab[pos];
    }

    void insert(std::size_t pos, const T& item) {
        if (pos > n) throw std::out_of_range("insert: index out of range");
        if (full()) throw std::length_error("insert: list is full");
        std::copy_backward(tab + pos, tab + n, tab + n + 1);
        tab[pos] = item;
        ++n;
    }

    void erase(std::size_t pos) {
        if (pos >= n) throw std::out_of_range("erase: index out of range");
        std::copy(tab + pos + 1, tab + n, tab + pos);
        --n;
    }

    int index(const T& item) const {
        for (std::size_t i = 0; i < n; ++i) {
            if (tab[i] == item) return static_cast<int>(i);
        }
        return -1;
    }

    void reverse() { std::reverse(tab, tab + n); }
    void sort() { std::sort(tab, tab + n); }

    void display() const {
        std::cout << "[";
        for (std::size_t i = 0; i < n; ++i) {
            if (i) std::cout << ", ";
            std::cout << tab[i];
        }
        std::cout << "]" << std::endl;
    }
};

#endif