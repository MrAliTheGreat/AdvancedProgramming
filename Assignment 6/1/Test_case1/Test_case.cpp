#include "tree.hpp"
#include <stdexcept>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("`Output` test1"){
  Tree tree;
  tree.add_operator_node(1, DUMMY_ROOT, Add);
  tree.add_operator_node(2, 1, Multiply);
  tree.add_operand_node(3, 1, 5);
  tree.add_operand_node(4, 2, 2);
  tree.add_operand_node(5, 2, 3);
  REQUIRE(tree.evaluate_tree() == 11);
}

TEST_CASE("`Output` test2"){
  Tree tree;
  tree.add_operator_node(1, DUMMY_ROOT, Add);
  tree.add_operator_node(2, 1, Multiply);
  tree.add_operator_node(6, 1, Median);
  tree.add_operator_node(7, 6, Not);
  tree.add_operand_node(4, 2, 2);
  tree.add_operand_node(5, 2, 3);
  tree.add_operand_node(8, 7, 4);
  tree.add_operand_node(9, 6, 10);
  tree.add_operand_node(10, 6, 20);
  tree.add_operand_node(11, 6, 30);
  REQUIRE(tree.evaluate_tree() == 21);
}

/*
       +
    /     \
   *   	  med
  / \   /  \  \  \
 2   3 10 30 not 20
 			   \
 			   4

*/
