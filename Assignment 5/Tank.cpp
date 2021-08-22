#include "Tank.hpp"
#include "src/rsdl.hpp"

#include <string>
#include <cmath>
#include <math.h>

Tank::Tank(int x , int y , int v , double angle , std::string name){
	tank_center_x = x;
	tank_center_y = y;
	tank_velocity = v;
	tank_angle = angle;
	name_tank = name;
	tank_power = new Powerup();
}

int Tank::get_num_bullets(){
	int num_regular_bullets = 0;
	for(int i = 0 ; i < tank_bullets.size() ; i++){
		if(tank_bullets[i]->get_bullet_type() == ""){
			num_regular_bullets++;
		}
	}
	return num_regular_bullets;
}

void Tank::set_velocity(int new_v){
	tank_velocity = new_v;
}

void Tank::add_new_bullet(Bullet* new_bullet){
	tank_bullets.push_back(new_bullet);
}

bool Tank::has_any_bullet(){
	if(tank_bullets.size() != 0){
		return true;
	}
	return false;
}

void Tank::remove_old_bullet(double limit , double timer , int index){
	if(tank_bullets.size() != 0 && timer >= limit){
		tank_bullets.erase(tank_bullets.begin() + index);
	}
}

void Tank::set_tank_power(Powerup* new_power){
	tank_power = new_power;
}

bool Tank::is_on_powerup(int powerup_x , int powerup_y , int powerup_radius){
	if(pow((powerup_x - tank_center_x) , 2 ) + pow((powerup_y - tank_center_y) , 2 ) < pow(powerup_radius - 5 , 2) ){
		return true;
	}
	return false;
}

void Tank::move(Event last_event){
	int dt = 5;
	if(name_tank == "Tank1"){
		switch (last_event.get_pressed_key()){
				case 'w':
					while(tank_angle >= 360){
						tank_angle -= 360;
					}
					while(tank_angle <= -360){
						tank_angle += 360;
					}

					if(tank_angle == 0){
						tank_center_x += tank_velocity * dt;
					}else if((tank_angle > 0 && tank_angle < 90) || (tank_angle > -360 && tank_angle < -270)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 90 || tank_angle == -270){
						tank_center_y += tank_velocity * dt;
					}else if((tank_angle > 90 && tank_angle < 180) || (tank_angle > -270 && tank_angle < -180)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 180 || tank_angle == -180){
						tank_center_x -= tank_velocity * dt;
					}else if((tank_angle > 180 && tank_angle < 270) || (tank_angle > -180 && tank_angle < -90)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;				
					}else if(tank_angle == 270 || tank_angle == -90){
						tank_center_y -= tank_velocity * dt;
					}else if((tank_angle > 270 && tank_angle < 360) || (tank_angle > -90 && tank_angle < 0)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}
					break;
				case 's':
					while(tank_angle >= 360){
						tank_angle -= 360;
					}
					while(tank_angle <= -360){
						tank_angle += 360;
					}

					if(tank_angle == 0){
						tank_center_x -= tank_velocity * dt;
					}else if((tank_angle > 0 && tank_angle < 90) || (tank_angle > -360 && tank_angle < -270)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 90 || tank_angle == -270){
						tank_center_y -= tank_velocity * dt;
					}else if((tank_angle > 90 && tank_angle < 180) || (tank_angle > -270 && tank_angle < -180)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 180 || tank_angle == -180){
						tank_center_x += tank_velocity * dt;
					}else if((tank_angle > 180 && tank_angle < 270) || (tank_angle > -180 && tank_angle < -90)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;				
					}else if(tank_angle == 270 || tank_angle == -90){
						tank_center_y += tank_velocity * dt;
					}else if((tank_angle > 270 && tank_angle < 360) || (tank_angle > -90 && tank_angle < 0)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}			
					break;
				case 'd':
					tank_angle += dt;
					break;
				case 'a':
					tank_angle -= dt;
					break;
		}
	}else if(name_tank == "Tank2"){
		switch (last_event.get_pressed_key()){
				case 'i':
					while(tank_angle >= 360){
						tank_angle -= 360;
					}

					while(tank_angle <= -360){
						tank_angle += 360;
					}

					if(tank_angle == 0){
						tank_center_x += tank_velocity * dt;
					}else if((tank_angle > 0 && tank_angle < 90) || (tank_angle > -360 && tank_angle < -270)){
						tank_center_x += tank_velocity * abs(cos(M_PI * abs(tank_angle) / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * abs(tank_angle) / 180)) * dt;
					}else if(tank_angle == 90 || tank_angle == -270){
						tank_center_y += tank_velocity * dt;
					}else if((tank_angle > 90 && tank_angle < 180) || (tank_angle > -270 && tank_angle < -180)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * abs(tank_angle) / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * abs(tank_angle) / 180)) * dt;
					}else if(tank_angle == 180 || tank_angle == -180){
						tank_center_x -= tank_velocity * dt;
					}else if((tank_angle > 180 && tank_angle < 270) || (tank_angle > -180 && tank_angle < -90)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * abs(tank_angle) / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * abs(tank_angle) / 180)) * dt;				
					}else if(tank_angle == 270 || tank_angle == -90){
						tank_center_y -= tank_velocity * dt;
					}else if((tank_angle > 270 && tank_angle < 360) || (tank_angle > -90 && tank_angle < 0)){
						tank_center_x += tank_velocity * abs(cos(M_PI * abs(tank_angle) / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * abs(tank_angle) / 180)) * dt;
					}
					break;
				case 'k':
					while(tank_angle >= 360){
						tank_angle -= 360;
					}
					while(tank_angle <= -360){
						tank_angle += 360;
					}

					if(tank_angle == 0){
						tank_center_x -= tank_velocity * dt;
					}else if((tank_angle > 0 && tank_angle < 90) || (tank_angle > -360 && tank_angle < -270)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 90 || tank_angle == -270){
						tank_center_y -= tank_velocity * dt;
					}else if((tank_angle > 90 && tank_angle < 180) || (tank_angle > -270 && tank_angle < -180)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y -= tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}else if(tank_angle == 180 || tank_angle == -180){
						tank_center_x += tank_velocity * dt;
					}else if((tank_angle > 180 && tank_angle < 270) || (tank_angle > -180 && tank_angle < -90)){
						tank_center_x += tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;				
					}else if(tank_angle == 270 || tank_angle == -90){
						tank_center_y += tank_velocity * dt;
					}else if((tank_angle > 270 && tank_angle < 360) || (tank_angle > -90 && tank_angle < 0)){
						tank_center_x -= tank_velocity * abs(cos(M_PI * tank_angle / 180)) * dt;
						tank_center_y += tank_velocity * abs(sin(M_PI * tank_angle / 180)) * dt;
					}				
					break;
				case 'l':
					tank_angle += dt;
					break;
				case 'j':
					tank_angle -= dt;
					break;
		}
	}
	
}