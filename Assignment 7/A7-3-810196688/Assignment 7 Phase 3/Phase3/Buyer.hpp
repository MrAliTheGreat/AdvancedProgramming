#ifndef __BUYER_H__
#define __BUYER_H__

#include "User.hpp"
#include "Offer.hpp"
#include "Program_errors.hpp"

#include <string>

class Buyer : public User
{
public:
	Buyer(int _user_id , std::string _username , std::string _password , std::string _email);
	void add_offer_to_cart(Offer* buyer_demand);
	void show_cart();
	void purchase_items();
	std::vector<Offer*> get_cart(){ return cart; };
	void clear_buyer_cart();
	void set_bought_products();
	int get_order_id();
	void show_buyer_orders(int number_orders);
	std::string show_cart_html();
	std::string get_total_price();
private:
	std::vector<Offer*> cart;
	std::vector<Offer*> bought_products;
};

#endif