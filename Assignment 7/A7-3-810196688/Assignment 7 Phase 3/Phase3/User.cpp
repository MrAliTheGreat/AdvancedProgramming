#include "User.hpp"

#include <iostream>

User::User(int _user_id , std::string _username , std::string _password , std::string _email , std::string _user_type){
	user_id = _user_id;
	email = _email;
	username = _username;
	password = _password;
	user_type = _user_type;
	logged_in = true;
	transactions.push_back(0);
}

void User::set_logged_in(bool status){
	logged_in = status;
}

void User::set_user_type(std::string type){
	user_type = type;
}

void User::add_to_wallet(double target_amount){
	if(target_amount <= 0){
		throw invalid_money_error();
	}
	transactions.push_back(transactions.back() + target_amount);
	if(user_type == "buyer"){
		std::cout << "OK\n";
	}
}

void User::show_buyer_transactions(int num_transactions){
	std::cout << "credit\n";
	if(num_transactions >= transactions.size()){
		for(int i = transactions.size() - 1 ; i >= 0 ; i--){
			std::cout << transactions[i] << "\n";
		}
	}else{
		for(int i = transactions.size() - 1 ; i > transactions.size() - 1 - num_transactions ; i--){
			std::cout << transactions[i] << "\n";
		}		
	}
}

std::string User::show_buyer_transactions_html(int num_transactions){
	std::cout << "credit\n";
	if(num_transactions >= transactions.size()){
		for(int i = transactions.size() - 1 ; i >= 0 ; i--){
			return std::to_string(transactions[i]);
		}
	}else{
		for(int i = transactions.size() - 1 ; i > transactions.size() - 1 - num_transactions ; i--){
			return std::to_string(transactions[i]);
		}		
	}
	return "";
}

void User::make_offer(int id_offer , int quantity , double unit_price , int product_id){}

void User::get_offers(){}

std::string User::get_offers_string(){ return ""; }

bool User::contains_offer(int offer_id){ return false; }

void User::change_seller_offer(int offer_id , double new_unit_price , int new_quantity){}

void User::get_offer_info_single_product(int product_id){}

bool User::contains_product(int product_id){ return false; }

void User::put_discount_on_offer(int offer_id , int discount_percentage , int num_discount_codes){}

void User::add_offer_to_cart(Offer* buyer_demand){}

Offer* User::get_offer_for_buyer(int offer_id){ return new Offer(-1 , -1 , -1 , -1); }

void User::show_cart(){}

void User::purchase_items(){}

std::vector<Offer*> User::get_cart(){ std::vector<Offer*> v; return v; }

void User::change_seller_offer_quantity(int offer_id , int new_quantity){}

int User::get_one_offer_quantity(int offer_id){ return -1; }

void User::clear_buyer_cart(){}

void User::set_bought_products(){}

int User::get_order_id(){ return -1; }

void User::show_buyer_orders(int number_orders){}

void User::show_offers(std::vector<User*> users , std::string sort_order , std::string field_offers){}

std::vector<Offer*> User::get_seller_offers(){ std::vector<Offer*> v; return v; }

bool User::already_existing_offer(Offer check_offer){ return false; }

void User::remove_used_code(std::string used_code){}

std::string User::get_offer_info_single_product_html(int product_id){ return ""; }

std::string User::show_cart_html(){ return ""; }

std::string User::get_total_price(){ return ""; }

int User::get_offer_amount_product_html(int product_id){ return -1; }