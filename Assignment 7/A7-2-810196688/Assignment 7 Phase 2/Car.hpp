#ifndef __CAR_H__
#define __CAR_H__

#include "Product.hpp"

#include <string>

class Car : public Product
{
public:
	Car(std::string _name , int _id , int _weight , int _num_seats , int _num_cylinders , int _engin_capacity 
			, int _has_park_sensors);
	void get_product_info();
	int get_weight();
	int get_num_seats();
	int get_num_cylinders();
	int get_engin_capacity();
	int get_has_park_sensors();
	void compare(Product* other_product , std::string name_products);
private:
	int weight;
	int num_seats;
	int num_cylinders;
	int engin_capacity;
	int has_park_sensors;
};

#endif