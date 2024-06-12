// umanskyvivian@gmail.com
#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(const T& val) : value(val) {}
    ~Node() {
        for (Node<T>* child : children) {
            delete child;
        }
    }

    T get_value() const {
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }
};
