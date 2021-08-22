#ifndef __TANK_HPP__
#define __TANK_HPP__

#include <string>
#include <vector>

#include "src/rsdl.hpp"
#include "Bullet.hpp"
#include "Powerup.hpp"

class Tank
{
public:
	Tank(int x , int y , int v , double angle , std::string name);
	int get_tank_x(){ return tank_center_x; };
	int get_tank_y(){ return tank_center_y; };
	int get_tank_velocity(){ return tank_velocity; };
	double get_tank_angle(){ return tank_angle; };
	int get_num_bullets();
	std::vector<Bullet*> get_tank_bullets(){ return tank_bullets; };
	Powerup* get_tank_power(){ return tank_power; };
	void set_velocity(int new_v);
	void add_new_bullet(Bullet* new_bullet);
	void move(Event last_event);
	bool has_any_bullet();
	void remove_old_bullet(double limit , double timer , int index);
	void set_tank_power(Powerup* new_power);
	bool is_on_powerup(int powerup_x , int powerup_y , int powerup_radius);
private:
	int tank_center_x , tank_center_y;
	int tank_velocity;
	double tank_angle;
	std::string name_tank;
	std::vector<Bullet*> tank_bullets;
	Powerup* tank_power;
};

#endif