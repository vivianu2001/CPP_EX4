#pragma once
#include "node.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>
#include <stack>
#include <queue>
#include "complex.hpp"
#include "value_to_qstring.hpp"
#include <QTimer>
#include <QtWidgets/QGraphicsDropShadowEffect>

template <typename T, size_t K = 2>
class Tree
{
private:
    Node<T> *root;

public:
    Tree() : root(nullptr) {}
    ~Tree() { delete root; }

    void add_root(const Node<T> &node)
    {
        if (root)
        {
            delete root;
        }
        root = new Node<T>(node); // Ensure correct value initialization
    }

    bool add_sub_node(const Node<T> &parent_node, const Node<T> &child_node)
    {
        Node<T> *parent = find_node(root, parent_node.get_value());
        if (parent && parent->children.size() < K)
        {
            parent->add_child(new Node<T>(child_node));
            return true;
        }
        return false;
    }
    // PreOrderIterator class
    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> node_stack;

    public:
        PreOrderIterator(Node<T> *root)
        {
            if (root)
            {
                node_stack.push(root);
            }
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator &other) const
        {
            if (node_stack.empty() && other.node_stack.empty())
            {
                return true;
            }
            else if (!node_stack.empty() && !other.node_stack.empty())
            {
                return node_stack.top() == other.node_stack.top();
            }
            return false;
        }

        PreOrderIterator &operator++()
        {
            if (!node_stack.empty())
            {
                Node<T> *current = node_stack.top();
                node_stack.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                {
                    node_stack.push(*it);
                }
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *node_stack.top();
        }

        Node<T> *operator->() const
        {
            return node_stack.top();
        }
    };

    PreOrderIterator begin_pre_order()
    {
        if (K != 2)
        {
            throw std::logic_error("Pre-order traversal is only supported for binary trees.");
        }
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order()
    {
        return PreOrderIterator(nullptr);
    }

    // PostOrderIterator class
    class PostOrderIterator
    {
    private:
        Node<T> *current;
        std::stack<Node<T> *> node_stack;
        std::stack<Node<T> *> output_stack;

    public:
        PostOrderIterator(Node<T> *root)
        {
            if (root)
            {
                node_stack.push(root);
                while (!node_stack.empty())
                {
                    Node<T> *node = node_stack.top();
                    node_stack.pop();
                    output_stack.push(node);
                    for (auto child : node->children)
                    {
                        node_stack.push(child);
                    }
                }
                if (!output_stack.empty())
                {
                    current = output_stack.top();
                    output_stack.pop();
                }
                else
                {
                    current = nullptr;
                }
            }
            else
            {
                current = nullptr;
            }
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return current != other.current;
        }

        PostOrderIterator &operator++()
        {
            if (!output_stack.empty())
            {
                current = output_stack.top();
                output_stack.pop();
            }
            else
            {
                current = nullptr;
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        Node<T> *operator->() const
        {
            return current;
        }
    };

    PostOrderIterator begin_post_order()
    {
        if (K != 2)
        {
            throw std::logic_error("Pre-order traversal is only supported for binary trees.");
        }
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order()
    {
        return PostOrderIterator(nullptr);
    }

    // InOrderIterator class
    class InOrderIterator
    {
    private:
        Node<T> *current;
        std::stack<Node<T> *> node_stack;

        void push_left(Node<T> *node)
        {
            while (node)
            {
                node_stack.push(node);
                node = (node->children.size() > 0) ? node->children[0] : nullptr;
            }
        }

    public:
        InOrderIterator(Node<T> *root) : current(nullptr)
        {
            push_left(root);
            if (!node_stack.empty())
            {
                current = node_stack.top();
                node_stack.pop();
            }
        }

        bool operator!=(const InOrderIterator &other) const
        {
            return current != other.current;
        }

        InOrderIterator &operator++()
        {
            if (current)
            {
                Node<T> *right = (current->children.size() > 1) ? current->children[1] : nullptr;
                push_left(right);
                if (!node_stack.empty())
                {
                    current = node_stack.top();
                    node_stack.pop();
                }
                else
                {
                    current = nullptr;
                }
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        Node<T> *operator->() const
        {
            return current;
        }
    };

    InOrderIterator begin_in_order()
    {
        if (K != 2)
        {
            throw std::logic_error("Pre-order traversal is only supported for binary trees.");
        }
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order()
    {
        return InOrderIterator(nullptr);
    }

    // BFSIterator class
    class BFSIterator
    {
    private:
        Node<T> *current;
        std::queue<Node<T> *> node_queue;

    public:
        BFSIterator(Node<T> *root)
        {
            if (root)
            {
                node_queue.push(root);
                current = root;
            }
            else
            {
                current = nullptr;
            }
        }

        bool operator!=(const BFSIterator &other) const
        {
            return current != other.current;
        }

        BFSIterator &operator++()
        {
            if (!node_queue.empty())
            {
                current = node_queue.front();
                node_queue.pop();
                for (auto child : current->children)
                {
                    node_queue.push(child);
                }
                if (!node_queue.empty())
                {
                    current = node_queue.front();
                }
                else
                {
                    current = nullptr;
                }
            }
            else
            {
                current = nullptr;
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        Node<T> *operator->() const
        {
            return current;
        }
    };

    BFSIterator begin_bfs_scan()
    {

        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan()
    {
        return BFSIterator(nullptr);
    }

    class DFSIterator
    {
    private:
        Node<T> *current;
        std::stack<Node<T> *> node_stack;

    public:
        DFSIterator(Node<T> *root)
        {
            if (root)
            {
                node_stack.push(root);
                current = root;
            }
            else
            {
                current = nullptr;
            }
        }

        bool operator!=(const DFSIterator &other) const
        {
            return current != other.current;
        }

        DFSIterator &operator++()
        {
            if (!node_stack.empty())
            {
                current = node_stack.top();
                node_stack.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                {
                    node_stack.push(*it);
                }
                if (!node_stack.empty())
                {
                    current = node_stack.top();
                }
                else
                {
                    current = nullptr;
                }
            }
            else
            {
                current = nullptr;
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        Node<T> *operator->() const
        {
            return current;
        }
    };

    DFSIterator begin_dfs_scan()
    {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan()
    {
        return DFSIterator(nullptr);
    }

    class HeapIterator
    {
    private:
        std::vector<Node<T> *> heap;
        size_t index;

        void heapify(Node<T> *root)
        {
            if (!root)
                return;
            std::vector<Node<T> *> nodes;
            std::queue<Node<T> *> node_queue;
            node_queue.push(root);

            while (!node_queue.empty())
            {
                Node<T> *node = node_queue.front();
                node_queue.pop();
                nodes.push_back(node);
                for (auto child : node->children)
                {
                    node_queue.push(child);
                }
            }

            std::make_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b)
                           {
                               return a->get_value() > b->get_value(); // Min-heap comparator
                           });

            // Extract elements to form the sorted heap
            while (!nodes.empty())
            {
                std::pop_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b)
                              {
                                  return a->get_value() > b->get_value(); // Min-heap comparator
                              });
                heap.push_back(nodes.back());
                nodes.pop_back();
            }

            // Reverse to maintain min-heap order
            // std::reverse(heap.begin(), heap.end());
        }

        // Private constructor for creating end iterator
        HeapIterator(size_t end_index) : index(end_index) {}

    public:
        HeapIterator(Node<T> *root) : index(0)
        {
            heapify(root);
        }

        bool operator!=(const HeapIterator &other) const
        {
            return index != other.index;
        }

        HeapIterator &operator++()
        {
            if (index < heap.size())
            {
                ++index;
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *heap[index];
        }

        Node<T> *operator->() const
        {
            return heap[index];
        }

        friend class Tree;
    };

    HeapIterator begin_heap() const
    {
        return HeapIterator(root);
    }

    HeapIterator end_heap() const
    {
        HeapIterator end_it = begin_heap();
        end_it.index = end_it.heap.size();
        return end_it;
    }
    void drawTree(QGraphicsScene &scene, Node<T> *node, int x, int y, int dx, int dy, int level = 0) const
    {
        if (!node)
            return;

        if (level == 0)
        {
               scene.setBackgroundBrush(QBrush(QColor(255, 247, 241))); // Slightly darker gray background color

        }

        int circleRadius = 35;                // Radius for the circle representing nodes
        QLinearGradient gradient(0, 0, 1, 1); // Gradient for nodes
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(255, 105, 180)); // Strong pink
        gradient.setColorAt(1, QColor(199, 21, 133));  // Deep pink
        QPen linePen(QColor(0, 0, 0), 4);              // Thicker black lines
        QFont textFont("Ariel", 10, QFont::Bold);      // Font for the text

        // Draw the circle for the node with gradient
        QGraphicsEllipseItem *circle = scene.addEllipse(x - circleRadius, y - circleRadius, circleRadius * 2, circleRadius * 2);
        circle->setBrush(gradient);
        circle->setPen(QPen(Qt::black));

        // Adding shadow effect
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(15);
        shadow->setOffset(10, 10);
        circle->setGraphicsEffect(shadow);

        // Draw the text inside the circle
        QGraphicsTextItem *text = scene.addText(valueToQString(node->get_value()));
        text->setFont(textFont);
        text->setDefaultTextColor(Qt::white);

        QRectF textRect = text->boundingRect();
        text->setPos(x - textRect.width() / 2, y - textRect.height() / 2);

        int childCount = node->children.size();
        int childX = x - dx * (childCount - 1) / 2; // Adjust horizontal position to center children
        int childY = y + dy;                        // Increase the length of the line between levels

        for (Node<T> *child : node->children)
        {
            scene.addLine(x, y + circleRadius, childX, childY - circleRadius, linePen);
            drawTree(scene, child, childX, childY, dx / 2, dy + 10, level + 1); // Keep the same dx for horizontal spacing
            childX += dx;                                                       // Move to the next sibling position
        }
    }

    void printTree() const
    {
        int argc = 0;
        char *argv[] = {(char *)"TreeVisualizer"};
        QApplication app(argc, argv);
        QGraphicsScene scene;
        QGraphicsView view(&scene);

        drawTree(scene, root, 70, 10, 500, 150);

        view.show();
        app.exec();
    }
   void drawHeap(QGraphicsScene &scene, const std::vector<Node<T> *> &heap, int x, int y, int dx) const
{
    if (heap.empty())
        return;

    scene.setBackgroundBrush(QBrush(QColor(255, 247, 241))); // Slightly darker gray background color

    int nodeCount = heap.size();
    int circleRadius = 35;                // Radius for the circle representing nodes
    int verticalSpacing = 100;             // Vertical spacing between levels
    QLinearGradient gradient(0, 0, 1, 1); // Gradient for nodes
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setColorAt(0, QColor(255, 105, 180)); // Strong pink
    gradient.setColorAt(1, QColor(199, 21, 133));  // Deep pink
    QPen linePen(QColor(0, 0, 0), 4);              // Thicker black lines
    QFont textFont("Arial", 10, QFont::Bold);      // Font for the text

    // Calculate the maximum width at the bottom level
    int maxLevel = static_cast<int>(std::log2(nodeCount));
    int maxWidth = std::pow(2, maxLevel) * dx;

    for (int index = 0; index < nodeCount; ++index)
    {
        int level = static_cast<int>(std::log2(index + 1));
        int levelStartIndex = std::pow(2, level) - 1;
        int levelOffset = index - levelStartIndex;
        int nodesInLevel = std::pow(2, level);

        // Calculate horizontal position
        int posX = x + (levelOffset * maxWidth / nodesInLevel) - (maxWidth / 2 - dx / 2);
        int posY = y + level * verticalSpacing;

        // Draw the circle for the node with gradient
        QGraphicsEllipseItem *circle = scene.addEllipse(posX - circleRadius, posY - circleRadius, circleRadius * 2, circleRadius * 2);
        circle->setBrush(gradient);
        circle->setPen(QPen(Qt::black, 2)); // Thicker border for nodes

        // Adding shadow effect
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(20); // Increased blur radius
        shadow->setOffset(10, 10); // Increased shadow offset
        circle->setGraphicsEffect(shadow);

        // Draw the text inside the circle
        QGraphicsTextItem *text = scene.addText(valueToQString(heap[index]->get_value()));
        text->setFont(textFont);
        text->setDefaultTextColor(Qt::white); // Ensure text is visible against the gradient

        // Center the text
        QRectF textRect = text->boundingRect();
        text->setPos(posX - textRect.width() / 2, posY - textRect.height() / 2);

        if (index > 0)
        {
            int parentIndex = (index - 1) / 2;
            int parentLevel = static_cast<int>(std::log2(parentIndex + 1));
            int parentLevelStartIndex = std::pow(2, parentLevel) - 1;
            int parentLevelOffset = parentIndex - parentLevelStartIndex;
            int parentNodesInLevel = std::pow(2, parentLevel);

            // Calculate parent positions
            int parentPosX = x + (parentLevelOffset * maxWidth / parentNodesInLevel) - (maxWidth / 2 - dx / 2);
            int parentPosY = y + parentLevel * verticalSpacing;

            scene.addLine(posX, posY - circleRadius, parentPosX, parentPosY + circleRadius, linePen);
        }
    }
}

void printHeap() const
{
    int argc = 0;
    char *argv[] = {(char *)"HeapVisualizer"};
    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    std::vector<Node<T> *> heap;
    HeapIterator heap_it(root);
    while (heap_it != end_heap())
    {
        heap.push_back(&(*heap_it));
        ++heap_it;
    }

    drawHeap(scene, heap, 100, 50, 80); // Increase initial dx for maximum spacing at root level

    view.show();
    app.exec();
}

    class Iterator
    {
    private:
        Node<T> *current;
        std::queue<Node<T> *> nodes_queue;

        void traverse(Node<T> *root)
        {
            if (!root)
                return;

            std::queue<Node<T> *> tempQueue;
            tempQueue.push(root);

            while (!tempQueue.empty())
            {
                Node<T> *node = tempQueue.front();
                tempQueue.pop();
                nodes_queue.push(node);

                for (auto child : node->children)
                {
                    tempQueue.push(child);
                }
            }
        }

    public:
        Iterator(Node<T> *root) : current(nullptr)
        {
            if (root)
            {
                traverse(root);
                if (!nodes_queue.empty())
                {
                    current = nodes_queue.front();
                    nodes_queue.pop();
                }
            }
        }

        Iterator &operator++()
        {
            if (!nodes_queue.empty())
            {
                current = nodes_queue.front();
                nodes_queue.pop();
            }
            else
            {
                current = nullptr;
            }
            return *this;
        }

        Node<T> &operator*() const
        {
            return *current;
        }

        Node<T> *operator->() const
        {
            return current;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin() const
    {
        return Iterator(root);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

private:
    Node<T> *find_node(Node<T> *node, const T &key) const
    {
        if (!node)
            return nullptr;
        if (node->get_value() == key)
            return node;
        for (Node<T> *child : node->children)
        {
            Node<T> *result = find_node(child, key);
            if (result)
                return result;
        }
        return nullptr;
    }
    void heapify(Node<T> *node, std::vector<Node<T> *> &heap) const
    {
        if (!node)
            return;
        std::vector<Node<T> *> nodes;
        std::queue<Node<T> *> node_queue;
        node_queue.push(node);

        while (!node_queue.empty())
        {
            Node<T> *n = node_queue.front();
            node_queue.pop();
            nodes.push_back(n);
            for (auto child : n->children)
            {
                node_queue.push(child);
            }
        }

        std::make_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b)
                       {
                           return a->get_value() > b->get_value(); // Min-heap comparator
                       });

        while (!nodes.empty())
        {
            std::pop_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b)
                          {
                              return a->get_value() > b->get_value(); // Min-heap comparator
                          });
            heap.push_back(nodes.back());
            nodes.pop_back();
        }

        std::reverse(heap.begin(), heap.end()); // Reverse to maintain min-heap order
    }
};