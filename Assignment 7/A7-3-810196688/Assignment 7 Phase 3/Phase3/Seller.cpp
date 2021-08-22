#include "Seller.hpp"

#include <string>
#include <iostream>
#include <ctime>

#define DISCOUNT_CODE_LENGTH 10
#define OFFER_TITLE "productId | offerId | offerUnitPrice | offerAmount\n"
#define SEPARATOR " | "

std::string generate_discount(){
	std::string data = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789";
	std::string discount_code = "";
	for(int i = 0 ; i < DISCOUNT_CODE_LENGTH ; i++){
		discount_code += data[rand() % data.length()];
	}
	return discount_code;
}

Seller::Seller(int _user_id , std::string _username , std::string _password , std::string _email)
				: User(_user_id , _username , _password , _email , "seller"){}

void Seller::make_offer(int id_offer , int quantity , double unit_price , int product_id){
	all_seller_offers.push_back(new Offer(id_offer , quantity , unit_price , product_id));
}

void Seller::get_offers(){
	std::cout << OFFER_TITLE;
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		std::cout << all_seller_offers[i]->get_product_id() << SEPARATOR << all_seller_offers[i]->get_offer_id() << SEPARATOR;
		std::cout << all_seller_offers[i]->get_unit_price() << SEPARATOR << all_seller_offers[i]->get_quantity() << "\n";
	}
}

std::string Seller::get_offers_string(){
	std::string offers_string = "";
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		offers_string += std::to_string(all_seller_offers[i]->get_product_id());
		offers_string += SEPARATOR;
		offers_string += std::to_string(all_seller_offers[i]->get_offer_id());
		offers_string += SEPARATOR;
		offers_string += std::to_string(all_seller_offers[i]->get_unit_price());
		offers_string += SEPARATOR;
		offers_string += std::to_string(all_seller_offers[i]->get_quantity());
		offers_string += "<br>";
	}
	return offers_string;
}

bool Seller::contains_offer(int offer_id){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			return true;
		}
	}
	return false;
}

void Seller::change_seller_offer(int offer_id , double new_unit_price , int new_quantity){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			all_seller_offers[i]->set_unit_price(new_unit_price);
			all_seller_offers[i]->set_quantity(new_quantity);
		}
	}
}

bool Seller::contains_product(int product_id){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_product_id() == product_id){
			return true;
		}
	}
	return false;
}

void Seller::get_offer_info_single_product(int product_id){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_product_id() == product_id){
			std::cout << all_seller_offers[i]->get_offer_id() << SEPARATOR; 
			std::cout << all_seller_offers[i]->get_unit_price() << SEPARATOR;
			std::cout << all_seller_offers[i]->get_quantity() << "\n";
		}
	}
}

std::string Seller::get_offer_info_single_product_html(int product_id){
	std::string offer_info = "";
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_product_id() == product_id){
			if(all_seller_offers[i]->get_quantity() != 0){
				offer_info += "  <tr>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_offer_id()) + "</th>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_unit_price()) + "</th>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_quantity()) + "</th>";
				offer_info += "    <form action=\"/product_help?offerId=" + std::to_string(all_seller_offers[i]->get_offer_id()) + "&productId=" + std::to_string(product_id) + "\" method=\"post\">";
				offer_info += "    <th> <input name=\"userDemandAmount\" type=\"text\" placeholder=\"User Demand Quantity\" /> </th>";			
				offer_info += "      <th> <button type=\"submit\" >Submit Demand</button> </th>";
				offer_info += "    </form>";
				offer_info += "  </tr>";
			}else{
				offer_info += "  <tr>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_offer_id()) + "</th>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_unit_price()) + "</th>";
				offer_info += "    <th>" + std::to_string(all_seller_offers[i]->get_quantity()) + "</th>";
				offer_info += "    <form action=\"/product_help?offerId=" + std::to_string(all_seller_offers[i]->get_offer_id()) + "&productId=" + std::to_string(product_id) + "\" method=\"post\">";
				offer_info += "    <th> <input name=\"userDemandAmount\" type=\"text\" placeholder=\"User Demand Quantity\" disabled/> </th>";			
				offer_info += "      <th> <button type=\"submit\" disabled>Submit Demand</button> </th>";
				offer_info += "    </form>";
				offer_info += "  </tr>";				
			}
		}
	}
	return offer_info;
}

void Seller::put_discount_on_offer(int offer_id , int discount_percentage , int num_discount_codes){
	srand(time(0));
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			for(int j = 0 ; j < num_discount_codes ; j++){
				all_seller_offers[i]->add_new_discount(generate_discount() , discount_percentage);
			}
		}
	}
}

Offer* Seller::get_offer_for_buyer(int offer_id){
	for (int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			return new Offer(all_seller_offers[i]->get_offer_id() , all_seller_offers[i]->get_quantity() , all_seller_offers[i]->get_unit_price() , all_seller_offers[i]->get_product_id());
		}
	}
	return new Offer(-1 , -1 , -1 , -1);
}

void Seller::change_seller_offer_quantity(int offer_id , int new_quantity){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			all_seller_offers[i]->set_quantity(new_quantity);
		}
	}
}

int Seller::get_one_offer_quantity(int offer_id){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_offer_id() == offer_id){
			return all_seller_offers[i]->get_quantity();
		}
	}
	return -1;
}

bool Seller::already_existing_offer(Offer check_offer){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->get_quantity() == check_offer.get_quantity() && 
			all_seller_offers[i]->get_product_id() == check_offer.get_product_id() && 
			all_seller_offers[i]->get_unit_price() == check_offer.get_unit_price()){

			return true;
		}
	}
	return false;
}

void Seller::remove_used_code(std::string used_code){
	for(int i = 0 ; i < all_seller_offers.size() ; i++){
		if(all_seller_offers[i]->contains_discount(used_code)){
			all_seller_offers[i]->remove_used_discount(used_code);
		}
	}
}