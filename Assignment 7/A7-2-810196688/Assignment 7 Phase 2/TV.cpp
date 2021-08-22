#include "TV.hpp"
#include <iostream>

TV::TV(std::string _name , int _id , int _display_size , std::string _screen_type , std::string _resolution
		 , int _has_3D , int _has_HDR) : Product(_name , _id){

	display_size = _display_size;
	screen_type = _screen_type;
	resolution = _resolution;
	has_3D = _has_3D;
	has_HDR = _has_HDR;
}

void TV::get_product_info(){
	std::cout << "Screen Size: " << display_size << "\n";
	std::cout << "Screen Type: " << screen_type << "\n";
	std::cout << "Resolution: " << resolution << "\n";
	std::cout << "3D: " << has_3D << "\n";
	std::cout << "HDR: " << has_HDR << "\n";
}

int TV::get_display_size_tv(){ return display_size; }

std::string TV::get_screen_type(){ return screen_type; }

std::string TV::get_resolution(){ return resolution; }

int TV::get_has_3D(){ return has_3D; }

int TV::get_has_HDR(){ return has_HDR; }

void TV::compare(Product* other_product , std::string name_products){
	if(other_product->get_has_3D() == -1){
		throw incomparable_error();
		return;
	}
	std::cout << name_products;
	std::cout << "Screen Size: " << display_size << " | " << other_product->get_display_size_tv() << "\n";
	std::cout << "Screen Type: " << screen_type << " | " << other_product->get_screen_type() << "\n";
	std::cout << "Resolution: " << resolution << " | " << other_product->get_resolution() << "\n";
	std::cout << "3D: " << has_3D << " | " << other_product->get_has_3D() << "\n";
	std::cout << "HDR: " << has_HDR << " | " << other_product->get_has_HDR() << "\n";
}