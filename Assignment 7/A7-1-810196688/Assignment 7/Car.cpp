#include "Car.hpp"
#include <iostream>

Car::Car(std::string _name , int _id , int _weight , int _num_seats , int _num_cylinders , int _engin_capacity 
			, int _has_park_sensors) : Product(_name , _id){

	weight = _weight;
	num_seats = _num_seats;
	num_cylinders = _num_cylinders;
	engin_capacity = _engin_capacity;
	has_park_sensors = _has_park_sensors;
}

void Car::get_product_info(){
	std::cout << "Weight: " << weight << "\n";
	std::cout << "Num. of Seats: " << num_seats << "\n";
	std::cout << "Num. of Cylinders: " << num_cylinders << "\n";
	std::cout << "Engine Capacity: " << engin_capacity << "\n";
	std::cout << "Reverse Parking Sensors: " << has_park_sensors << "\n";
}

int Car::get_weight(){ return weight; }

int Car::get_num_seats(){ return num_seats; }

int Car::get_num_cylinders(){ return num_cylinders; }

int Car::get_engin_capacity(){ return engin_capacity; }

int Car::get_has_park_sensors(){ return has_park_sensors; }

void Car::compare(Product* other_product , std::string name_products){
	if(other_product->get_num_seats() == -1){
		throw incomparable_error();
		return;
	}
	std::cout << name_products;
	std::cout << "Weight: " << weight << " | " << other_product->get_weight() << "\n";
	std::cout << "Num. of Seats: " << num_seats << " | " << other_product->get_num_seats() << "\n";
	std::cout << "Num. of Cylinders: " << num_cylinders << " | " << other_product->get_num_cylinders() << "\n";
	std::cout << "Engine Capacity: " << engin_capacity << " | " << other_product->get_engin_capacity() << "\n";
	std::cout << "Reverse Parking Sensors: " << has_park_sensors << " | " << other_product->get_has_park_sensors() << "\n";
}