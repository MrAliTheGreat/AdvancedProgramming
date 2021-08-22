#include "Operator.hpp"
#include "Operand.hpp"
#include "Median_Operator.hpp"

#include <algorithm>

bool sort_method(int i,int j){ return (i<j); }

Median_Operator::Median_Operator(int _id , int _parent_id)
	: Operator(_id , _parent_id){}

double Median_Operator::calculate(){
	std::vector<double> result_childs;

	for (int i = 0; i < child_operator.size(); i++){
		result_childs.push_back(child_operator[i]->calculate());
	}
	for (int i = 0; i < child_operand.size(); i++){
		result_childs.push_back(child_operand[i]->calculate());
	}
	std::sort(result_childs.begin() , result_childs.end() , sort_method);
	if (result_childs.size() % 2 == 0){
		return (result_childs[result_childs.size() / 2 - 1] + result_childs[result_childs.size() / 2]) / 2;
	}
	else{
		return result_childs[result_childs.size() / 2];
	}
}

bool Median_Operator::check_num_childs(){
	if(child_operand.size() + child_operator.size() <= 0){
		return false;
	}
	return true;
}