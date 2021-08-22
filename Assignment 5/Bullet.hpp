#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <string>
#include <vector>

#include "src/rsdl.hpp"

class Bullet
{
public:
	Bullet(int x , int y , int v , double angle);
	Bullet(int x , int y , int v , double angle , std::string type);
	int get_bullet_x(){ return bullet_x; };
	int get_bullet_y(){ return bullet_y; };
	int get_bullet_velocity(){ return bullet_velocity; };
	double get_bullet_angle(){ return bullet_angle; };
	double get_timer(){ return time_alive; };
	std::string get_bullet_type(){ return bullet_type; };
	void set_timer(double timer);
	void move_bullet();
	void reflect(int width , int length , std::vector<int> wall_ranges_x_const , std::vector<int> wall_ranges_y_const);
	int has_hit_tank(int tank0_x , int tank0_y , int tank1_x , int tank1_y , int tank_radius);

private:
	int bullet_x , bullet_y;
	int bullet_velocity;
	double bullet_angle;
	double time_alive;
	std::string bullet_type;
};

#endif