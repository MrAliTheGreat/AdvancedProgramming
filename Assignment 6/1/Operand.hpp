#ifndef __OPERAND_H__
#define __OPERAND_H__

class Operand
{
public:
	Operand(int _id , int _parent_id , int _value);
	int get_ID(){ return id; };
	int get_parent_ID(){ return parent_id; };
	double calculate();
private:
	int id , parent_id;
	int value;
};

#endif