/**
 * Demo app for Ex4s
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
int runTests();

using namespace std;

int main()
{

//     Node<double> root_node = Node(1.1);
//     Tree<double> tree; // Binary tree that contains doubles.
//     tree.add_root(root_node);
//     Node<double> n1 = Node(1.2);
//     Node<double> n2 = Node(1.3);
//     Node<double> n3 = Node(1.4);
//     Node<double> n4 = Node(1.5);
//     Node<double> n5 = Node(1.6);

//     tree.add_sub_node(root_node, n1);
//     tree.add_sub_node(root_node, n2);
//     tree.add_sub_node(n1, n3);
//     tree.add_sub_node(n1, n4);
//     tree.add_sub_node(n2, n5);
   
//     // The tree should look like:
//     /**
//      *       root = 1.1
//      *     /       \
//      *    1.2      1.3
//      *   /  \      /
//      *  1.4  1.5  1.6
//      */

//        cout << "Pre-Order Traversal:" << endl;
//     for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
//         cout << node->get_value() << endl;
//     }

//     cout << "\nPost-Order Traversal:" << endl;
//     for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
//         cout << node->get_value() << endl;
//     }

//     cout << "\nIn-Order Traversal:" << endl;
//     for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
//         cout << node->get_value() << endl;
//     }

//     cout << "\nBFS Traversal:" << endl;
//     for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
//         cout << node->get_value() << endl;
//     }

//     cout << "\nDFS Traversal:" << endl;
//     for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
//         cout << node->get_value() << endl;
//     }
//  cout << "\nHeap Traversal:" << endl;
//     auto heap_begin = tree.begin_heap();
//     auto heap_end = tree.end_heap();
//     for (auto node = heap_begin; node != heap_end; ++node) {
//         cout << node->get_value() << endl;
//     }

//     cout << tree; // Should print the graph using GUI.

//     Tree<double,3> three_ary_tree; // 3-ary tree.
//     three_ary_tree.add_root(root_node);
//     three_ary_tree.add_sub_node(root_node, n1);
//     three_ary_tree.add_sub_node(root_node, n2);
//     three_ary_tree.add_sub_node(root_node, n3);
//     three_ary_tree.add_sub_node(n1, n4);
//     three_ary_tree.add_sub_node(n2, n5);

//      // The tree should look like:
//     /**
//      *       root = 1.1
//      *     /      |     \
//      *    1.2    1.3    1.4
//      *   /        |
//      *  1.5      1.6
//      */
//     cout << three_ary_tree;
 // Create complex numbers
    // Complex c1(1, 1);
    // Complex c2(1, 2);
    // Complex c3(2, 1);
    // Complex c4(3, 1);
    // Complex c5(1, 3);
    // Complex c6(2, 2);

    // // Create nodes
    // Node<Complex> root_node = Node(c1);
    // Tree<Complex> tree; // Binary tree that contains complex numbers.
    // tree.add_root(root_node);

    // Node<Complex> n1 = Node(c2);
    // Node<Complex> n2 = Node(c3);
    // Node<Complex> n3 = Node(c4);
    // Node<Complex> n4 = Node(c5);
    // Node<Complex> n5 = Node(c6);

    // tree.add_sub_node(root_node, n1);
    // tree.add_sub_node(root_node, n2);
    // tree.add_sub_node(n1, n3);
    // tree.add_sub_node(n1, n4);
    // tree.add_sub_node(n2, n5);

    // // The tree should look like:
    // /**
    //  *       root = 1+1i
    //  *     /        \
    //  *    1+2i      2+1i
    //  *   /   \       /
    //  *  3+1i 1+3i  2+2i
    //  */

    // cout << "Visualizing Tree:" << endl;
    // tree.printTree();

    // cout << "Visualizing Heap:" << endl;
    // tree.printHeap();

    // return 0;

     // Create integer numbers
    // Node<int> root_node_int = Node(1);
    // Tree<int> tree_int; // Binary tree that contains integers.
    // tree_int.add_root(root_node_int);

    // Node<int> n1_int = Node(2);
    // Node<int> n2_int = Node(3);
    // Node<int> n3_int = Node(4);
    // Node<int> n5_int = Node(6);
    // Node<int> n4_int = Node(5);
   

    // tree_int.add_sub_node(root_node_int, n1_int);
    // tree_int.add_sub_node(root_node_int, n2_int);
    // tree_int.add_sub_node(n1_int, n3_int);
    // tree_int.add_sub_node(n1_int, n4_int);
    // tree_int.add_sub_node(n2_int, n5_int);

    // // The integer tree should look like:
    // /**
    //  *       root = 1
    //  *     /        \
    //  *    2          3
    //  *   /   \       /
    //  *  4     5     6
    //  */

    // // cout << "Visualizing Integer Tree:" << endl;
    // // tree_int.printTree();

    // cout << "Visualizing Integer Heap:" << endl;
    // tree_int.printHeap();

    // return 0;
     std::cout << "\nRunning tests..." << std::endl;
    int testResult = runTests(); // Run tests and capture the result

    return testResult; // Return the result of the tests as the program's exit code
    
}