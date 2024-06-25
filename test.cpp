
#include "doctest.h"
#include "complex.hpp"
#include "node.hpp"
#include "tree.hpp"
#include <string>

TEST_CASE("Adding a root when the tree is empty")
{
    Tree<int> tree;
    tree.add_root(1);
    auto it = tree.begin();
    CHECK(it != tree.end());     // Check that the tree is not empty
    CHECK(it->get_value() == 1); // Check that the root value is correct
}
TEST_CASE("Adding a root to a non-empty tree")
{
    Tree<int> tree;
    tree.add_root(1);
    tree.add_root(2);
    auto it = tree.begin();
    CHECK(it != tree.end());     // Check that the tree is not empty
    CHECK(it->get_value() == 2); // Check that the root value is updated
}

TEST_CASE("Adding a child to a node that already has the maximum number of children")
{
    Tree<int> tree; // Binary tree
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    CHECK_FALSE(tree.add_sub_node(1, 4)); // Should return false
}
TEST_CASE("Adding a child to a non-existent parent node")
{
    Tree<int> tree;
    tree.add_root(1);
    CHECK_FALSE(tree.add_sub_node(999, 2)); // Should return false
}
TEST_CASE("Adding a child to the root node")
{
    Tree<int> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    auto it = tree.begin_bfs_scan();
    CHECK(it->get_value() == 1); // Root node
    ++it;
    CHECK(it->get_value() == 2); // Child node
}
TEST_CASE("Traversing an empty tree")
{
    Tree<int> tree;
    CHECK_FALSE(tree.begin() != tree.end()); // Check that the tree is empty
}

TEST_CASE("Traversing a tree with only one node (the root)")
{
    Tree<int> tree;
    tree.add_root(1);
    auto it = tree.begin();
    CHECK(it != tree.end());     // Check that the tree is not empty
    CHECK(it->get_value() == 1); // Check that the root value is correct
    ++it;
    CHECK_FALSE(it != tree.end()); // Check that there are no more nodes
}

TEST_CASE("Deleting an empty tree")
{
    Tree<int> *tree = new Tree<int>();
    delete tree; // Should not throw any exceptions
}

TEST_CASE("Deleting a tree with multiple levels")
{
    Tree<int> *tree = new Tree<int>();
    tree->add_root(1);
    tree->add_sub_node(1, 2);
    tree->add_sub_node(1, 3);
    tree->add_sub_node(2, 4);
    tree->add_sub_node(2, 5);
    delete tree; // Should not throw any exceptions
}

TEST_CASE("Attempting pre-order traversal on a 3-ary tree")
{
    Tree<int, 3> tree; // 3-ary tree
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);

    CHECK_THROWS_AS(tree.begin_pre_order(), std::logic_error);
}
TEST_CASE("Attempting in-order traversal on a 4-ary tree")
{
    Tree<int, 4> tree; // 4-ary tree
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);

    CHECK_THROWS_AS(tree.begin_in_order(), std::logic_error);
}

TEST_CASE("Attempting post-order traversal on a 5-ary tree")
{
    Tree<int, 5> tree; // 5-ary tree
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);

    CHECK_THROWS_AS(tree.begin_post_order(), std::logic_error);
}

TEST_CASE("Testing Tree Class with Integer Keys")
{
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // Pre-Order: 1 2 4 5 3 6
    std::vector<int> pre_order_expected = {1, 2, 4, 5, 3, 6};
    std::vector<int> pre_order_result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
    {
        pre_order_result.push_back(it->get_value());
    }
    CHECK(pre_order_result == pre_order_expected);

    // Post-Order: 4 5 2 6 3 1
    std::vector<int> post_order_expected = {4, 5, 2, 6, 3, 1};
    std::vector<int> post_order_result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
    {
        post_order_result.push_back(it->get_value());
    }
    CHECK(post_order_result == post_order_expected);

    // In-Order: 4 2 5 1 6 3
    std::vector<int> in_order_expected = {4, 2, 5, 1, 6, 3};
    std::vector<int> in_order_result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
    {
        in_order_result.push_back(it->get_value());
    }
    CHECK(in_order_result == in_order_expected);

    // BFS: 1 2 3 4 5 6
    std::vector<int> bfs_expected = {1, 2, 3, 4, 5, 6};
    std::vector<int> bfs_result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: 1 2 4 5 3 6
    std::vector<int> dfs_expected = {1, 2, 4, 5, 3, 6};
    std::vector<int> dfs_result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
    {
        dfs_result.push_back(it->get_value());
    }
    CHECK(dfs_result == dfs_expected);

    // Heap: 1 2 3 4 5 6 (min-heap)
    std::vector<int> heap_expected = {1, 2, 3, 4, 5, 6};
    std::vector<int> heap_result;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it)
    {
        heap_result.push_back(it->get_value());
    }
    CHECK(heap_result == heap_expected);
}

TEST_CASE("Testing Tree Class with String Keys")
{
    Tree<std::string> tree;
    Node<std::string> root_node("A");
    tree.add_root(root_node);

    Node<std::string> n1("B");
    Node<std::string> n2("C");
    Node<std::string> n3("D");
    Node<std::string> n4("E");
    Node<std::string> n5("F");
    Node<std::string> n6("G");
    Node<std::string> n7("H");
    Node<std::string> n8("I");
    Node<std::string> n9("J");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n3, n7);
    tree.add_sub_node(n3, n8);
    tree.add_sub_node(n6, n9);

    // Pre-Order: 1 2 4 5 3 6
    std::vector<std::string> pre_order_expected = {"A", "B", "D", "H", "I", "E", "C", "F", "G", "J"};
    std::vector<std::string> pre_order_result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
    {
        pre_order_result.push_back(it->get_value());
    }
    CHECK(pre_order_result == pre_order_expected);

    // Post-Order: 4 5 2 6 3 1
    std::vector<std::string> post_order_expected = {"H", "I", "D", "E", "B", "F", "J", "G", "C", "A"};
    std::vector<std::string> post_order_result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
    {
        post_order_result.push_back(it->get_value());
    }
    CHECK(post_order_result == post_order_expected);

    // In-Order: 4 2 5 1 6 3
    std::vector<std::string> in_order_expected = {"H", "D", "I", "B", "E", "A", "F", "C", "J", "G"};
    std::vector<std::string> in_order_result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
    {
        in_order_result.push_back(it->get_value());
    }
    CHECK(in_order_result == in_order_expected);

    // BFS: 1 2 3 4 5 6
    std::vector<std::string> bfs_expected = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    std::vector<std::string> bfs_result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: 1 2 4 5 3 6
    std::vector<std::string> dfs_expected = {"A", "B", "D", "H", "I", "E", "C", "F", "G", "J"};
    std::vector<std::string> dfs_result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
    {
        dfs_result.push_back(it->get_value());
    }
    CHECK(dfs_result == dfs_expected);

    // Heap: 1 2 3 4 5 6 (min-heap)
    std::vector<std::string> heap_expected = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    std::vector<std::string> heap_result;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it)
    {
        heap_result.push_back(it->get_value());
    }
    CHECK(heap_result == heap_expected);
}

TEST_CASE("Testing Tree Class with Complex Keys")
{
    Tree<Complex> tree;
    Complex c1(1, 1);
    Complex c2(1, 2);
    Complex c3(2, 1);
    Complex c4(3, 1);
    Complex c5(1, 3);
    Complex c6(2, 2);

    Node<Complex> root_node(c1);
    tree.add_root(root_node);

    Node<Complex> n1(c2);
    Node<Complex> n2(c3);
    Node<Complex> n3(c4);
    Node<Complex> n4(c5);
    Node<Complex> n5(c6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // Pre-Order: (1+1i) (1+2i) (3+1i) (1+3i) (2+1i) (2+2i)
    std::vector<Complex> pre_order_expected = {c1, c2, c4, c5, c3, c6};
    std::vector<Complex> pre_order_result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
    {
        pre_order_result.push_back(it->get_value());
    }
    CHECK(pre_order_result == pre_order_expected);

    // Post-Order: (3+1i) (1+3i) (1+2i) (2+2i) (2+1i) (1+1i)
    std::vector<Complex> post_order_expected = {c4, c5, c2, c6, c3, c1};
    std::vector<Complex> post_order_result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
    {
        post_order_result.push_back(it->get_value());
    }
    CHECK(post_order_result == post_order_expected);

    // In-Order: (3+1i) (1+2i) (1+3i) (1+1i) (2+2i) (2+1i)
    std::vector<Complex> in_order_expected = {c4, c2, c5, c1, c6, c3};
    std::vector<Complex> in_order_result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
    {
        in_order_result.push_back(it->get_value());
    }
    CHECK(in_order_result == in_order_expected);

    // BFS: (1+1i) (1+2i) (2+1i) (3+1i) (1+3i) (2+2i)
    std::vector<Complex> bfs_expected = {c1, c2, c3, c4, c5, c6};
    std::vector<Complex> bfs_result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: (1+1i) (1+2i) (3+1i) (1+3i) (2+1i) (2+2i)
    std::vector<Complex> dfs_expected = {c1, c2, c4, c5, c3, c6};
    std::vector<Complex> dfs_result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
    {
        dfs_result.push_back(it->get_value());
    }
    CHECK(dfs_result == dfs_expected);

    // Expected min-heap order based on magnitude
    std::vector<Complex> heap_expected = {c1, c3, c2, c6, c4, c5};
    std::vector<Complex> heap_result;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it)
    {
        heap_result.push_back(it->get_value());
    }

    CHECK(heap_result == heap_expected);
}


TEST_CASE("Testing Tree Class with Complex Keys") {
    Tree<Complex> tree;
    Complex c1(1, 1);
    Complex c2(1, 2);
    Complex c3(2, 1);
    Complex c4(3, 1);
    Complex c5(1, 3);
    Complex c6(2, 2);
    Complex c7(3, 3);
    Complex c8(4, 1);
    Complex c9(5, 2);

    Node<Complex> root_node(c1);
    tree.add_root(root_node);

    Node<Complex> n1(c2);
    Node<Complex> n2(c3);
    Node<Complex> n3(c4);
    Node<Complex> n4(c5);
    Node<Complex> n5(c6);
    Node<Complex> n6(c7);
    Node<Complex> n7(c8);
    Node<Complex> n8(c9);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n3, n7);
    tree.add_sub_node(n4, n8);

    // Pre-Order: (1+1i) (1+2i) (3+1i) (4+1i) (1+3i) (5+2i) (2+1i) (2+2i) (3+3i)
    std::vector<Complex> pre_order_expected = {c1, c2, c4, c8, c5, c9, c3, c6, c7};
    std::vector<Complex> pre_order_result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        pre_order_result.push_back(it->get_value());
    }
    CHECK(pre_order_result == pre_order_expected);

    // Post-Order: (4+1i) (3+1i) (5+2i) (1+3i) (1+2i) (2+2i) (3+3i) (2+1i) (1+1i)
    std::vector<Complex> post_order_expected = {c8, c4, c9, c5, c2, c6, c7, c3, c1};
    std::vector<Complex> post_order_result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        post_order_result.push_back(it->get_value());
    }
    CHECK(post_order_result == post_order_expected);

    // In-Order: (4+1i) (3+1i) (1+2i) (5+2i) (1+3i) (1+1i) (2+2i) (2+1i) (3+3i)
    std::vector<Complex> in_order_expected = {c8, c4, c2, c9, c5, c1, c6, c3, c7};
    std::vector<Complex> in_order_result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        in_order_result.push_back(it->get_value());
    }
    CHECK(in_order_result == in_order_expected);

    // BFS: (1+1i) (1+2i) (2+1i) (3+1i) (1+3i) (2+2i) (3+3i) (4+1i) (5+2i)
    std::vector<Complex> bfs_expected = {c1, c2, c3, c4, c5, c6, c7, c8, c9};
    std::vector<Complex> bfs_result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: (1+1i) (1+2i) (3+1i) (4+1i) (1+3i) (5+2i) (2+1i) (2+2i) (3+3i)
    std::vector<Complex> dfs_expected = {c1, c2, c4, c8, c5, c9, c3, c6, c7};
    std::vector<Complex> dfs_result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        dfs_result.push_back(it->get_value());
    }
    CHECK(dfs_result == dfs_expected);

    // Expected min-heap order based on magnitude
    std::vector<Complex> heap_expected = {c1, c3, c2, c6, c5, c4, c8, c7, c9};
    std::vector<Complex> heap_result;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it) {
        heap_result.push_back(it->get_value());
    }
    CHECK(heap_result == heap_expected);
}


TEST_CASE("DFS VS BFS THREE ARY STRING")
{
    Tree<std::string, 3> three_ary_tree;
    Node<std::string> root_node("A");
    three_ary_tree.add_root(root_node);

    Node<std::string> n1("B");
    Node<std::string> n2("C");
    Node<std::string> n3("D");
    Node<std::string> n4("E");
    Node<std::string> n5("F");

    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n2, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // BFS: 1 2 3 4 5 6
    std::vector<std::string> bfs_expected = {"A", "B", "C", "D", "E", "F"};
    std::vector<std::string> bfs_result;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: 1 2 4 5 3 6
    std::vector<std::string> dfs_expected = {"A", "B", "C", "E", "F", "D"};
    std::vector<std::string> dfs_result;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it)
    {
        dfs_result.push_back(it->get_value());
    }
}

TEST_CASE("DFS VS BFS THREE ARY INT")
{
    Tree<int, 3> three_ary_tree;
    Node<int> root_node(0);
    three_ary_tree.add_root(root_node);

    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);
    Node<int> n6(6);
    Node<int> n7(7);

    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n1, n5);
    three_ary_tree.add_sub_node(n2, n6);
    three_ary_tree.add_sub_node(n3, n7);

    // BFS: 1 2 3 4 5 6
    std::vector<int> bfs_expected = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> bfs_result;
    for (auto it = three_ary_tree.begin_bfs_scan(); it != three_ary_tree.end_bfs_scan(); ++it)
    {
        bfs_result.push_back(it->get_value());
    }
    CHECK(bfs_result == bfs_expected);

    // DFS: 1 2 4 5 3 6
    std::vector<int> dfs_expected = {0, 1, 4, 5, 2, 6, 3, 7};
    std::vector<int> dfs_result;
    for (auto it = three_ary_tree.begin_dfs_scan(); it != three_ary_tree.end_dfs_scan(); ++it)
    {
        dfs_result.push_back(it->get_value());
    }
    CHECK(dfs_result == dfs_expected);
}
