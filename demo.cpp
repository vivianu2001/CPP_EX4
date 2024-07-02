/**
 * Demo app for Ex4
 * umanskyvivian@gmail.com
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
  setenv("QT_QPA_PLATFORM", "xcb", 1);
  std::cout << "Running demo..." << std::endl;

  cout << "Creating double binary tree..." << endl;

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

  cout << "Pre-order traversal:" << endl;
  for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
  {
    cout << node->get_value() << " ";
  }
  cout << endl; // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

  cout << "Post-order traversal:" << endl;
  for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
  {
    cout << node->get_value() << " ";
  }
  cout << endl; // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

  cout << "In-order traversal:" << endl;
  for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
  {
    cout << node->get_value() << " ";
  }
  cout << endl; // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

  cout << "BFS scan:" << endl;
  for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
  {
    cout << node->get_value() << " ";
  }
  cout << endl; // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

  cout << "Level-order traversal using range-based for loop:" << endl;
  for (auto node : tree)
  {
    cout << node.get_value() << " ";
  }
  cout << endl; // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

  cout << "Printing double tree using GUI..." << endl;
  tree.printTree(); // Should print the graph using GUI.

  cout << "Creating 3-ary tree..." << endl;
  Tree<double, 3> three_ary_tree; // 3-ary tree.
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

  cout << "Creating complex number binary tree..." << endl;
  Complex c1(1, 1);
  Complex c2(1, 2);
  Complex c3(3, 1);
  Complex c4(4, 1);
  Complex c5(5, 1);
  Complex c6(6, 1);

  // Create nodes
  Node<Complex> root_node_c = Node(c1);
  Tree<Complex> tree_c; // Binary tree that contains complex numbers.
  tree_c.add_root(root_node_c);

  Node<Complex> n_c1 = Node(c2);
  Node<Complex> n_c2 = Node(c3);
  Node<Complex> n_c3 = Node(c4);
  Node<Complex> n_c4 = Node(c5);
  Node<Complex> n_c5 = Node(c6);
  tree_c.add_sub_node(root_node_c, n_c1);
  tree_c.add_sub_node(root_node_c, n_c2);
  tree_c.add_sub_node(n_c1, n_c3);
  tree_c.add_sub_node(n_c1, n_c4);
  tree_c.add_sub_node(n_c2, n_c5);

  cout << "Visualizing complex number tree using GUI..." << endl;
  tree_c.printTree();

  cout << "Visualizing complex number heap using GUI..." << endl;
  tree_c.printHeap();

  cout << "Creating integer binary tree..." << endl;
  Node<int> root_node_int = Node(1);
  Tree<int> tree_int; // Binary tree that contains integers.
  tree_int.add_root(root_node_int);

  Node<int> n1_int = Node(16);
  Node<int> n2_int = Node(18);
  Node<int> n3_int = Node(28);
  Node<int> n4_int = Node(19);
  Node<int> n5_int = Node(36);
  Node<int> n6_int = Node(35);
  Node<int> n7_int = Node(39);
  Node<int> n8_int = Node(25);
  Node<int> n9_int = Node(43);
  Node<int> n10_int = Node(10);
  Node<int> n11_int = Node(9);
  Node<int> n12_int = Node(7);
  Node<int> n13_int = Node(14);

  tree_int.add_sub_node(root_node_int, n1_int);
  tree_int.add_sub_node(root_node_int, n2_int);
  tree_int.add_sub_node(n1_int, n3_int);
  tree_int.add_sub_node(n1_int, n4_int);
  tree_int.add_sub_node(n2_int, n5_int);
  tree_int.add_sub_node(n2_int, n6_int);
  tree_int.add_sub_node(n3_int, n7_int);
  tree_int.add_sub_node(n3_int, n8_int);
  tree_int.add_sub_node(n4_int, n9_int);
  tree_int.add_sub_node(n4_int, n10_int);
  tree_int.add_sub_node(n5_int, n11_int);
  tree_int.add_sub_node(n5_int, n12_int);

  // The integer tree should look like:
  /**
   *       root = 1
   *     /        \
   *    2          3
   *   /   \       /
   *  4     5     6
   */

  cout << "Visualizing integer tree using GUI..." << endl;
  tree_int.printTree();

  cout << "Visualizing integer heap using GUI..." << endl;
  tree_int.printHeap();

  cout << "Creating integer 4-ary tree..." << endl;
  Node<int> four_root_node = Node(1);
  Tree<int, 5> four_ary_tree; // Binary tree that contains integers.
  four_ary_tree.add_root(four_root_node);

  Node<int> n1_f = Node(7);
  Node<int> n2_f = Node(8);
  Node<int> n3_f = Node(9);
  Node<int> n4_f = Node(10);
  Node<int> n5_f = Node(11);
  Node<int> n6_f = Node(12);
  Node<int> n7_f = Node(13);
  Node<int> n8_f = Node(14);
  Node<int> n9_f = Node(15);
  Node<int> n10_f = Node(18);
  Node<int> n11_f = Node(16);
  Node<int> n12_f = Node(17);
  Node<int> n13_f = Node(19);
  Node<int> n14_f = Node(20);
  Node<int> n15_f = Node(2);
  Node<int> n16_f = Node(3);
  Node<int> n17_f = Node(4);
  Node<int> n18_f = Node(5);
  Node<int> n19_f = Node(6);

  four_ary_tree.add_sub_node(four_root_node, n1_f);
  four_ary_tree.add_sub_node(four_root_node, n2_f);
  four_ary_tree.add_sub_node(four_root_node, n3_f);
  four_ary_tree.add_sub_node(four_root_node, n4_f);
  four_ary_tree.add_sub_node(n1_f, n5_f);
  four_ary_tree.add_sub_node(n1_f, n6_f);
  four_ary_tree.add_sub_node(n1_f, n7_f);

  four_ary_tree.add_sub_node(n5_f, n8_f);
  four_ary_tree.add_sub_node(n5_f, n9_f);
  four_ary_tree.add_sub_node(n5_f, n10_f);
  four_ary_tree.add_sub_node(n5_f, n11_f);
  four_ary_tree.add_sub_node(n5_f, n12_f);
  four_ary_tree.add_sub_node(n2_f, n13_f);
  four_ary_tree.add_sub_node(n3_f, n14_f);
  four_ary_tree.add_sub_node(n3_f, n15_f);
  four_ary_tree.add_sub_node(n4_f, n16_f);
  four_ary_tree.add_sub_node(n4_f, n17_f);
  four_ary_tree.add_sub_node(n4_f, n18_f);
  four_ary_tree.add_sub_node(n18_f, n19_f);

  cout << "Visualizing integer tree using GUI..." << endl;
  four_ary_tree.printTree();

  cout << "Visualizing integer heap using GUI..." << endl;
  four_ary_tree.printHeap();
}
