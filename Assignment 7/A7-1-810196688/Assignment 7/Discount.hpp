#ifndef __DISCOUNT_H__
#define __DISCOUNT_H__

#include <string>

class Discount
{
public:
	Discount(std::string _code , int _percentage);
	std::string get_code(){ return code; };
	int get_percentage(){ return percentage; };
private:
	std::string code;
	int percentage;
};

#endif