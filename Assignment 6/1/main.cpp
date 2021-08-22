#include "tree.hpp"
#include <iostream>

int main() {
  Tree tree;
  tree.add_operator_node(1, DUMMY_ROOT, Add);
  tree.add_operator_node(2, 1, Multiply);
  tree.add_operand_node(3, 1, 5);
  tree.add_operand_node(4, 2, 2);
  tree.add_operand_node(5, 2, 3);
  int result = tree.evaluate_tree();
  cout << result << endl; // output will be 11
}

/*
     +
    / \
   *   5
  / \
 2   3

*/
