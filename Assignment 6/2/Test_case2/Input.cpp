#include "Input.hpp"

Input::Input(int _id){
	id = _id;
	value = -1;
}

void Input::set_value(int new_value){ 
	value = new_value;
}

void Input::set_id(int new_id){ 
	id = new_id;
}