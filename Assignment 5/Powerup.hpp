#ifndef __POWERUP_HPP__
#define __POWERUP_HPP__

#include <string>
#include <vector>

#include "src/rsdl.hpp"

class Powerup
{
public:
	Powerup(int x , int y , int _type_encoded);
	Powerup();
	int get_powerup_x(){ return powerup_x; };
	int get_powerup_y(){ return powerup_y; };
	int get_type_encoded(){ return type_encoded; };
	double get_time_in_use(){ return time_in_use; };
	std::string get_type(){ return type; };
	void set_time_in_use(double timer);
private:
	int powerup_x , powerup_y;
	int type_encoded;
	std::string type;
	double time_in_use;
};

#endif