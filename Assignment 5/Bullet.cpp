#include "Bullet.hpp"
#include "src/rsdl.hpp"

#include <string>
#include <iostream>
#include <cmath>
#include <math.h>

Bullet::Bullet(int x , int y , int v , double angle){
	bullet_x = x;
	bullet_y = y;
	bullet_velocity = v;
	bullet_angle = angle;
	time_alive = 0;
}

Bullet::Bullet(int x , int y , int v , double angle , std::string type){
	bullet_x = x;
	bullet_y = y;
	bullet_velocity = v;
	bullet_angle = angle;
	time_alive = 0;
	bullet_type = type;	
}

void Bullet::set_timer(double timer){
	time_alive = timer;
}

void Bullet::move_bullet(){
	int dt = 5;
	while(bullet_angle >= 360){
		bullet_angle -= 360;
	}
	while(bullet_angle <= -360){
		bullet_angle += 360;
	}

	if(bullet_angle == 0){
		bullet_x += bullet_velocity * dt;
	}else if((bullet_angle > 0 && bullet_angle < 90) || (bullet_angle > -360 && bullet_angle < -270)){
		bullet_x += bullet_velocity * abs(cos(M_PI * bullet_angle / 180)) * dt;
		bullet_y += bullet_velocity * abs(sin(M_PI * bullet_angle / 180)) * dt;
	}else if(bullet_angle == 90 || bullet_angle == -270){
		bullet_y += bullet_velocity * dt;
	}else if((bullet_angle > 90 && bullet_angle < 180) || (bullet_angle > -270 && bullet_angle < -180)){
		bullet_x -= bullet_velocity * abs(cos(M_PI * bullet_angle / 180)) * dt;
		bullet_y += bullet_velocity * abs(sin(M_PI * bullet_angle / 180)) * dt;
	}else if(bullet_angle == 180 || bullet_angle == -180){
		bullet_x -= bullet_velocity * dt;
	}else if((bullet_angle > 180 && bullet_angle < 270) || (bullet_angle > -180 && bullet_angle < -90)){
		bullet_x -= bullet_velocity * abs(cos(M_PI * bullet_angle / 180)) * dt;
		bullet_y -= bullet_velocity * abs(sin(M_PI * bullet_angle / 180)) * dt;				
	}else if(bullet_angle == 270 || bullet_angle == -90){
		bullet_y -= bullet_velocity * dt;
	}else if((bullet_angle > 270 && bullet_angle < 360) || (bullet_angle > -90 && bullet_angle < 0)){
		bullet_x += bullet_velocity * abs(cos(M_PI * bullet_angle / 180)) * dt;
		bullet_y -= bullet_velocity * abs(sin(M_PI * bullet_angle / 180)) * dt;
	}
}

int has_hit_wall_coded(int bullet_x , int bullet_y , int width , int length , std::vector<int> wall_ranges_x_const , std::vector<int> wall_ranges_y_const){
	for(int i = 0 ; i < wall_ranges_x_const.size() ; i += 3){
		if(bullet_x >= wall_ranges_x_const[i + 2] - 20 &&  bullet_x <= wall_ranges_x_const[i + 2] + 20){
			if(bullet_y > wall_ranges_x_const[i] && bullet_y < wall_ranges_x_const[i + 1]){
				return 1;
			}
		}
	}

	for(int i = 0 ; i < wall_ranges_y_const.size() ; i += 3){
		if(bullet_y >= wall_ranges_y_const[i + 2] - 20 && bullet_y <= wall_ranges_y_const[i + 2] + 20){
			if(bullet_x > wall_ranges_y_const[i] && bullet_x < wall_ranges_y_const[i + 1]){
				return 2;
			}
		}
	}

	if((bullet_x + 18) >= width){
		return 3;
	}

	if((bullet_y + 18) >= length){
		return 4;
	}

	if((bullet_x + 18) <= 0){
		return 5;
	}

	if((bullet_y + 18) <= 0){
		return 6;
	}

	return -1;
}

void Bullet::reflect(int width , int length , std::vector<int> wall_ranges_x_const , std::vector<int> wall_ranges_y_const){
	int hit_code = has_hit_wall_coded(bullet_x , bullet_y , width , length , wall_ranges_x_const , wall_ranges_y_const);
	if(hit_code != -1){
		while(bullet_angle >= 360){
			bullet_angle -= 360;
		}
		while(bullet_angle <= -360){
			bullet_angle += 360;
		}
		if(bullet_angle == 0){
			bullet_angle = 180;
		}else if(bullet_angle == 90 || bullet_angle == -270){
			bullet_angle = 270;
		}else if(bullet_angle == 180 || bullet_angle == -180){
			bullet_angle = 0;
		}else if(bullet_angle == 270 || bullet_angle == -90){
			bullet_angle = 90;
		}else if((bullet_angle > 0 && bullet_angle < 90) || (bullet_angle > -360 && bullet_angle < -270)){
			if(hit_code == 3 || hit_code == 1 || hit_code == 5){
				bullet_angle = 180 - bullet_angle;
			}else if(hit_code == 4 || hit_code == 2 || hit_code == 6){
				bullet_angle = - bullet_angle;
			}
		}else if((bullet_angle > 90 && bullet_angle < 180) || (bullet_angle > -270 && bullet_angle < -180)){
			if(hit_code == 4 || hit_code == 2 || hit_code == 6){
				bullet_angle = 360 - bullet_angle;
			}else if(hit_code == 1 || hit_code == 3 || hit_code == 5){
				bullet_angle = 180 - bullet_angle;
			}
		}else if((bullet_angle > 180 && bullet_angle < 270) || (bullet_angle > -180 && bullet_angle < -90)){
			if(hit_code == 1 || hit_code == 3 || hit_code == 5){
				bullet_angle = 540 - bullet_angle;
			}else if(hit_code == 2 || hit_code == 4 || hit_code == 6){
				bullet_angle = 360 - bullet_angle;
			}				
		}else if((bullet_angle > 270 && bullet_angle < 360) || (bullet_angle > -90 && bullet_angle < 0)){
			if(hit_code == 3 || hit_code == 1 || hit_code == 5){
				bullet_angle = 540 - bullet_angle;
			}else if(hit_code == 2 || hit_code == 4 || hit_code == 6){
				bullet_angle = 360 - bullet_angle;
			}
		}
	}

}

int Bullet::has_hit_tank(int tank0_x , int tank0_y , int tank1_x , int tank1_y , int tank_radius){
	if(pow((bullet_x - tank0_x) , 2 ) + pow((bullet_y - tank0_y) , 2 ) < pow(tank_radius - 2 , 2) ){
		return 0;
	}
	if(pow((bullet_x - tank1_x) , 2 ) + pow((bullet_y - tank1_y) , 2 ) < pow(tank_radius - 2 , 2) ){
		return 1;
	}
	return -1;
}