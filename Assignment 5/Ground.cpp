#include "Ground.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TANK_LENGTH 100
#define TANK_WIDTH 100
#define SHIELD_ADDRESS "Assets/Shield-Pickup.png"
#define SHOTGUN_ADDRESS "Assets/Shotgun-Pickup.png"
#define DOUBLEBARREL_ADDRESS "Assets/DoubleBarrel-Pickup.png"
#define TANK1_ADDRESS "Assets/Tank1-Normal.png"
#define TANK2_ADDRESS "Assets/Tank2-Normal.png"
#define TANK1_WIN_MESSAGE "Green Tank Won!"
#define TANK2_WIN_MESSAGE "Red Tank Won!"
#define DRAW_MESSAGE "It's a Draw!"
#define FONT_ADDRESS "Assets/TankTrouble.ttf"
#define EXIT_MESSAGE "Press Any Key To Quit"
#define SHIELD_TANK1_ADDRESS "Assets/Tank1-Shield.png"
#define SHOTGUN_TANK1_ADDRESS "Assets/Tank1-Shotgun.png"
#define DOUBLEBARREL_TANK1_ADDRESS "Assets/Tank1-DoubleBarrel.png"
#define SHIELD_TANK2_ADDRESS "Assets/Tank2-Shield.png"
#define SHOTGUN_TANK2_ADDRESS "Assets/Tank2-Shotgun.png"
#define DOUBLEBARREL_TANK2_ADDRESS "Assets/Tank2-DoubleBarrel.png"
#define SHIELD "shield"
#define SHOTGUN "shotgun"
#define DOUBLEBARREL "doubleBarrel"

std::vector<std::string > windows_info_generater(std::string ground_info_address){
	std::ifstream ground_info(ground_info_address);

	std::string line , number;
	std::stringstream ss_line;
	std::vector<std::string> info;
	int index = 0;

	while(getline(ground_info , line)){
		ss_line.str(line);
		ss_line.clear();
		while(getline(ss_line , number , ' ')){
			info.push_back(number);
		}
		index++;
	}
	return info;
}

std::vector<std::string> generate_box_info(std::vector<std::string> ground_info){
	std::vector<std::string> box_info;
	for (int i = 2; i < ground_info.size() - 4; i++){
		box_info.push_back(ground_info[i]);
	}
	return box_info;
}

std::vector<int> generate_windows_size(std::string address){
	std::vector<int> window_sizes;
	std::vector<std::string> ground_info = windows_info_generater(address);
	window_sizes.push_back(3 * TANK_WIDTH * std::stoi(ground_info[1]));
	window_sizes.push_back(3 * TANK_LENGTH * std::stoi(ground_info[0]));
	return window_sizes;
}

Ground::Ground(std::string address){
	ground_address = address;
	ground_width = generate_windows_size(address)[0];
	ground_length = generate_windows_size(address)[1];
	powerup_addresses.push_back(SHIELD_ADDRESS);
	powerup_addresses.push_back(SHOTGUN_ADDRESS);
	powerup_addresses.push_back(DOUBLEBARREL_ADDRESS);
	window_game = new Window(ground_width , ground_length , "Tank Game");
	tank0_win = false;
	tank1_win = false;
}

void Ground::make_ground(){
	std::vector<std::string> ground_info = windows_info_generater(ground_address);

	std::vector<std::string> box_info = generate_box_info(ground_info);

	window_game->fill_rect(Rectangle(0 , 0 , ground_width , ground_length) , WHITE);
	window_game->fill_rect(Rectangle(ground_width - 15 , 5 , 10 , ground_length - 10) , BLACK);
	window_game->fill_rect(Rectangle(5 , ground_length - 15 , ground_width - 10 , 10) , BLACK);

	for (int i = 0; i <= box_info.size(); i++)
	{
		for(int j = 0 ; j < box_info[i].length() ; j++){
			switch(box_info[i][j] - '0'){
				case 0 :
					continue;
				case 1 :
					if(i == 0){
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH + 5 , 3 * TANK_WIDTH , 10) , BLACK);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH + 5);
					}else{
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 3 * TANK_WIDTH , 10) , BLACK);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH);
					}
					break;
				case 2 :
					if(j == 0){
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH + 5 , i * 3 * TANK_LENGTH , 10 , 3 * TANK_LENGTH ) , BLACK);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH + 5);	
					}else{
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 10 , 3 * TANK_LENGTH) , BLACK);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH);
					}
					break;
				case 3 :
					if(i == 0 && j == 0){
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH + 5 , i * 3 * TANK_LENGTH + 5 , 10 , 3 * TANK_LENGTH - 5) , BLACK);
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH + 5 , i * 3 * TANK_LENGTH + 5 , 3 * TANK_WIDTH - 5 , 10) , BLACK);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 5);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH + 5);

						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 5);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH + 5);						
					}else if(i == 0 && j != 0){
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH + 5 , 3 * TANK_WIDTH , 10) , BLACK);
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 10 , 3 * TANK_LENGTH) , BLACK);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH);

						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH + 5);							
					}else if(i != 0 && j == 0){
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH + 5 , i * 3 * TANK_LENGTH , 10 , 3 * TANK_LENGTH) , BLACK);
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 3 * TANK_WIDTH , 10) , BLACK);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH + 5);

						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH);	
					}else{
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 3 * TANK_WIDTH , 10) , BLACK);
						window_game->fill_rect(Rectangle(j * 3 * TANK_WIDTH , i * 3 * TANK_LENGTH , 10 , 3 * TANK_LENGTH) , BLACK);

						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(i * 3 * TANK_LENGTH + 3 * TANK_LENGTH);
						wall_ranges_x_const.push_back(j * 3 * TANK_WIDTH);

						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(j * 3 * TANK_WIDTH + 3 * TANK_WIDTH);
						wall_ranges_y_const.push_back(i * 3 * TANK_LENGTH);
					}
					break;
			}	
		}
	}
	window_game->update_screen();
}

bool Ground::contains_tank(int tank_x , int tank_y){
	if((tank_x + TANK_WIDTH / 2) < ground_width && (tank_x - TANK_WIDTH / 2) > 0 && (tank_y + TANK_LENGTH / 2) < ground_length && (tank_y - TANK_LENGTH / 2) > 0){
		return true;
	}
	return false;
}


bool Ground::has_hit_wall(int tank_x , int tank_y){
	for(int i = 0 ; i < wall_ranges_x_const.size() ; i += 3){
		if(tank_x >= wall_ranges_x_const[i + 2] - 20 &&  tank_x <= wall_ranges_x_const[i + 2] + 20){
			if(tank_y > wall_ranges_x_const[i] && tank_y < wall_ranges_x_const[i + 1]){
				return true;
			}
		}
	}

	for(int i = 0 ; i < wall_ranges_y_const.size() ; i += 3){
		if(tank_y >= wall_ranges_y_const[i + 2] - 20 && tank_y <= wall_ranges_y_const[i + 2] + 20){
			if(tank_x > wall_ranges_y_const[i] && tank_x < wall_ranges_y_const[i + 1]){
				return true;
			}
		}
	}
	return false;
}

void Ground::spawn_tanks(){
	tanks.push_back(new Tank(1.5 * TANK_WIDTH , 1.5 * TANK_WIDTH , 4 , 0 , "Tank1"));
	tanks.push_back(new Tank(ground_width - 1.5 * TANK_WIDTH , ground_length - 1.5 * TANK_LENGTH , 4 , 0 , "Tank2"));
	window_game->draw_img(TANK1_ADDRESS, Rectangle(TANK_WIDTH , TANK_LENGTH , 100 , 100));
	window_game->draw_img(TANK2_ADDRESS, Rectangle(ground_width - 2 * TANK_WIDTH , ground_length - 2 * TANK_LENGTH , 100 , 100));
	window_game->update_screen();
}

void Ground::place_new_tank(std::string tank_address , int tank_pos_x , int tank_pos_y , double tank_angle){
	window_game->draw_img(tank_address, Rectangle(tank_pos_x - TANK_WIDTH / 2 , tank_pos_y - TANK_LENGTH / 2 , 100 , 100) , NULL_RECT , tank_angle);
}

void Ground::place_new_bullet(int bullet_pos_x , int bullet_pos_y , double bullet_angle){
	window_game->fill_circle(Point(bullet_pos_x, bullet_pos_y) , 10 , BLACK);
}

void Ground::place_new_powerup(int powerup_x , int powerup_y , int type_encoded){
	window_game->draw_img(powerup_addresses[type_encoded] , Rectangle(powerup_x - TANK_WIDTH / 2 , powerup_y - TANK_LENGTH / 2 , 80 , 80) , NULL_RECT , 0);
}

bool is_control(std::vector<char> control_vec , Event input_event){
	for (int i = 0 ; i < control_vec.size() ; i++){
		if(input_event.get_pressed_key() == control_vec[i]){
			return true;
		}
	}
	return false;
}

bool tanks_collided(int tank0_x , int tank0_y , int tank1_x , int tank1_y){
	if(pow((tank1_x - tank0_x) , 2 ) + pow((tank1_y - tank0_y) , 2 ) < pow((TANK_WIDTH / 2) + 15 , 2)){
		return true;
	}
	return false;
}

void Ground::game_engine(){
	srand(time(NULL));
	Event previous_event1 , help_event1 , previous_event2 , help_event2;
	std::vector<char> tank1_controls = {'w' , 'a' , 's' , 'd'};
	std::vector<char> tank2_controls = {'i' , 'j' , 'k' , 'l'};
	bool flag_tank1 = false;
	bool flag_tank2 = false;
	bool play_game = true;
	int powerup_timer = rand() % 75;
	int game_timer = 0;
	int num_pressed_q_shotgun = 0;
	int num_pressed_q_doubleBarrel = 0;
	int num_pressed_u_shotgun = 0;
	int num_pressed_u_doubleBarrel = 0;

	while(play_game){
		Event event1 = window_game->poll_for_event();
		Event event2 = event1;

		if(event1.get_pressed_key() == 'z'){
			break;
		}

		if(event1.get_type() == Event::KEY_PRESS && event1.get_pressed_key() == 'q'){
			if(tanks[0]->get_num_bullets() < 5 && (tanks[0]->get_tank_power()->get_type() != SHOTGUN && tanks[0]->get_tank_power()->get_type() != DOUBLEBARREL) ){
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 10 , tanks[0]->get_tank_angle()));
			}else if(tanks[0]->get_tank_power()->get_type() == SHOTGUN && num_pressed_q_shotgun < 3){
				num_pressed_q_shotgun++;
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 13 , tanks[0]->get_tank_angle() - 20 , SHOTGUN) );
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 13 , tanks[0]->get_tank_angle() - 10 , SHOTGUN) );
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 13 , tanks[0]->get_tank_angle() , SHOTGUN) );
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 13 , tanks[0]->get_tank_angle() + 10 , SHOTGUN) );
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 13 , tanks[0]->get_tank_angle() + 20 , SHOTGUN) );
			}else if(tanks[0]->get_tank_power()->get_type() == DOUBLEBARREL){
				num_pressed_q_doubleBarrel++;
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 10 , tanks[0]->get_tank_angle() + 2 , DOUBLEBARREL) );
				tanks[0]->add_new_bullet(new Bullet(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , 10 , tanks[0]->get_tank_angle() - 2, DOUBLEBARREL) );
			}

			if(num_pressed_q_shotgun == 3){
				tanks[0]->set_tank_power(new Powerup());
				num_pressed_q_shotgun = 0;
			}

			if(num_pressed_q_doubleBarrel == 5){
				tanks[0]->set_tank_power(new Powerup());
				num_pressed_q_doubleBarrel = 0;
			}
		}

		if(event2.get_type() == Event::KEY_PRESS && event2.get_pressed_key() == 'u'){
			if(tanks[1]->get_num_bullets() < 5 && (tanks[1]->get_tank_power()->get_type() != SHOTGUN && tanks[1]->get_tank_power()->get_type() != DOUBLEBARREL) ){
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 10 , tanks[1]->get_tank_angle()));
			}else if(tanks[1]->get_tank_power()->get_type() == SHOTGUN && num_pressed_u_shotgun < 3){
				num_pressed_u_shotgun++;
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 13 , tanks[1]->get_tank_angle() - 20 , SHOTGUN) );
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 13 , tanks[1]->get_tank_angle() - 10 , SHOTGUN) );
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 13 , tanks[1]->get_tank_angle() , SHOTGUN) );
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 13 , tanks[1]->get_tank_angle() + 10 , SHOTGUN) );
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 13 , tanks[1]->get_tank_angle() + 20 , SHOTGUN) );
			}else if(tanks[1]->get_tank_power()->get_type() == DOUBLEBARREL){
				num_pressed_u_doubleBarrel++;
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 10 , tanks[1]->get_tank_angle() + 2 , DOUBLEBARREL) );
				tanks[1]->add_new_bullet(new Bullet(tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , 10 , tanks[1]->get_tank_angle() - 2, DOUBLEBARREL) );
			}

			if(num_pressed_u_shotgun == 3){
				tanks[1]->set_tank_power(new Powerup());
				num_pressed_u_shotgun = 0;
			}

			if(num_pressed_u_doubleBarrel == 5){
				tanks[1]->set_tank_power(new Powerup());
				num_pressed_u_doubleBarrel = 0;
			}
		}

		if(game_timer >= powerup_timer && all_powerups.size() < 3){
			int powerup_x = rand() % (ground_width - 100) + 50;
			int powerup_y = rand() % (ground_length - 100) + 50;
			int type_encoded = rand() % 3;
			all_powerups.push_back(new Powerup(powerup_x , powerup_y , type_encoded) );			
			game_timer = 0;
			powerup_timer = rand() % 75;
		}

		window_game->clear();
		this->make_ground();
		this->make_ground();

		for(int i = 0 ; i < all_powerups.size() ; i++){
			this->place_new_powerup(all_powerups[i]->get_powerup_x() , all_powerups[i]->get_powerup_y() , all_powerups[i]->get_type_encoded());
		}

		if(tanks[0]->has_any_bullet()){
			for(int i = 0 ; i < tanks[0]->get_tank_bullets().size() ; i++){
				tanks[0]->get_tank_bullets()[i]->move_bullet();
				tanks[0]->get_tank_bullets()[i]->reflect(ground_width , ground_length , wall_ranges_x_const , wall_ranges_y_const);
				tanks[0]->get_tank_bullets()[i]->set_timer(tanks[0]->get_tank_bullets()[i]->get_timer() + 0.01);
				this->place_new_bullet(tanks[0]->get_tank_bullets()[i]->get_bullet_x() , tanks[0]->get_tank_bullets()[i]->get_bullet_y() , tanks[0]->get_tank_bullets()[i]->get_bullet_angle());				
				if(tanks[0]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 0 && tanks[0]->get_tank_power()->get_type() != SHIELD){
					std::cout << TANK2_WIN_MESSAGE << "\n";
					tank1_win = true;
					play_game = false;
				}else if(tanks[0]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 1 && tanks[1]->get_tank_power()->get_type() != SHIELD){
					std::cout << TANK1_WIN_MESSAGE << "\n";
					tank0_win = true;
					play_game = false;
				}else if(tanks[0]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 0 && tanks[0]->get_tank_power()->get_type() == SHIELD){
					tanks[0]->remove_old_bullet(0.5 , 0.5 , i);
				}else if(tanks[0]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 1 && tanks[1]->get_tank_power()->get_type() == SHIELD){
					tanks[0]->remove_old_bullet(0.5 , 0.5 , i);
				}else{
					if(tanks[0]->get_tank_bullets()[i]->get_bullet_type() == SHOTGUN){
						tanks[0]->remove_old_bullet(0.15 , tanks[0]->get_tank_bullets()[i]->get_timer() , i);
					}else{
						tanks[0]->remove_old_bullet(0.5 , tanks[0]->get_tank_bullets()[i]->get_timer() , i);
					}
				}
			}
		}
		if(tanks[1]->has_any_bullet()){
			for(int i = 0 ; i < tanks[1]->get_tank_bullets().size() ; i++){
				tanks[1]->get_tank_bullets()[i]->move_bullet();
				tanks[1]->get_tank_bullets()[i]->reflect(ground_width , ground_length , wall_ranges_x_const , wall_ranges_y_const);
				tanks[1]->get_tank_bullets()[i]->set_timer(tanks[1]->get_tank_bullets()[i]->get_timer() + 0.01);
				this->place_new_bullet(tanks[1]->get_tank_bullets()[i]->get_bullet_x() , tanks[1]->get_tank_bullets()[i]->get_bullet_y() , tanks[1]->get_tank_bullets()[i]->get_bullet_angle());
				if(tanks[1]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 0 && tanks[0]->get_tank_power()->get_type() != SHIELD){
					std::cout << TANK2_WIN_MESSAGE << "\n";
					tank1_win = true;
					play_game = false;
				}else if(tanks[1]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 1 && tanks[1]->get_tank_power()->get_type() != SHIELD){
					std::cout << TANK1_WIN_MESSAGE << "\n";
					tank0_win = true;
					play_game = false;
				}else if(tanks[1]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 0 && tanks[0]->get_tank_power()->get_type() == SHIELD){
					tanks[1]->remove_old_bullet(0.5 , 0.5 , i);
				}else if(tanks[1]->get_tank_bullets()[i]->has_hit_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , TANK_LENGTH / 2) == 1 && tanks[1]->get_tank_power()->get_type() == SHIELD){
					tanks[1]->remove_old_bullet(0.5 , 0.5 , i);
				}else{
					if(tanks[1]->get_tank_bullets()[i]->get_bullet_type() == SHOTGUN){
						tanks[1]->remove_old_bullet(0.15 , tanks[1]->get_tank_bullets()[i]->get_timer() , i);
					}else{
						tanks[1]->remove_old_bullet(0.5 , tanks[1]->get_tank_bullets()[i]->get_timer() , i);
					}
				}
			}
		}

		help_event1 = event1;
		help_event2 = event2;

		if(previous_event1.get_type() == Event::KEY_PRESS || is_control(tank2_controls , help_event1)){
			event1 = previous_event1;
		}	

		if(help_event1.get_type() == Event::KEY_PRESS && help_event1.get_pressed_key() != previous_event1.get_pressed_key() && is_control(tank1_controls , help_event1)){
			event1 = help_event1;
			tanks[0]->set_velocity(4);
			flag_tank1 = true;

			Tank temp_tank1 = *tanks[0];
			temp_tank1.move(event1);
			temp_tank1.set_velocity(20);
			if(!contains_tank(temp_tank1.get_tank_x() , temp_tank1.get_tank_y()) || has_hit_wall(temp_tank1.get_tank_x() , temp_tank1.get_tank_y()) || tanks_collided(temp_tank1.get_tank_x() , temp_tank1.get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() ) ){
				if(event1.get_pressed_key() == 'd' || event1.get_pressed_key() == 'a'){
					flag_tank1 = true;
				}else{
					flag_tank1 = false;
				}
			}
		}

		if(previous_event2.get_type() == Event::KEY_PRESS || is_control(tank1_controls , help_event2)){
			event2 = previous_event2;
		}

		if(help_event2.get_type() == Event::KEY_PRESS && help_event2.get_pressed_key() != previous_event2.get_pressed_key() && is_control(tank2_controls , help_event2)){
			event2 = help_event2;
			tanks[1]->set_velocity(4);
			flag_tank2 = true;

			Tank temp_tank2 = *tanks[1];
			temp_tank2.move(event2);
			temp_tank2.set_velocity(20);
			if(!contains_tank(temp_tank2.get_tank_x() , temp_tank2.get_tank_y()) || has_hit_wall(temp_tank2.get_tank_x() , temp_tank2.get_tank_y()) || tanks_collided(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , temp_tank2.get_tank_x() , temp_tank2.get_tank_y() ) ){
				if(event2.get_pressed_key() == 'j' || event2.get_pressed_key() == 'l'){
					flag_tank2 = true;
				}else{
					flag_tank2 = false;
				}
			}			
		}		

		if(event1.get_type() == Event::KEY_PRESS){
			if(contains_tank(tanks[0]->get_tank_x() , tanks[0]->get_tank_y()) && !has_hit_wall(tanks[0]->get_tank_x() , tanks[0]->get_tank_y()) && !tanks_collided(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() ) ){
				tanks[0]->move(event1);
				flag_tank1 = false;
			}else{
				if(flag_tank1){
					tanks[0]->move(event1);
				}else{
					tanks[0]->set_velocity(0);
				}
			}
			previous_event1 = event1;
		}

		if(event2.get_type() == Event::KEY_PRESS){
			if(contains_tank(tanks[1]->get_tank_x() , tanks[1]->get_tank_y()) && !has_hit_wall(tanks[1]->get_tank_x() , tanks[1]->get_tank_y()) && !tanks_collided(tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() ) ){
				tanks[1]->move(event2);
				flag_tank2 = false;		
			}else{
				if(flag_tank2){
					tanks[1]->move(event2);
				}else{
					tanks[1]->set_velocity(0);
				}
			}
			previous_event2 = event2;
		}

		for(int i = 0 ; i < all_powerups.size() ; i++){
			if(tanks[0]->is_on_powerup(all_powerups[i]->get_powerup_x() , all_powerups[i]->get_powerup_y() , 40) ){
				all_powerups[i]->set_time_in_use(50);
				tanks[0]->set_tank_power(all_powerups[i]);
				all_powerups.erase(all_powerups.begin() + i);
			}

			if(tanks[1]->is_on_powerup(all_powerups[i]->get_powerup_x() , all_powerups[i]->get_powerup_y() , 40) ){
				all_powerups[i]->set_time_in_use(50);
				tanks[1]->set_tank_power(all_powerups[i]);
				all_powerups.erase(all_powerups.begin() + i);
			}
		}

		if(tanks[0]->get_tank_power()->get_type() == ""){
			this->place_new_tank(TANK1_ADDRESS , tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[0]->get_tank_angle());
		
		}else if(tanks[0]->get_tank_power()->get_type() == SHIELD){
			this->place_new_tank(SHIELD_TANK1_ADDRESS , tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[0]->get_tank_angle());
			tanks[0]->get_tank_power()->set_time_in_use(tanks[0]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[0]->get_tank_power()->get_time_in_use() == 0){
				tanks[0]->set_tank_power(new Powerup());
			}
			
		}else if(tanks[0]->get_tank_power()->get_type() == SHOTGUN){
			this->place_new_tank(SHOTGUN_TANK1_ADDRESS , tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[0]->get_tank_angle());
			tanks[0]->get_tank_power()->set_time_in_use(tanks[0]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[0]->get_tank_power()->get_time_in_use() == 0){
				tanks[0]->set_tank_power(new Powerup());
			}

		}else if(tanks[0]->get_tank_power()->get_type() == DOUBLEBARREL){
			this->place_new_tank(DOUBLEBARREL_TANK1_ADDRESS , tanks[0]->get_tank_x() , tanks[0]->get_tank_y() , tanks[0]->get_tank_angle());
			tanks[0]->get_tank_power()->set_time_in_use(tanks[0]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[0]->get_tank_power()->get_time_in_use() == 0){
				tanks[0]->set_tank_power(new Powerup());
			}		
		}

		if(tanks[1]->get_tank_power()->get_type() == ""){
			this->place_new_tank(TANK2_ADDRESS , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , tanks[1]->get_tank_angle());
		
		}else if(tanks[1]->get_tank_power()->get_type() == SHIELD){
			this->place_new_tank(SHIELD_TANK2_ADDRESS , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , tanks[1]->get_tank_angle());
			tanks[1]->get_tank_power()->set_time_in_use(tanks[1]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[1]->get_tank_power()->get_time_in_use() == 0){
				tanks[1]->set_tank_power(new Powerup());
			}
			
		}else if(tanks[1]->get_tank_power()->get_type() == SHOTGUN){
			this->place_new_tank(SHOTGUN_TANK2_ADDRESS , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , tanks[1]->get_tank_angle());
			tanks[1]->get_tank_power()->set_time_in_use(tanks[1]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[1]->get_tank_power()->get_time_in_use() == 0){
				tanks[1]->set_tank_power(new Powerup());
			}

		}else if(tanks[1]->get_tank_power()->get_type() == DOUBLEBARREL){
			this->place_new_tank(DOUBLEBARREL_TANK2_ADDRESS , tanks[1]->get_tank_x() , tanks[1]->get_tank_y() , tanks[1]->get_tank_angle());
			tanks[1]->get_tank_power()->set_time_in_use(tanks[1]->get_tank_power()->get_time_in_use() - 1);
			if(tanks[1]->get_tank_power()->get_time_in_use() == 0){
				tanks[1]->set_tank_power(new Powerup());
			}		
		}

		window_game->update_screen();
		delay(150);
		game_timer++;
	}
}

void Ground::ending(){
	delete window_game;
	Window* window_end = new Window(800 , 500 , "Game Over");
	if(tank0_win){
		window_end->show_text(TANK1_WIN_MESSAGE, Point(145, 150), GREEN, FONT_ADDRESS, 50);
	}else if(tank1_win){
		window_end->show_text(TANK2_WIN_MESSAGE, Point(180, 150), GREEN, FONT_ADDRESS, 50);
	}else{
		window_end->show_text(DRAW_MESSAGE, Point(180, 150), YELLOW, FONT_ADDRESS, 50);
	}
	window_end->show_text(EXIT_MESSAGE, Point(140, 300), RED, FONT_ADDRESS, 40);
	window_end->update_screen();
	delay(100);

	while(true){
		if(window_end->poll_for_event().get_type() == Event::KEY_PRESS){
			break;
		}
	}
}