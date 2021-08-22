#include "Powerup.hpp"
#include "src/rsdl.hpp"

#include <string>

Powerup::Powerup(int x , int y , int _type_encoded){
	powerup_x = x;
	powerup_y = y;
	time_in_use = 0;
	type_encoded = _type_encoded;
	if(_type_encoded == 0){
		type = "shield";
	}else if(_type_encoded == 1){
		type = "shotgun";
	}else if(_type_encoded == 2){
		type = "doubleBarrel";
	}
}

Powerup::Powerup(){
	time_in_use = 0;
	type = "";
}

void Powerup::set_time_in_use(double timer){
	time_in_use = timer;
}

