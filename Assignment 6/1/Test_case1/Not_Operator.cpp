#include "Operator.hpp"
#include "Operand.hpp"
#include "Not_Operator.hpp"

Not_Operator::Not_Operator(int _id , int _parent_id)
	: Operator(_id , _parent_id){}

double Not_Operator::calculate(){
	if(child_operator.size() == 0){
		return child_operand[0]->calculate();
	}
	return child_operator[0]->calculate();
}

bool Not_Operator::check_num_childs(){
	if(child_operator.size() + child_operand.size() == 1){
		return true;
	}
	return false;
}