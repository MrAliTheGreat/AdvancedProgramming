#ifndef __SHOP_H__
#define __SHOP_H__

#include "Product.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Seller.hpp"
#include "Buyer.hpp"
#include "Phone.hpp"
#include "TV.hpp"
#include "Car.hpp"
#include "Program_errors.hpp"

#include <string>
#include <vector>

class Shop
{
public:
	Shop();
	void import_product(std::vector<std::string> command_info);
	void signup(std::vector<std::string> command_info);
	void login(std::vector<std::string> command_info);
	void logout();
	void get_products();
	void seller_offer(std::vector<std::string> command_info);
	void get_seller_offers();
	void change_offer(std::vector<std::string> command_info);
	void offers_on_product(std::vector<std::string> command_info);
	void product_detail(std::vector<std::string> command_info);
	void post_comment(std::vector<std::string> command_info);
	void get_product_comments(std::vector<std::string> command_info);
	void generate_discount_code(std::vector<std::string> command_info);
	void add_to_cart(std::vector<std::string> command_info);
	void show_buyer_cart();
	void charge_buyer_wallet(std::vector<std::string> command_info);
	void get_wallet(std::vector<std::string> command_info);
	void submit_cart();
	void get_buyer_orders(std::vector<std::string> command_info);
	void compare_products(std::vector<std::string> command_info);
	void show_admin_offers(std::vector<std::string> command_info);
	void show_buyer_all_offers();
private:
	std::vector<Product*> all_products;
	std::vector<User*> all_users;
	Admin* shop_admin;
	std::vector<User*> active_users;
	int id_products;
	int id_users;
	int id_offer;
};

#endif