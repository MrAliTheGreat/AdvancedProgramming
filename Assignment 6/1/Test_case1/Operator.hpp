#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "Operand.hpp"
#include <vector>

class Operator
{
public:
	Operator(int _id , int _parent_id);

	void add_child_operator(Operator* new_child_operator);
	void add_child_operand(Operand* new_child_operand);

	int get_ID(){ return id; };
	int get_parent_ID(){ return parent_id; };

	int num_all_childs();

	virtual double calculate() = 0;
	virtual bool check_num_childs() = 0;
protected:
	int id , parent_id;
	std::vector<Operator*> child_operator;
	std::vector<Operand*> child_operand;
};

#endif