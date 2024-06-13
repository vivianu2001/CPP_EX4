#pragma once
#include "node.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>
#include <stack>
#include <queue>

template <typename T, size_t K = 2>
class Tree {
private:
    Node<T>* root;

public:
    Tree() : root(nullptr) {}
    ~Tree() { delete root; }

    void add_root(const Node<T>& node) {
        if (root) {
            delete root;
        }
        root = new Node<T>(node.get_value()); // Ensure correct value initialization
    }

    bool add_sub_node(const Node<T>& parent_node, const Node<T>& child_node) {
        Node<T>* parent = find_node(root, parent_node.get_value());
        if (parent && parent->children.size() < K) {
            parent->add_child(new Node<T>(child_node.get_value())); // Ensure correct value initialization
            return true;
        }
        return false;
    }
    // PreOrderIterator class
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

    // PostOrderIterator class
    class PostOrderIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> node_stack;
        std::stack<Node<T>*> output_stack;

    public:
        PostOrderIterator(Node<T>* root) {
            if (root) {
                node_stack.push(root);
                while (!node_stack.empty()) {
                    Node<T>* node = node_stack.top();
                    node_stack.pop();
                    output_stack.push(node);
                    for (auto child : node->children) {
                        node_stack.push(child);
                    }
                }
                if (!output_stack.empty()) {
                    current = output_stack.top();
                    output_stack.pop();
                } else {
                    current = nullptr;
                }
            } else {
                current = nullptr;
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return current != other.current;
        }

        PostOrderIterator& operator++() {
            if (!output_stack.empty()) {
                current = output_stack.top();
                output_stack.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }
    };

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // InOrderIterator class
    class InOrderIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> node_stack;

        void push_left(Node<T>* node) {
            while (node) {
                node_stack.push(node);
                node = (node->children.size() > 0) ? node->children[0] : nullptr;
            }
        }

    public:
        InOrderIterator(Node<T>* root) : current(nullptr) {
            push_left(root);
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return current != other.current;
        }

        InOrderIterator& operator++() {
            if (current) {
                Node<T>* right = (current->children.size() > 1) ? current->children[1] : nullptr;
                push_left(right);
                if (!node_stack.empty()) {
                    current = node_stack.top();
                    node_stack.pop();
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    // BFSIterator class
    class BFSIterator {
    private:
        Node<T>* current;
        std::queue<Node<T>*> node_queue;

    public:
        BFSIterator(Node<T>* root) {
            if (root) {
                node_queue.push(root);
                current = root;
            } else {
                current = nullptr;
            }
        }

        bool operator!=(const BFSIterator& other) const {
            return current != other.current;
        }

        BFSIterator& operator++() {
            if (!node_queue.empty()) {
                current = node_queue.front();
                node_queue.pop();
                for (auto child : current->children) {
                    node_queue.push(child);
                }
                if (!node_queue.empty()) {
                    current = node_queue.front();
                } else {
                    current = nullptr;
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // DFSIterator class
    class DFSIterator {
    private:
        Node<T>* current;
        std::stack<Node<T>*> node_stack;

    public:
        DFSIterator(Node<T>* root) {
            if (root) {
                node_stack.push(root);
                current = root;
            } else {
                current = nullptr;
            }
        }

        bool operator!=(const DFSIterator& other) const {
            return current != other.current;
        }

        DFSIterator& operator++() {
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    node_stack.push(*it);
                }
                if (!node_stack.empty()) {
                    current = node_stack.top();
                } else {
                    current = nullptr;
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

    class HeapIterator {
    private:
        std::vector<Node<T>*> heap;
        size_t index;

        void heapify(Node<T>* root) {
            if (!root) return;
            std::vector<Node<T>*> nodes;
            std::queue<Node<T>*> node_queue;
            node_queue.push(root);

            while (!node_queue.empty()) {
                Node<T>* node = node_queue.front();
                node_queue.pop();
                nodes.push_back(node);
                for (auto child : node->children) {
                    node_queue.push(child);
                }
            }

            std::make_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) {
                return a->get_value() > b->get_value();
            });

            // Extract elements to form the sorted heap
            while (!nodes.empty()) {
                std::pop_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) {
                    return a->get_value() > b->get_value();
                });
                heap.push_back(nodes.back());
                nodes.pop_back();
            }
        }

        // Private constructor for creating end iterator
        HeapIterator(size_t end_index) : index(end_index) {}

    public:
        HeapIterator(Node<T>* root) : index(0) {
            heapify(root);
            // std::cout << "Heap created with " << heap.size() << " elements." << std::endl;
            // for (auto node : heap) {
            //     std::cout << node->get_value() << " ";
            // }
            // std::cout << std::endl;
        }

        bool operator!=(const HeapIterator& other) const {
            return index != other.index;
        }

        HeapIterator& operator++() {
            if (index < heap.size()) {
                ++index;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *heap[index];
        }

        Node<T>* operator->() const {
            return heap[index];
        }

        friend class Tree;
    };

    HeapIterator begin_heap() {
        return HeapIterator(root);
    }

    HeapIterator end_heap() {
        HeapIterator end_it = begin_heap();
        end_it.index = end_it.heap.size();
        return end_it;
    }

    void drawTree(QGraphicsScene& scene, Node<T>* node, int x, int y, int dx) const {
        if (!node) return;

        QGraphicsTextItem* text = scene.addText(QString::number(node->get_value()));
        text->setPos(x, y);

        int childX = x - (dx / 2);
        int childY = y + 50;
        for (Node<T>* child : node->children) {
            scene.addLine(x + 10, y + 10, childX + 10, childY + 10);
            drawTree(scene, child, childX, childY, dx / 2);
            childX += dx;
        }
    }

    void print() const {
        int argc = 0;
        char *argv[] = {(char *)"TreeVisualizer"};
        QApplication app(argc, argv);
        QGraphicsScene scene;
        QGraphicsView view(&scene);

        drawTree(scene, root, 400, 50, 200);

        view.show();
        app.exec();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
        tree.print();
        return os;
    }
 // Iterator class for range-based for loops
    class Iterator {
    private:
        Node<T>* current;
        std::queue<Node<T>*> nodes_queue;

        void traverse(Node<T>* node) {
            if (node) {
                nodes_queue.push(node);
                for (auto child : node->children) {
                    traverse(child);
                }
            }
        }

    public:
        Iterator(Node<T>* root) : current(nullptr) {
            if (root) {
                traverse(root);
                current = nodes_queue.front();
                nodes_queue.pop();
            }
        }

        Iterator& operator++() {
            if (!nodes_queue.empty()) {
                current = nodes_queue.front();
                nodes_queue.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }


private:
    Node<T>* find_node(Node<T>* node, const T& key) const {
        if (!node) return nullptr;
        if (node->get_value() == key) return node;
        for (Node<T>* child : node->children) {
            Node<T>* result = find_node(child, key);
            if (result) return result;
        }
        return nullptr;
    }
};