#ifndef __PHONE_H__
#define __PHONE_H__

#include "Product.hpp"

#include <string>

class Phone : public Product
{
public:
	Phone(std::string _name , int _id , int _weight , double _CPU_frequency , int _built_in_memory , int _RAM 
			, double _display_size , int _camera_resolution , std::string _OS);
	void get_product_info();
	std::string get_product_info_html();
	int get_weight();
	double get_CPU_frequency();
	int get_built_in_memory();
	int get_RAM();
	double get_display_size_phone();
	int get_camera_resolution();
	std::string get_OS();
	void compare(Product* other_product , std::string name_products);
private:
	int weight;
	double CPU_frequency;
	int built_in_memory;
	int RAM;
	double display_size;
	int camera_resolution;
	std::string OS;
};

#endif