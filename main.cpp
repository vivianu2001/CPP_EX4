/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

int main()
{

    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

       cout << "Pre-Order Traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "\nPost-Order Traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "\nIn-Order Traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "\nBFS Traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }

    cout << "\nDFS Traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << endl;
    }
 cout << "\nHeap Traversal:" << endl;
    auto heap_begin = tree.begin_heap();
    auto heap_end = tree.end_heap();
    for (auto node = heap_begin; node != heap_end; ++node) {
        cout << node->get_value() << endl;
    }

    cout << tree; // Should print the graph using GUI.

    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    cout << three_ary_tree;
    
}