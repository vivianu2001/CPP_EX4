# K-ary Tree Implementation

**Author:** Vivian Umansky
**Email:** umanskyvivian@gmail.com

## Overview

👋 Welcome to my C++ project! This project involves implementing a container representing a k-ary tree. A k-ary tree is a tree in which each vertex has at most k children. This project includes various tree traversal algorithms and visualizations using Qt. By default, the tree is a binary tree (k=2). The tree can contain keys of any type (e.g., numbers, strings, and classes).

## Files

- **main.cpp**: The entry point of the application, demonstrating the main functionalities.
- **demo.cpp**: Provides examples showcasing the usage of the tree structure.
- **tree.hpp**: Contains the implementation of the `Tree` class for managing hierarchical structures.
- **node.hpp**: Defines the `Node` class representing each node in the tree.
- **complex.hpp**: Defines the `Complex` class for handling complex data.
- **value_to_qstring.hpp**: Utility functions for converting values to `QString`.
- **test.cpp**: Contains tests for all iterators to ensure correctness.


## Tree Representation

📊 Trees are represented using nodes connected by edges. Each node contains a value and pointers to its children nodes. The `Tree` class manages the root node and provides methods for manipulating the tree.

## Implemented Classes and Methods

### Tree

- **Implementation**: Manages a hierarchical tree structure.
- **Methods**:
  - `void add_root(Node* root)`: Adds the root of the tree.
  - `void add_sub_node(Node* parent, Node* child)`: Adds a child node to a parent node.
  - `void drawTree(QGraphicsScene &scene, Node<T> *node, int x, int y, int dx, int dy, int level = 0) const`: Draws the tree using Qt.
  - `void printTree() const`: Visualizes the tree structure using Qt.
  - `void drawHeap(QGraphicsScene &scene, const std::vector<Node<T> *> &heap, int x, int y, int dx) const`: Draws the heap using Qt.
  - `void printHeap() const`: Visualizes the heap structure using Qt.

### Iterators

- **Pre-Order Iterator**: Scans the tree in the order: current node -> left subtree -> right subtree.
- **Post-Order Iterator**: Scans the tree in the order: left subtree -> right subtree -> current node.
- **In-Order Iterator**: Scans the tree in the order: left subtree -> current node -> right subtree.
- **BFS Iterator**: Scans the tree level by level from left to right.
- **DFS Iterator**: Scans the tree using the DFS algorithm.
- **Heap Iterator**: Transforms a binary tree into a minimum heap.

### Node

- **Implementation**: Represents a single node in the tree.
- **Attributes**:
  - `int value`: The value stored in the node.
  - `std::vector<Node*> children`: A list of pointers to the node's children.

### Complex

- **Implementation**: Handles complex numbers or data.
- **Attributes**:
  - `double real`: The real part of the complex number.
  - `double imag`: The imaginary part of the complex number.

### Utilities

#### value_to_qstring.hpp

- **Implementation**: Provides utility functions.
- **Functions**:
  - `QString valueToQString(int value)`: Converts an integer value to a `QString`.


## Dependencies

The project uses the following libraries:

- **QtCore**: Provides the `QString` class used in `value_to_qstring.hpp`.
- **QtWidgets**: Used for visualizing the tree and heap structures.

Ensure you have the necessary dependencies installed. For QtCore and QtWidgets, you can install them using your package manager:

```sh
sudo apt-get install qtbase5-dev qt5-default

make tree: Builds and runs the demo application.
- make tests: Builds and runs the tests.
