#pragma once
#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node*> children;

    Node(T val) : value(val) {}
    T get_value() const { return value; }
    void add_child(Node* child) { children.push_back(child); }

    // Destructor to delete all child nodes
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }
};
