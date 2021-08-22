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
	void import_product_html(std::vector<std::string> product_info , std::string product_type);
	void signup(std::vector<std::string> command_info);
	void login(std::vector<std::string> command_info);
	void logout();
	void get_products();
	void seller_offer(std::vector<std::string> command_info);
	void get_seller_offers();
	std::string get_seller_offers_string();
	void change_offer(std::vector<std::string> command_info);
	void offers_on_product(std::vector<std::string> command_info);
	std::string offers_on_product_html(std::vector<std::string> command_info);
	void product_detail(std::vector<std::string> command_info);
	void post_comment(std::vector<std::string> command_info);
	void get_product_comments(std::vector<std::string> command_info);
	void generate_discount_code(std::vector<std::string> command_info);
	void add_to_cart(std::vector<std::string> command_info);
	void show_buyer_cart();
	std::string show_buyer_cart_html();
	void charge_buyer_wallet(std::vector<std::string> command_info);
	void get_wallet(std::vector<std::string> command_info);
	std::string get_wallet_html(std::vector<std::string> command_info);
	void submit_cart();
	void get_buyer_orders(std::vector<std::string> command_info);
	void compare_products(std::vector<std::string> command_info);
	void show_admin_offers(std::vector<std::string> command_info);
	void show_buyer_all_offers();
	int find_user_id_html(std::string email);
	std::string find_user_type_html(std::string email);
	int get_active_user_id();
	std::string get_all_product_html();
	std::vector<Product*> get_all_products_vector_html();
	std::string get_buyer_total_price();
	std::string get_active_user_type();
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