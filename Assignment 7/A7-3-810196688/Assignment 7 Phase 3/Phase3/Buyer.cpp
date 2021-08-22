#include "Buyer.hpp"

#include <iostream>
#include <string>

#define CART_TITLE "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount\n"
#define ORDER_TITLE "productId | productName | offerId | sellerId | soldPrice | amount\n"
#define SEPARATOR " | "

Buyer::Buyer(int _user_id , std::string _username , std::string _password , std::string _email)
				: User(_user_id , _username , _password , _email , "buyer") {}

void Buyer::set_bought_products(){
	for(int i = 0 ; i < cart.size() ; i++){
		bought_products.push_back(cart[i]);
	}
}

int Buyer::get_order_id(){
	if(bought_products.size() == 0){
		return 0;
	}else{
		return bought_products.back()->get_order_buyer_id();
	}
}


void Buyer::add_offer_to_cart(Offer* buyer_demand){
	cart.push_back(buyer_demand);
	std::cout << "OK\n";
}

void Buyer::show_cart(){
	std::cout << CART_TITLE;
	for(int i = 0 ; i < cart.size() ; i++){
		std::cout << cart[i]->get_product_id() << SEPARATOR << cart[i]->get_product_name() << SEPARATOR << cart[i]->get_offer_id() << SEPARATOR;
		std::cout << cart[i]->get_seller_id() << SEPARATOR << cart[i]->get_unit_price() << SEPARATOR << cart[i]->get_quantity() << "\n";
	}

	if(cart.size() == 0){
		std::cout << "Empty\n";
	}
}

std::string Buyer::show_cart_html(){
	std::string cart_info = "";
	for(int i = 0 ; i < cart.size() ; i++){
		cart_info += "  <tr>";
		cart_info += "    <th>" + std::to_string(cart[i]->get_product_id()) + "</th>";
		cart_info += "    <th>" + cart[i]->get_product_name() + "</th>";
		cart_info += "    <th>" + std::to_string(cart[i]->get_offer_id()) + "</th>";
		cart_info += "    <th>" + std::to_string(cart[i]->get_seller_id()) + "</th>";
		cart_info += "    <th>" + std::to_string(cart[i]->get_unit_price()) + "</th>";
		cart_info += "    <th>" + std::to_string(cart[i]->get_quantity()) + "</th>";
		cart_info += "  </tr>";
	}
	cart_info += "</table>";
	cart_info += "<form action=\"/purchase\" method=\"post\">";			
	cart_info += "	<p> <button type=\"submit\" >Purchase</button> </p>";
	cart_info += "</form>";
	return cart_info;
}

std::string Buyer::get_total_price(){
	double money_spent = 0;
	for(int i = 0 ; i < cart.size() ; i++){
		money_spent += ( cart[i]->get_unit_price());
	}
	return std::to_string(money_spent);
}

void Buyer::purchase_items(){
	double money_spent = 0;
	for(int i = 0 ; i < cart.size() ; i++){
		money_spent += cart[i]->get_unit_price();
	}
	if(transactions.back() < money_spent){
		throw credit_error();
		return;
	}
	transactions.push_back(transactions.back() - money_spent);
	std::cout << "OK\n";
}

void Buyer::clear_buyer_cart(){
	cart.clear();
}

void Buyer::show_buyer_orders(int number_orders){
	int flag_order_id = 1;
	if(bought_products.size() == 0){
		throw no_order_error();
	}
	std::cout << ORDER_TITLE;
	if(number_orders >= bought_products.size()){
		for(int i = bought_products.size() - 1 ; i >= 0 ; i--){
			if(bought_products[i]->get_order_buyer_id() != flag_order_id){
				std::cout << "****\n";
			}
			// soldPrice means unitPrice
			std::cout << bought_products[i]->get_product_id() << SEPARATOR << bought_products[i]->get_product_name() << SEPARATOR ;
			std::cout << bought_products[i]->get_offer_id() << SEPARATOR << bought_products[i]->get_seller_id() << SEPARATOR;
			std::cout << bought_products[i]->get_unit_price() / bought_products[i]->get_quantity() << SEPARATOR << bought_products[i]->get_quantity() << "\n";
			flag_order_id = bought_products[i]->get_order_buyer_id();
		}
	}else{
		for(int i = bought_products.size() - 1 ; i > bought_products.size() - 1 - number_orders ; i--){
			if(bought_products[i]->get_order_buyer_id() != flag_order_id){
				std::cout << "****\n";
			}
			std::cout << bought_products[i]->get_product_id() << SEPARATOR << bought_products[i]->get_product_name() << SEPARATOR ;
			std::cout << bought_products[i]->get_offer_id() << SEPARATOR << bought_products[i]->get_seller_id() << SEPARATOR;
			std::cout << bought_products[i]->get_unit_price() << SEPARATOR << bought_products[i]->get_quantity() << "\n";
			flag_order_id = bought_products[i]->get_order_buyer_id();
		}
	}
}