#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

class Multiply_Operator : public Operator
{
public:
	Multiply_Operator(int _id , int _parent_id);
	virtual double calculate();
	virtual bool check_num_childs();
private:
};

#endif