#ifndef __TV_H__
#define __TV_H__

#include "Product.hpp"

#include <string>

class TV : public Product
{
public:
	TV(std::string _name , int _id , int _display_size , std::string _screen_type , std::string _resolution
		 , int _has_3D , int _has_HDR);
	void get_product_info();
	int get_display_size_tv();
	std::string get_screen_type();
	std::string get_resolution();
	int get_has_3D();
	int get_has_HDR();
	void compare(Product* other_product , std::string name_products);
private:
	int display_size;
	std::string screen_type;
	std::string resolution;
	int has_3D;
	int has_HDR;
};

#endif