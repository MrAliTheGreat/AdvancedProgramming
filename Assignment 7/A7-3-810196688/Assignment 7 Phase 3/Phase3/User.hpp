#ifndef __USER_H__
#define __USER_H__

#include "Offer.hpp"
#include "Program_errors.hpp"
#include <string>

class User
{
public:
	User(int _user_id , std::string _username , std::string _password , std::string _email , std::string _user_type = "buyer");
	void set_logged_in(bool status);
	bool get_logged_in(){ return logged_in; }
	void set_user_type(std::string type);
	std::string get_user_type(){ return user_type; }
	std::string get_email(){ return email; };
	std::string get_username(){ return username; };
	std::string get_password(){ return password; };
	int get_user_id(){ return user_id; };
	void add_to_wallet(double target_amount);
	void show_buyer_transactions(int num_transactions);
	std::string show_buyer_transactions_html(int num_transactions);
	virtual void make_offer(int id_offer , int quantity , double unit_price , int product_id);
	virtual void get_offers();
	virtual std::string get_offers_string();
	virtual bool contains_offer(int offer_id);
	virtual void change_seller_offer(int offer_id , double new_unit_price , int new_quantity);
	virtual void get_offer_info_single_product(int product_id);
	virtual std::string get_offer_info_single_product_html(int product_id);
	virtual bool contains_product(int product_id);
	virtual void put_discount_on_offer(int offer_id , int discount_percentage , int num_discount_codes);
	virtual void add_offer_to_cart(Offer* buyer_demand);
	virtual Offer* get_offer_for_buyer(int offer_id);
	virtual void show_cart();
	virtual std::string show_cart_html();
	virtual void purchase_items();
	virtual std::vector<Offer*> get_cart();
	virtual void change_seller_offer_quantity(int offer_id , int new_quantity);
	virtual int get_one_offer_quantity(int offer_id);
	virtual void clear_buyer_cart();
	virtual void set_bought_products();
	virtual int get_order_id();
	virtual void show_buyer_orders(int number_orders);
	virtual void show_offers(std::vector<User*> users , std::string sort_order , std::string field_offers);
	virtual std::vector<Offer*> get_seller_offers();
	virtual bool already_existing_offer(Offer check_offer);
	virtual void remove_used_code(std::string used_code);
	virtual std::string get_total_price();
	virtual int get_offer_amount_product_html(int product_id);
protected:
	int user_id;
	std::string username;
	std::string password;
	std::string email;
	std::string user_type;
	bool logged_in;
	std::vector<double> transactions;
};

#endif