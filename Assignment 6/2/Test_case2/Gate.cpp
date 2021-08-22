#include "Gate.hpp"
#include <iostream>

Gate::Gate(Output* _gate_output , std::vector<Input*> _gate_inputs){
	gate_output = _gate_output;
	gate_inputs = _gate_inputs;
}

bool Gate::input_search(int checking_id){
	for(int i = 0 ; i < gate_inputs.size() ; i++){
		if(gate_inputs[i]->get_id() == checking_id){
			return true;
		}
	}
	return false;
}

void Gate::add_new_input(int previous_id , int new_input){
	for(int i = 0 ; i < gate_inputs.size() ; i++){
		if(gate_inputs[i]->get_id() == previous_id){
			gate_inputs[i]->set_id(new_input);
		}
	}
}

void Gate::edit_inputs(int input_id , int value){
	for(int i = 0 ; i < gate_inputs.size() ; i++){
		if(gate_inputs[i]->get_id() == input_id){
			gate_inputs[i]->set_value(value);
		}
	}
}

bool Gate::has_valid_input(){
	for(int i = 0 ; i < gate_inputs.size() ; i++){
		if(gate_inputs[i]->get_value() == -1){
			return false;
		}
	}
	return true;
}