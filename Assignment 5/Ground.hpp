#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include <string>
#include <vector>

#include "src/rsdl.hpp"
#include "Tank.hpp"
#include "Bullet.hpp"
#include "Powerup.hpp"

class Ground
{
public:
	Ground(std::string address);
	void make_ground();
	void spawn_tanks();
	void game_engine();
	void place_new_tank(std::string tank_address , int tank_pos_x , int tank_pos_y , double tank_angle);
	void place_new_bullet(int bullet_pos_x , int bullet_pos_y , double bullet_angle);
	bool contains_tank(int tank_x , int tank_y);
	bool has_hit_wall(int tank_x , int tank_y);
	void place_new_powerup(int powerup_x , int powerup_y , int type_encoded);
	void ending();
private:
	Window *window_game;
	int ground_width , ground_length;
	std::string ground_address;
	std::vector<Tank*> tanks;
	std::vector<int> wall_ranges_x_const;
	std::vector<int> wall_ranges_y_const;
	std::vector<Powerup*> all_powerups;
	std::vector<std::string> powerup_addresses;
	bool tank0_win , tank1_win;
};


#endif