#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include "Shop.hpp"

#define NUM_ROWS_HEADER 1
#define COMMENT "comment"
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define TYPE "type"
#define SELLER "seller"
#define BUYER "buyer"
#define ADMIN "admin"
#define SUCCESS "OK\n"
#define MOBILE_FORM "mobile"
#define CAR_FORM "car"
#define TV_FORM "tv"
#define GET_PRODUCTS_TITLE "productId | productName\n"
#define SPACER " | "
#define OFFER_ID "offerId"
#define PRODUCT_ID "productId"
#define OFFER_AMOUNT "offerAmount"
#define OFFER_UNIT_PRICE "offerUnitPrice"
#define OFFER_TITLE "productId | productName | offerId | offerUnitPrice | offerAmount\n"
#define DISCOUNT_CODE "discountCode"
#define MOBILE_INFO_SEPARATOR 8
#define CAR_INFO_SEPARATOR 6
#define TV_INFO_SEPARATOR 6

Shop::Shop(){
	shop_admin = new Admin;
	shop_admin->set_logged_in(true);
	active_users.push_back(shop_admin);
	id_products = 0;
	id_users = 0;
	id_offer = 0;
}

std::vector<std::string> extractor(std::string address){
	std::vector<std::string> extracted;
	std::stringstream ss_line;
	std::string line , info;
	int counter_line = 1;
	std::fstream file(address);

	if(!file.is_open()){
		throw file_existance_error();
	}

	while(getline(file , line)){
		ss_line.str(line);
		ss_line.clear();
		if(counter_line > NUM_ROWS_HEADER){
			while(getline(ss_line , info , ',')){
				extracted.push_back(info);
			}
		}
		counter_line++;
	}
	file.close();
	return extracted;
}

int word_finder_in_command(std::vector<std::string> command_info , std::string word){
	bool is_first_comment = true;
	for (int i = 0; i < command_info.size(); i++){
		if(command_info[i] == word){
			if(word == COMMENT && is_first_comment == true){
				is_first_comment = false;
				continue;
			}
			return i + 1;
		}
	}
	return -1;
}

std::string get_product_name(std::vector<Product*> all_products , int target_product_id){
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == target_product_id){
			return all_products[i]->get_product_name();
		}
	}
	return "";
}

std::string command_extractor(std::vector<std::string> command_info , int comment_start_index){
	std::string comment = "";
	for(int i = comment_start_index ; i < command_info.size() ; i++){
		if(i == command_info.size() - 1){
			comment = comment + command_info[i];
		}else{
			comment = comment + command_info[i] + " ";
		}
	}
	return comment;
}

bool user_email_exists(std::vector<User*> all_users , std::string email){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->get_email() == email){
			return true;
		}
	}
	return false;
}

int user_index_finder_email(std::vector<User*> all_users , std::string email){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->get_email() == email){
			return i;
		}
	}
	return -1;
}

bool product_exists(std::vector<Product*> all_products , int product_id){
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == product_id){
			return true;
		}
	}
	return false;
}

bool offer_already_exists(std::vector<User*> all_users , int amount, double price , int product_id){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->already_existing_offer(Offer(-1 , amount , price , product_id)) ){
			return true;
		}
	}
	return false;
}

bool offer_already_exists_offerId(std::vector<User*> all_users , int offer_id){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->contains_offer(offer_id)){
			return true;
		}
	}
	return false;
}

void Shop::signup(std::vector<std::string> command_info){
	try{
		if(active_users.size() != 0 || shop_admin->get_logged_in()){
			throw signup_error();
		}
	}catch(signup_error e){
		std::cerr << e.what();
		throw signup_error();
		return;
	}
	try{
		for(int i = 0 ; i < all_users.size() ; i++){
			if(all_users[i]->get_username() == command_info[word_finder_in_command(command_info , USERNAME)]){
				throw signup_error();
			}
		}
		if(shop_admin->get_username() == command_info[word_finder_in_command(command_info , USERNAME)]){
			throw signup_error();
		}
	}catch(signup_error e){
		std::cerr << e.what();
		throw signup_error();
		return;
	}
	if(word_finder_in_command(command_info , TYPE) != -1){
		if(command_info[word_finder_in_command(command_info , TYPE)] == SELLER){
			id_users++;
			Seller* new_seller = new Seller(id_users , command_info[word_finder_in_command(command_info , USERNAME)] ,
										    command_info[word_finder_in_command(command_info , PASSWORD)] ,
										    command_info[word_finder_in_command(command_info , EMAIL)]);
			new_seller->set_user_type(SELLER);
			all_users.push_back(new_seller);
			active_users.push_back(new_seller);
			std::cout << SUCCESS;
		}else if(command_info[word_finder_in_command(command_info , TYPE)] == BUYER){
			id_users++;
			Buyer* new_buyer = new Buyer(id_users , command_info[word_finder_in_command(command_info , USERNAME)] ,
										    command_info[word_finder_in_command(command_info , PASSWORD)] ,
										    command_info[word_finder_in_command(command_info , EMAIL)]);
			new_buyer->set_user_type(BUYER);
			all_users.push_back(new_buyer);
			active_users.push_back(new_buyer);
			std::cout << SUCCESS;		
		}
	}else{
		id_users++;
		Buyer* new_buyer = new Buyer(id_users , command_info[word_finder_in_command(command_info , USERNAME)] ,
									    command_info[word_finder_in_command(command_info , PASSWORD)] ,
									    command_info[word_finder_in_command(command_info , EMAIL)]);
		all_users.push_back(new_buyer);
		active_users.push_back(new_buyer);
		std::cout << SUCCESS;	
	}
}

void Shop::login(std::vector<std::string> command_info){
	std::string user_email = command_info[word_finder_in_command(command_info , EMAIL)];
	try{
		if(active_users.size() != 0 || shop_admin->get_logged_in()){
			throw login_error();
		}
	}catch(login_error e){
		std::cerr << e.what();
		throw login_error();
		return;
	}
	try{
		if(user_email == shop_admin->get_email()){
			if(shop_admin->get_password() != command_info[word_finder_in_command(command_info , PASSWORD)]){
				throw login_error();
			}
		}else if(!user_email_exists(all_users , user_email)){
			throw login_error();
		}else{
			if(all_users[user_index_finder_email(all_users , user_email)]->get_password() != command_info[word_finder_in_command(command_info , PASSWORD)] ){
				throw login_error();
			}
		}
	}catch(login_error e){
		std::cerr << e.what();
		throw login_error();
		return;
	}

	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->get_email() == command_info[word_finder_in_command(command_info , EMAIL)] && 
		   all_users[i]->get_password() == command_info[word_finder_in_command(command_info , PASSWORD)]){

			all_users[i]->set_logged_in(true);
			active_users.push_back(all_users[i]);
			std::cout << SUCCESS;
		}
	}

	if(shop_admin->get_email() == command_info[word_finder_in_command(command_info , EMAIL)] && 
	   shop_admin->get_password() == command_info[word_finder_in_command(command_info , PASSWORD)]){
		shop_admin->set_logged_in(true);
		active_users.push_back(shop_admin);
		std::cout << SUCCESS;
	}
}

void Shop::logout(){
	try{
		if(active_users.size() == 0 && !shop_admin->get_logged_in()){
			throw logout_error();
		}
	}catch(logout_error e){
		std::cerr << e.what();
		return;
	}
	if(shop_admin->get_logged_in()){
		shop_admin->set_logged_in(false);
		active_users.erase(active_users.begin());
		std::cout << SUCCESS;
	}else{
		for(int i = 0 ; i < all_users.size() ; i++){
			if(all_users[i]->get_user_id() == active_users[0]->get_user_id()){
				all_users[i]->set_logged_in(false);
				active_users[0]->clear_buyer_cart();
				active_users.erase(active_users.begin());
			}
		}
		std::cout << SUCCESS;
	}
	active_users[0]->clear_buyer_cart();
}

void Shop::import_product(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != ADMIN){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	
	try{
		extractor(command_info[command_info.size() - 1]);
	}catch(file_existance_error e){
		std::cerr << e.what();
		return;
	}
	std::vector<std::string> product_info = extractor(command_info[command_info.size() - 1]);

	if(command_info[word_finder_in_command(command_info , TYPE)] == MOBILE_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + MOBILE_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new Phone(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 std::stod(product_info[i + 2]) , std::stoi(product_info[i + 3]) , 
											 std::stoi(product_info[i + 4]) , std::stod(product_info[i + 5]) ,
											 std::stoi(product_info[i + 6]) , product_info[i + 7] ));
		}
		std::cout << SUCCESS;
	}else if(command_info[word_finder_in_command(command_info , TYPE)] == CAR_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + CAR_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new Car(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 std::stoi(product_info[i + 2]) , std::stoi(product_info[i + 3]) , 
											 std::stoi(product_info[i + 4]) , std::stoi(product_info[i + 5]) ));
		}
		std::cout << SUCCESS;	
	} else if(command_info[word_finder_in_command(command_info , TYPE)] == TV_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + TV_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new TV(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 product_info[i + 2] , product_info[i + 3] , 
											 std::stoi(product_info[i + 4]) , std::stoi(product_info[i + 5]) ));
		}
		std::cout << SUCCESS;
	}
}

void Shop::import_product_html(std::vector<std::string> product_info , std::string product_type){

	if(product_type == MOBILE_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + MOBILE_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new Phone(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 std::stod(product_info[i + 2]) , std::stoi(product_info[i + 3]) , 
											 std::stoi(product_info[i + 4]) , std::stod(product_info[i + 5]) ,
											 std::stoi(product_info[i + 6]) , product_info[i + 7] ));
		}
		std::cout << SUCCESS;
	}else if(product_type == CAR_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + CAR_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new Car(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 std::stoi(product_info[i + 2]) , std::stoi(product_info[i + 3]) , 
											 std::stoi(product_info[i + 4]) , std::stoi(product_info[i + 5]) ));
		}
		std::cout << SUCCESS;	
	} else if(product_type == TV_FORM){
		for(int i = 0 ; i < product_info.size() ; i = i + TV_INFO_SEPARATOR){
			id_products++;
			all_products.push_back(new TV(product_info[i + 0] , id_products , std::stoi(product_info[i + 1]) , 
											 product_info[i + 2] , product_info[i + 3] , 
											 std::stoi(product_info[i + 4]) , std::stoi(product_info[i + 5]) ));
		}
		std::cout << SUCCESS;
	}
}

void Shop::get_products(){
	try{
		if(active_users[0]->get_user_type() == ADMIN){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	std::cout << GET_PRODUCTS_TITLE;
	for(int i = 0 ; i < all_products.size() ; i++){
		std::cout << all_products[i]->get_product_id() << SPACER << all_products[i]->get_product_name() << "\n";
	}
}

void Shop::seller_offer(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != SELLER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	try{
		if(!product_exists(all_products , std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)])) ){
			throw offer_error();
		}
	}catch(offer_error e){
		std::cerr << e.what();
		throw offer_error();
		return;
	}
	try{
		if(offer_already_exists(all_users , std::stoi(command_info[word_finder_in_command(command_info , OFFER_AMOUNT)]) ,
								std::stod(command_info[word_finder_in_command(command_info , OFFER_UNIT_PRICE)]) ,
								std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)])) ){

			throw offer_error();
		}
	}catch(offer_error e){
		std::cerr << e.what();
		return;
	}

	id_offer++;
	active_users[0]->make_offer(id_offer , std::stoi(command_info[word_finder_in_command(command_info , OFFER_AMOUNT)]) ,
								std::stod(command_info[word_finder_in_command(command_info , OFFER_UNIT_PRICE)]) ,
								std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]) );
	std::cout << SUCCESS;
}

void Shop::get_seller_offers(){
	try{
		if(active_users[0]->get_user_type() != SELLER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	active_users[0]->get_offers();
}

std::string Shop::get_seller_offers_string(){
	return active_users[0]->get_offers_string();
}

void Shop::change_offer(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != SELLER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}

	try{
		if(!offer_already_exists_offerId(all_users , std::stoi(command_info[word_finder_in_command(command_info , OFFER_ID)]) )){
			throw offer_error();
		}
	}catch(offer_error e){
		std::cerr << e.what();
		return;
	}

	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->contains_offer(std::stoi(command_info[word_finder_in_command(command_info , OFFER_ID)]))){
			all_users[i]->change_seller_offer(std::stoi(command_info[word_finder_in_command(command_info , OFFER_ID)]) ,
											  std::stod(command_info[word_finder_in_command(command_info , OFFER_UNIT_PRICE)]) ,
											  std::stoi(command_info[word_finder_in_command(command_info , OFFER_AMOUNT)]) );
		}
	}
	std::cout << SUCCESS;
}

void Shop::offers_on_product(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_product_id = std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]);
	std::string target_product_name = get_product_name(all_products , target_product_id);
	std::cout << OFFER_TITLE;

	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->contains_product(target_product_id)){
			std::cout << target_product_id << SPACER << target_product_name << SPACER;
			all_users[i]->get_offer_info_single_product(target_product_id);
		}
	}
}

std::string Shop::offers_on_product_html(std::vector<std::string> command_info){
	std::string html_message = "";
	int target_product_id = std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]);

	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->contains_product(target_product_id)){
			html_message += all_users[i]->get_offer_info_single_product_html(target_product_id);
		}
	}
	return html_message;
}

void Shop::product_detail(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_product_id = std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]);
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == target_product_id){
			std::cout << all_products[i]->get_product_name() << "\n";
			all_products[i]->get_product_info();
		}
	}
}

void Shop::post_comment(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_product_id = std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]);
	try{
		if(!product_exists(all_products , target_product_id)){
			throw no_offer_error();
		}
	}catch(no_offer_error e){
		std::cerr << e.what();
		return;
	}
	std::string comment = command_extractor(command_info , word_finder_in_command(command_info , COMMENT));
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == target_product_id){
			all_products[i]->add_new_product_comment(comment , active_users[0]->get_username());
		}
	}
}

void Shop::get_product_comments(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}	
	int target_product_id = std::stoi(command_info[word_finder_in_command(command_info , PRODUCT_ID)]);
	std::string target_product_name = get_product_name(all_products , target_product_id);
	std::cout << target_product_name << "\n";
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == target_product_id){
			all_products[i]->show_product_comments();
		}
	}	
}

void Shop::generate_discount_code(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != SELLER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_offer_id = std::stoi(command_info[word_finder_in_command(command_info , OFFER_ID)]);
	int discount_percentage = std::stoi(command_info[word_finder_in_command(command_info , "discountPercent")]);
	int number_dicount_codes = std::stoi(command_info[word_finder_in_command(command_info , "discountNumber")]);
	active_users[0]->put_discount_on_offer(target_offer_id , discount_percentage , number_dicount_codes);
}

void Shop::add_to_cart(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_offer_id = std::stoi(command_info[word_finder_in_command(command_info , OFFER_ID)]);
	int target_amount = std::stoi(command_info[word_finder_in_command(command_info , "amount")]);
	std::string discount_code = "";

	if(word_finder_in_command(command_info , DISCOUNT_CODE) != -1){
		discount_code = command_info[word_finder_in_command(command_info , DISCOUNT_CODE)];
	}

	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->contains_offer(target_offer_id)){
			try{
				if(target_amount > all_users[i]->get_one_offer_quantity(target_offer_id)){
					throw offer_error();
				}
			}catch(offer_error e){
				std::cerr << e.what();
				throw offer_error();
				return;		
			}			
			Offer* buyer_demand = all_users[i]->get_offer_for_buyer(target_offer_id);
			buyer_demand->set_quantity(target_amount);
			if(discount_code == ""){
				buyer_demand->set_unit_price(target_amount * buyer_demand->get_unit_price());
			}else{
				try{
					if(buyer_demand->contains_discount(discount_code)){
						buyer_demand->set_unit_price(target_amount * (buyer_demand->get_unit_price() - ((buyer_demand->get_unit_price()) * buyer_demand->get_discount_percentage(discount_code) * 0.01)));
						buyer_demand->set_used_code(discount_code);
					}else{
						throw discount_code_error();
					}
				}catch(discount_code_error e){
					std::cerr << e.what();
					return;
				}
			}
			buyer_demand->set_seller_id(i + 1);
			buyer_demand->set_product_name(get_product_name(all_products , buyer_demand->get_product_id()));
			active_users[0]->add_offer_to_cart(buyer_demand); 
		}
	}
}

void Shop::show_buyer_cart(){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	active_users[0]->show_cart();
}

std::string Shop::show_buyer_cart_html(){
	return active_users[0]->show_cart_html();
}

std::string Shop::get_buyer_total_price(){
	return active_users[0]->get_total_price();
}

void Shop::charge_buyer_wallet(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	double target_amount = std::stod(command_info[word_finder_in_command(command_info , "amount")]);
	try{
		active_users[0]->add_to_wallet(target_amount);
	}catch(invalid_money_error e){
		std::cerr << e.what();
		return;
	}
}

void Shop::get_wallet(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() == ADMIN){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int num_transactions = std::stoi(command_info[word_finder_in_command(command_info , "count")]);
	active_users[0]->show_buyer_transactions(num_transactions);
}

std::string Shop::get_wallet_html(std::vector<std::string> command_info){
	int num_transactions = std::stoi(command_info[word_finder_in_command(command_info , "count")]);
	return active_users[0]->show_buyer_transactions_html(num_transactions);
}

// Submit Cart Has Changed and is different from phase 1 
void Shop::submit_cart(){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	try{
		active_users[0]->purchase_items();
	}catch(credit_error e){
		std::cerr << e.what();
		throw credit_error();
		return;
	}
	std::vector<Offer*> user_cart = active_users[0]->get_cart();

	for(int j = 0 ; j < user_cart.size() ; j++){
		for (int i = 0 ; i < all_users.size() ; i++){
			if(user_cart[j]->get_seller_id() == all_users[i]->get_user_id()){
				all_users[i]->change_seller_offer_quantity(user_cart[j]->get_offer_id() , 
					all_users[i]->get_one_offer_quantity(user_cart[j]->get_offer_id()) - user_cart[j]->get_quantity() );
				all_users[i]->add_to_wallet(user_cart[j]->get_unit_price() * user_cart[j]->get_quantity());
				all_users[i]->remove_used_code(user_cart[j]->get_used_code());
			}
		}
	}

	for(int i = 0 ; i < user_cart.size() ; i++){
		user_cart[i]->set_order_buyer_id(active_users[0]->get_order_id() + 1);
	}

	active_users[0]->set_bought_products();
	active_users[0]->clear_buyer_cart();
}

void Shop::get_buyer_orders(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int num_orders = std::stoi(command_info[word_finder_in_command(command_info , "count")]);
	try{
		active_users[0]->show_buyer_orders(num_orders);
	}catch(no_order_error e){
		std::cerr << e.what();
		return;
	}
}

void Shop::compare_products(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	int target_product_id_1 = std::stoi(command_info[word_finder_in_command(command_info , "productId1")]);
	int target_product_id_2 = std::stoi(command_info[word_finder_in_command(command_info , "productId2")]);
	try{
		if(!product_exists(all_products , target_product_id_1) || !product_exists(all_products , target_product_id_2)){
			throw no_product_error();
		}
	}catch(no_product_error e){
		std::cerr << e.what();
		return;
	}

	Product* product_1;
	Product* product_2;
	for(int i = 0 ; i < all_products.size() ; i++){
		if(all_products[i]->get_product_id() == target_product_id_1){
			product_1 = all_products[i];
		}else if(all_products[i]->get_product_id() == target_product_id_2){
			product_2 = all_products[i];
		}
	}

	std::string name_products = product_1->get_product_name() + SPACER + product_2->get_product_name() + "\n";
	
	try{
		product_1->compare(product_2 , name_products);
	}catch(incomparable_error e){
		std::cerr << e.what();
		return;
	}
}

void Shop::show_admin_offers(std::vector<std::string> command_info){
	try{
		if(active_users[0]->get_user_type() != ADMIN){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}
	std::string sort_order = command_info[word_finder_in_command(command_info , "order")];
	std::string field_offers = command_info[word_finder_in_command(command_info , "field")];
	active_users[0]->show_offers(all_users , sort_order , field_offers);
}

bool sort_offers_by_id(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_offer_id() < offer_2->get_offer_id()); }

void Shop::show_buyer_all_offers(){
	try{
		if(active_users[0]->get_user_type() != BUYER){
			throw access_error();
		}
	}catch(access_error e){
		std::cerr << e.what();
		return;
	}

	std::vector<Offer*> all_offers;
	for(int i = 0 ; i < all_users.size() ; i++){
		for(int j = 0 ; j < all_users[i]->get_seller_offers().size() ; j++){
			all_offers.push_back(all_users[i]->get_seller_offers()[j]);
		}
	}

	std::sort(all_offers.begin() , all_offers.end() , sort_offers_by_id);
	std::cout << OFFER_TITLE;
	for(int i = 0 ; i < all_offers.size() ; i++){
		std::cout << all_offers[i]->get_product_id() << SPACER;
		std::cout << get_product_name(all_products , all_offers[i]->get_product_id()) << SPACER;
		std::cout << all_offers[i]->get_offer_id() << SPACER;
		std::cout << all_offers[i]->get_unit_price() << SPACER;
		std::cout << all_offers[i]->get_quantity() << "\n";
	}
}

int Shop::find_user_id_html(std::string email){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->get_email() == email){
			return all_users[i]->get_user_id(); 
		}
	}
	if(email == shop_admin->get_email()){
		return shop_admin->get_user_id();
	}
	return -1;
}

std::string Shop::find_user_type_html(std::string email){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i]->get_email() == email){
			return all_users[i]->get_user_type(); 
		}
	}
	if(email == shop_admin->get_email()){
		return shop_admin->get_user_type();
	}
	return "";
}

int Shop::get_active_user_id(){
	if(active_users.size() == 0){
		return -1;
	}
	return active_users[0]->get_user_id();
}

std::string Shop::get_all_product_html(){
	std::string product_info_string = "";
	for(int i = 0 ; i < all_products.size() ; i++){
		product_info_string += std::to_string(all_products[i]->get_product_id());
		product_info_string += " | ";
		product_info_string += all_products[i]->get_product_name();
		product_info_string += "<br>";
	}
	return product_info_string;
}

std::vector<Product*> Shop::get_all_products_vector_html(){
	return all_products;
}

std::string Shop::get_active_user_type(){
	if(active_users.size() == 0){
		return "";
	}
	return active_users[0]->get_user_type();
}