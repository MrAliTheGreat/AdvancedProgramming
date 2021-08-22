#ifndef __INPUT_H__
#define __INPUT_H__

class Input
{
public:
	Input(int _id);
	void set_value(int new_value);
	void set_id(int new_id);
	int get_id(){ return id; };
	int get_value(){ return value; };
private:
	int id;
	int value;
};


#endif