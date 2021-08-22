#include "Operator.hpp"
#include "Operand.hpp"

#include <vector>

Operator::Operator(int _id , int _parent_id){
	id = _id;
	parent_id = _parent_id;
}

void Operator::add_child_operator(Operator* new_child_operator){
	child_operator.push_back(new_child_operator);
}

void Operator::add_child_operand(Operand* new_child_operand){
	child_operand.push_back(new_child_operand);
}

int Operator::num_all_childs(){
	return child_operator.size() + child_operand.size();
}