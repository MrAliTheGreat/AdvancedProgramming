#include "Offer.hpp"

#include <iostream>

Offer::Offer(int _id , int _quantity , double _unit_price , int _product_id){
	offer_id = _id;
	quantity = _quantity;
	unit_price = _unit_price;
	product_id = _product_id;
	order_buyer_id = 0;
	discount_code_used = "";
}

void Offer::set_quantity(int new_quantity){
	quantity = new_quantity;
}

void Offer::set_used_code(std::string used_code){
	discount_code_used = used_code;
}

void Offer::set_seller_id(int id){
	seller_id = id;
}

void Offer::set_product_name(std::string product_name){
	name_product = product_name;
}

void Offer::set_unit_price(double new_unit_price){
	unit_price = new_unit_price;
}

void Offer::add_new_discount(std::string discount_code , int discount_percentage){
	all_discounts.push_back(new Discount(discount_code , discount_percentage));
	std::cout << discount_code << "\n";
}

void Offer::set_order_buyer_id(int num_order){
	order_buyer_id = num_order;
}

bool Offer::contains_discount(std::string discount_code){
	for(int i = 0 ; i < all_discounts.size() ; i++){
		if(all_discounts[i]->get_code() == discount_code){
			return true;
		}
	}
	return false;
}

int Offer::get_discount_percentage(std::string discount_code){
	for(int i = 0 ; i < all_discounts.size() ; i++){
		if(all_discounts[i]->get_code() == discount_code){
			return all_discounts[i]->get_percentage();
		}
	}
	return -1;
}

void Offer::remove_used_discount(std::string used_code){
	for(int i = 0 ; i < all_discounts.size() ; i++){
		if(all_discounts[i]->get_code() == used_code){
			all_discounts.erase(all_discounts.begin() + i);
		}
	}
}