#include "tree.hpp"
#include "Operator.hpp"
#include "Operand.hpp"

#include <vector>
#include <iostream>
#include <stdlib.h>

class parent_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Parent node not found\n";
	}
};

class parent_operand_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Invalid parent\n";
	}
};

class tree_shape_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Invalid tree structure\n";
	}
};

void Tree::count_childs_root(int parent_id){
	num_childs_root = 0;
	for (int i = 0; i < all_operands.size(); i++){
		if(all_operands[i]->get_parent_ID() == DUMMY_ROOT){
			num_childs_root++;
		}
	}

	for (int i = 0; i < all_operators.size(); i++){
		if(all_operators[i]->get_parent_ID() == DUMMY_ROOT){
			num_childs_root++;
		}
	}
	if(parent_id == DUMMY_ROOT){
		num_childs_root++;
	}
	if(num_childs_root >= 2){
		throw parent_operand_exception();
	}
}

bool parent_operator_finder(std::vector<Operator*> operators , int parent_id){
	if(parent_id == DUMMY_ROOT){
		return true;
	}
	for (int i = 0; i < operators.size(); i++){
		if(operators[i]->get_ID() == parent_id){
			return true;
		}
	}
	throw parent_exception();
	return false;
}

bool parent_operand_finder(std::vector<Operand*> operands , int parent_id){
	for (int i = 0; i < operands.size(); i++){
		if(operands[i]->get_ID() == parent_id){
			throw parent_operand_exception();
			return true;
		}
	}
	return false;
}

void check_tree_shape(std::vector<Operator*> operators){
	for(int i = 0 ; i < operators.size() ; i++){
		if(!operators[i]->check_num_childs()){
			throw tree_shape_exception();
		}
	}
}

void Tree::add_operand_node(const std::size_t id, const std::size_t parent_id, const int value){
	try{ 
		parent_operand_finder(all_operands , parent_id);
	} catch(parent_operand_exception parent_ex1) {
		cerr << parent_ex1.what();
		abort();
	}

	try{ 
		parent_operator_finder(all_operators , parent_id);
	} catch(parent_exception parent_ex2) {
		cerr << parent_ex2.what();
		abort();
	}

	try{ 
		count_childs_root(parent_id);
	} catch(parent_operand_exception parent_ex3){
		cerr << parent_ex3.what();
		abort();
	}

	Operand* new_operator = new Operand(id , parent_id , value);
	all_operands.push_back(new_operator);
	parent_finder_operand_child(new_operator);
}
void Tree::add_operator_node(const std::size_t id, const std::size_t parent_id, const OperatorType type){
	try{ 
		parent_operand_finder(all_operands , parent_id);
	} catch(parent_operand_exception parent_ex2) {
		cerr << parent_ex2.what();
		abort();
	}

	try{ 
		parent_operator_finder(all_operators , parent_id);
	} catch(parent_exception parent_ex1) {
		cerr << parent_ex1.what();
		abort();
	}

	try{ 
		count_childs_root(parent_id);
	} catch(parent_operand_exception parent_ex3){
		cerr << parent_ex3.what();
		abort();
	}
	switch(type){
		case 0:
			{
				Add_Operator* new_operator = new Add_Operator(id , parent_id);
				all_operators.push_back(new_operator);
				parent_finder_operator_child(new_operator);
				break;
			}
		case 1:
			{
				Multiply_Operator* new_operator = new Multiply_Operator(id , parent_id);
				all_operators.push_back(new_operator);
				parent_finder_operator_child(new_operator);
				break;
			}		
		case 2:
			{
				Not_Operator* new_operator = new Not_Operator(id , parent_id);
				all_operators.push_back(new_operator);
				parent_finder_operator_child(new_operator);
				break;
			}
		case 3:
			{
				Median_Operator* new_operator = new Median_Operator(id , parent_id);
				all_operators.push_back(new_operator);
				parent_finder_operator_child(new_operator);
				break;
			}
	}
}

void Tree::parent_finder_operator_child(Operator* child_operator){
	for (int i = 0; i < all_operators.size() ; i++){
		if(all_operators[i]->get_ID() == child_operator->get_parent_ID()){
			all_operators[i]->add_child_operator(child_operator);
		}
	}
}

void Tree::parent_finder_operand_child(Operand* child_operand){
	for (int i = 0; i < all_operators.size() ; i++){
		if(all_operators[i]->get_ID() == child_operand->get_parent_ID()){
			all_operators[i]->add_child_operand(child_operand);
		}
	}
}
int Tree::evaluate_tree(){
	try{
		check_tree_shape(all_operators);
	} catch(tree_shape_exception tree_ex){
		cerr << tree_ex.what();
		abort();
	}
	return all_operators[0]->calculate();
}