#ifndef __SELLER_H__
#define __SELLER_H__

#include "User.hpp"
#include "Offer.hpp"

#include <string>
#include <vector>

class Seller : public User
{
public:
	Seller(int _user_id , std::string _username , std::string _password , std::string _email);
	void make_offer(int id_offer , int quantity , double unit_price , int product_id);
	void get_offers();
	bool contains_offer(int offer_id);
	void change_seller_offer(int offer_id , double new_unit_price , int new_quantity);
	void get_offer_info_single_product(int product_id);
	bool contains_product(int product_id);
	void put_discount_on_offer(int offer_id , int discount_percentage , int num_discount_codes);
	Offer* get_offer_for_buyer(int offer_id);
	void change_seller_offer_quantity(int offer_id , int new_quantity);
	int get_one_offer_quantity(int offer_id);
	std::vector<Offer*> get_seller_offers(){ return all_seller_offers; };
	bool already_existing_offer(Offer check_offer);
	void remove_used_code(std::string used_code);
private:
	std::vector<Offer*> all_seller_offers;
};

#endif