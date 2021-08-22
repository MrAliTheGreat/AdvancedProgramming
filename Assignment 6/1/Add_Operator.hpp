#ifndef __ADD_H__
#define __ADD_H__

class Add_Operator : public Operator
{
public:
	Add_Operator(int _id , int _parent_id);
	virtual double calculate();
	virtual bool check_num_childs();
private:
};

#endif