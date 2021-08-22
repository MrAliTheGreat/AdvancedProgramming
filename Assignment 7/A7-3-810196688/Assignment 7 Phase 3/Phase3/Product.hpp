#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include "Comment.hpp"
#include "Program_errors.hpp"

#include <string>
#include <vector>

class Product
{
public:
	Product(std::string _name , int _product_id);
	int get_product_id(){ return product_id; };
	std::string get_product_name(){ return name; };
	void set_quantity(int quantity);
	void set_unit_price(double price);
	virtual void get_product_info() = 0;
	virtual std::string get_product_info_html() = 0;
	void add_new_product_comment(std::string new_comment , std::string username);
	void show_product_comments();
	virtual int get_weight();
	virtual int get_num_seats();
	virtual int get_num_cylinders();
	virtual int get_engin_capacity();
	virtual int get_has_park_sensors();
	virtual int get_display_size_tv();
	virtual std::string get_screen_type();
	virtual std::string get_resolution();
	virtual int get_has_3D();
	virtual int get_has_HDR();
	virtual double get_CPU_frequency();
	virtual int get_built_in_memory();
	virtual int get_RAM();
	virtual double get_display_size_phone();
	virtual int get_camera_resolution();
	virtual std::string get_OS();
	virtual void compare(Product* other_product , std::string name_products) = 0;
protected:
	std::string name;
	int product_id;
	int quantity_seller;
	double unit_price_seller;
	std::vector<Comment*> all_product_comments;
};

#endif