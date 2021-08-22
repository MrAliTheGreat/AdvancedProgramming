#include "Phone.hpp"
#include <iostream>

Phone::Phone(std::string _name , int _id , int _weight , double _CPU_frequency , int _built_in_memory , int _RAM 
				, double _display_size , int _camera_resolution , std::string _OS) : Product(_name , _id) {

	weight = _weight;
	CPU_frequency = _CPU_frequency;
	built_in_memory = _built_in_memory;
	RAM = _RAM;
	display_size = _display_size;
	camera_resolution = _camera_resolution;
	OS = _OS;
}

void Phone::get_product_info(){
	std::cout << "Weight: " << weight << "\n";
	std::cout << "CPU Frequency: " << CPU_frequency << "\n";
	std::cout << "Built-in Memory: " << built_in_memory << "\n";
	std::cout << "RAM: " << RAM << "\n";
	std::cout << "Display Size: " << display_size << "\n";
	std::cout << "Camera Resolution: " << camera_resolution << "\n";
	std::cout << "Operating System: " << OS << "\n";
}

int Phone::get_weight(){ return weight; }

double Phone::get_CPU_frequency(){ return CPU_frequency; }

int Phone::get_built_in_memory(){ return built_in_memory; }

int Phone::get_RAM(){ return RAM; }

double Phone::get_display_size_phone(){ return display_size; }

int Phone::get_camera_resolution(){ return camera_resolution; }

std::string Phone::get_OS(){ return OS; }

void Phone::compare(Product* other_product , std::string name_products){
	if(other_product->get_camera_resolution() == -1){
		throw incomparable_error();
		return;
	}
	std::cout << name_products;
	std::cout << "Weight: " << weight << " | " << other_product->get_weight() << "\n";
	std::cout << "CPU Frequency: " << CPU_frequency << " | " << other_product->get_CPU_frequency() << "\n";
	std::cout << "Built-in Memory: " << built_in_memory << " | " << other_product->get_built_in_memory() << "\n";
	std::cout << "RAM: " << RAM << " | " << other_product->get_RAM() << "\n";
	std::cout << "Display Size: " << display_size << " | " << other_product->get_display_size_phone() << "\n";
	std::cout << "Camera Resolution: " << camera_resolution << " | " << other_product->get_camera_resolution() << "\n";
	std::cout << "Operating System: " << OS << " | " << other_product->get_OS() << "\n";	
}