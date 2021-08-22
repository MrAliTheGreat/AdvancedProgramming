#include "Product.hpp"
#include <iostream>

Product::Product(std::string _name , int _product_id){
	name = _name;
	product_id = _product_id;
}

void Product::set_quantity(int quantity){
	quantity_seller = quantity;
}

void Product::set_unit_price(double price){
	unit_price_seller = price;
}

void Product::add_new_product_comment(std::string new_comment , std::string username){
	all_product_comments.push_back(new Comment(new_comment , username));
	std::cout << "OK\n";
}

void Product::show_product_comments(){
	for (int i = 0 ; i < all_product_comments.size() ; i++){
		std::cout << all_product_comments[i]->get_user_posted() << " | " << all_product_comments[i]->get_comment_sentence();
		std::cout << "\n";
	}
}

int Product::get_weight(){ return -1;}

int Product::get_num_seats(){ return -1; }

int Product::get_num_cylinders(){ return -1; }

int Product::get_engin_capacity(){ return -1; }

int Product::get_has_park_sensors(){ return -1; }

int Product::get_display_size_tv(){ return -1; }

std::string Product::get_screen_type(){ return ""; }

std::string Product::get_resolution(){ return ""; }

int Product::get_has_3D(){ return -1; }

int Product::get_has_HDR(){ return -1; }

double Product::get_CPU_frequency(){ return -1; }

int Product::get_built_in_memory(){ return -1; }

int Product::get_RAM(){ return -1; }

double Product::get_display_size_phone(){ return -1; }

int Product::get_camera_resolution(){ return -1; }

std::string Product::get_OS(){ return ""; }
