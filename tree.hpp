// tree.hpp
#pragma once
#include "node.hpp"
#include <iostream>
#include <vector>
#include <stack>

template <typename T>
class Tree {
private:
    Node<T>* root;
    size_t max_children;

public:
    Tree(size_t k = 2) : root(nullptr), max_children(k) {}
    ~Tree() {
        delete root;  // The destructor of Node will recursively delete all children
    }

    void add_root(const Node<T>& node) {
        if (root) {
            delete root;
        }
        root = new Node<T>(node);
    }

    bool add_sub_node(const Node<T>& parent_node, const Node<T>& child_node) {
        Node<T>* parent = find_node(root, parent_node.get_value());
        if (parent && parent->children.size() < max_children) {
            parent->add_child(new Node<T>(child_node));
            return true;
        }
        return false;
    }

    class PreOrderIterator {
    private:
        std::stack<Node<T>*> node_stack;

    public:
        PreOrderIterator(Node<T>* root) {
            if (root) {
                node_stack.push(root);
            }
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator& other) const {
            if (node_stack.empty() && other.node_stack.empty()) {
                return true;
            } else if (!node_stack.empty() && !other.node_stack.empty()) {
                return node_stack.top() == other.node_stack.top();
            }
            return false;
        }

        PreOrderIterator& operator++() {
            if (!node_stack.empty()) {
                Node<T>* current = node_stack.top();
                node_stack.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    node_stack.push(*it);
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *node_stack.top();
        }

        Node<T>* operator->() const {
            return node_stack.top();
        }
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

private:
    Node<T>* find_node(Node<T>* node, const T& key) {
        if (!node) return nullptr;
        if (node->get_value() == key) return node;
        for (Node<T>* child : node->children) {
            Node<T>* result = find_node(child, key);
            if (result) return result;
        }
        return nullptr;
    }
};
