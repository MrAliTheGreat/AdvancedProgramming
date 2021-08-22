#include "Operator.hpp"
#include "Operand.hpp"
#include "Multiply_Operator.hpp"
#include <iostream>

Multiply_Operator::Multiply_Operator(int _id , int _parent_id)
	: Operator(_id , _parent_id){}

double Multiply_Operator::calculate(){
	if(child_operator.size() == 0){
		return child_operand[0]->calculate() * child_operand[1]->calculate();
	}else if(child_operand.size() == 0){
		return child_operator[0]->calculate() * child_operator[1]->calculate();
	}
	return child_operator[0]->calculate() * child_operand[0]->calculate();
}

bool Multiply_Operator::check_num_childs(){
	if(child_operator.size() + child_operand.size() == 2){
		return true;
	}
	return false;
}