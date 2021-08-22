#ifndef __OUTPUT_H__
#define __OUTPUT_H__

class Output
{
public:
	Output(int _id);
	void set_value(int new_value);

	int get_id(){ return id; };
	int get_value(){ return value; };
private:
	int id;
	int value;
};


#endif