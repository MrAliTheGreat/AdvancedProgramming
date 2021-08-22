#ifndef __OFFER_H__
#define __OFFER_H__

#include <string>
#include <vector>
#include "Discount.hpp"

class Offer
{
public:
	Offer(int _id , int _quantity , double _unit_price , int _product_id);
	int get_offer_id(){ return offer_id; };
	int get_quantity(){ return quantity; };
	double get_unit_price(){ return unit_price; };
	int get_product_id(){ return product_id; };
	void set_quantity(int new_quantity);
	void set_unit_price(double new_unit_price);
	void add_new_discount(std::string discount_code , int discount_percentage);
	bool contains_discount(std::string discount_code);
	int get_discount_percentage(std::string discount_code);
	void set_seller_id(int id);
	int get_seller_id(){ return seller_id; };
	void set_product_name(std::string product_name);
	std::string get_product_name(){ return name_product; };
	void set_order_buyer_id(int num_order);
	int get_order_buyer_id(){ return order_buyer_id; };
	void remove_used_discount(std::string used_code);
	void set_used_code(std::string used_code);
	std::string get_used_code(){ return discount_code_used; };
protected:
	int offer_id;
	int quantity;
	double unit_price;
	int product_id;
	std::string name_product;
	int seller_id;
	std::vector<Discount*> all_discounts;
	int order_buyer_id;
	std::string discount_code_used;
};

#endif