#ifndef __MEDIAN_H__
#define __MEDIAN_H__

class Median_Operator : public Operator
{
public:
	Median_Operator(int _id , int _parent_id);
	virtual double calculate();
	virtual bool check_num_childs();
private:
};

#endif