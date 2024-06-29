//umanskyvivian@gmail.com
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <sstream>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node*> children;

    Node(const T& val) : value(val) {}
    
    Node(const Node& other) : value(other.value) {
        for (auto child : other.children) {
            children.push_back(new Node(*child));
        }
    }
    
    Node& operator=(const Node& other) {
        if (this != &other) {
            value = other.value;
            for (auto child : children) {
                delete child;
            }
            children.clear();
            for (auto child : other.children) {
                children.push_back(new Node(*child));
            }
        }
        return *this;
    }
    
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }

    const T& get_value() const { return value; }
    void add_child(Node* child) {
        children.push_back(child);
    }
};

#endif // NODE_HPP
