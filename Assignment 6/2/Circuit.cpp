#include "circuit.hpp"

#include<cstdarg>
#include<iostream>
#include <stdlib.h>

#define MESSAGE "The current output of gate with id "
#define MESSAGE_SPACER " is "
#define MESSAGE_SEPARATOR "\n"

class existing_ID_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Duplicate ID\n";
	}
};

class Not_gate_input_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Not should have 1 input\n";
	}
};

class connection_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Override by two driver\n";
	}
};

class invalid_value_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Invalid value\n";
	}
};

class invalid_ID_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Invalid ID\n";
	}
};

class initialization_exception : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Bad initialization\n";
	}
};

void check_duplicate_output_id(std::vector<Gate*> all_gates , int output_id){
	for(int i = 0 ; i < all_gates.size() ; i++){
		if(all_gates[i]->get_output_id() == output_id){
			throw existing_ID_exception();
		}
	}
}

void check_duplicate_input_id(std::vector<Gate*> all_gates , std::vector<Input*> inputs){
	for(int i = 0 ; i < all_gates.size() ; i++){
		for(int j = 0 ; j < inputs.size() ; j++){
			if(all_gates[i]->input_search(inputs[j]->get_id())){
				throw existing_ID_exception();
			}
		}
	}
}

void Circuit::add_gate_to_circuit(const GateType gate, const int number_of_gate_inputs, const int output_id, const int input1_id, ...){
	std::vector<Input*> inputs;

	va_list args;
	va_start(args, input1_id);
	inputs.push_back(new Input(input1_id));
	for(int i = 1 ; i < number_of_gate_inputs ; i++){
	    inputs.push_back(new Input(va_arg(args, int)));
	}
	va_end(args);

	for(int i = 0 ; i < inputs.size() ; i++){
		all_primary_input_ids.push_back(inputs[i]->get_id());
	}

	try{
		check_duplicate_output_id(all_gates , output_id);
		check_duplicate_input_id(all_gates , inputs);
	}catch(existing_ID_exception ex1){
		cerr << ex1.what();
		abort();
	}
	Output* new_output = new Output(output_id);
	switch(gate){
		case 0:
			{
			    And_gate* new_gate = new And_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}
		case 1:
			{
				Or_gate* new_gate = new Or_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}	
		case 2:
			{
				try{
					if(inputs.size() > 1){
						throw Not_gate_input_exception();
					}
				}catch(Not_gate_input_exception ex2){
					cerr << ex2.what();
					abort();
				}
				Not_gate* new_gate = new Not_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}
		case 3:
			{
				Xor_gate* new_gate = new Xor_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}
		case 4:
			{
				Nand_gate* new_gate = new Nand_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}
		case 5:
			{
				Nor_gate* new_gate = new Nor_gate(new_output , inputs);
			    all_gates.push_back(new_gate);
				break;
			}
	}
}

bool is_ouput_id(std::vector<Gate*> gates , int out_id){
	for(int i = 0 ; i < gates.size() ; i++){
		if(gates[i]->get_output_id() == out_id){
			return true;
		}
	}
	return false;
}

void Circuit::connect(const int first_id, const int second_id){
	try{
		if(is_ouput_id(all_gates , first_id) && is_ouput_id(all_gates , second_id)){
			throw connection_exception();
		}
	}catch(connection_exception ex3){
		cerr << ex3.what();
		abort();
	}
	if(is_ouput_id(all_gates , first_id)){
		for(int i = 0 ; i < all_gates.size() ; i++){
			if(all_gates[i]->input_search(second_id)){
				all_gates[i]->add_new_input(second_id , first_id);
			}
		}
	}else{
		for(int i = 0 ; i < all_gates.size() ; i++){
			if(all_gates[i]->input_search(first_id)){
				all_gates[i]->add_new_input(first_id , second_id);
			}
		}
	}
}

bool input_id_exists(std::vector<Gate*> all_gates , int input_id){
	for(int i = 0 ; i < all_gates.size() ; i++){
		if(all_gates[i]->input_search(input_id)){
			return true;
		}
	}
	throw connection_exception();
	return false;
}

bool input_id_primarily_exists(std::vector<int> all_primary_input_ids , int input_id){
	for(int i = 0 ; i < all_primary_input_ids.size() ; i++){
		if(all_primary_input_ids[i] == input_id){
			return true;
		}
	}
	throw invalid_ID_exception();
	return false;
}

void Circuit::put_value_on_gate_input(const int input_id, const int value){
	try{
		input_id_primarily_exists(all_primary_input_ids , input_id);
	}catch(invalid_ID_exception ex4){
		cerr << ex4.what();
		abort();
	}

	try{
		input_id_exists(all_gates , input_id);
	}catch(connection_exception ex5){
		cerr << ex5.what();
		abort();
	}

	try{
		if(!(value == 0 || value == 1)){
			throw invalid_value_exception();
		}
	}catch(invalid_value_exception ex6){
		cerr << ex6.what();
		abort();
	}

	for(int i = 0 ; i < all_gates.size() ; i++){
		if(all_gates[i]->input_search(input_id)){
			all_gates[i]->edit_inputs(input_id , value);
		}
	}
}

void Circuit::print_gate_output(const int output_id){
	try{
		if(!is_ouput_id(all_gates , output_id)){
			throw invalid_ID_exception();
		}
	}catch(invalid_ID_exception ex7){
		cerr << ex7.what();
		abort();
	}

	for(int i = 0 ; i < all_gates.size() ; i++){
		all_gates[i]->calculate_output();
		Gate* changed_gate = all_gates[i];
		for(int j = 0 ; j < all_gates.size() ; j++){
			if(all_gates[j]->input_search(changed_gate->get_output_id())){
				all_gates[j]->edit_inputs(changed_gate->get_output_id() , changed_gate->get_output_value());
			}
		}
	}

	try{
		for(int i = 0 ; i < all_gates.size() ; i++){
			if(all_gates[i]->get_output_id() == output_id){
				if(!all_gates[i]->has_valid_input()){
					throw initialization_exception();
				}
			}
		}
	}catch(initialization_exception ex8){
		cerr << ex8.what();
		abort();
	}

	for(int i = 0 ; i < all_gates.size() ; i++){
		if(all_gates[i]->get_output_id() == output_id){
			std::cout << MESSAGE + std::to_string(output_id) + MESSAGE_SPACER + std::to_string(all_gates[i]->get_output_value()) + MESSAGE_SEPARATOR;
		}
	}
}