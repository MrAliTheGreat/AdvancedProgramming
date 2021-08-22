#ifndef __TREE_H__
#define __TREE_H__

#define DUMMY_ROOT 0
#define FAIL 0
#include "Operator.hpp"
#include "Add_Operator.hpp"
#include "Multiply_Operator.hpp"
#include "Not_Operator.hpp"
#include "Median_Operator.hpp"

using namespace std;

enum OperatorType { Add , Multiply , Not , Median};

class Tree{
public:
  void add_operand_node(const std::size_t id, const std::size_t parent_id, const int value);
  void add_operator_node(const std::size_t id, const std::size_t parent_id, const OperatorType type);

  void parent_finder_operator_child(Operator* child_operator);
  void parent_finder_operand_child(Operand* child_operand);

  void count_childs_root(int parent_id);
  int evaluate_tree();
private:
	std::vector<Operator*> all_operators;
	std::vector<Operand*> all_operands;
	int num_childs_root;
};

#endif
