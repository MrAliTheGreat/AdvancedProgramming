#ifndef __NOT_H__
#define __NOT_H__

class Not_Operator : public Operator
{
public:
	Not_Operator(int _id , int _parent_id);
	virtual double calculate();
	virtual bool check_num_childs();
private:
};

#endif