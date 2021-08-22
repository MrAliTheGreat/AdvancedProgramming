#include "Xor_gate.hpp"
#include <iostream>

void Xor_gate::calculate_output(){
	int result = gate_inputs[0]->get_value() ^ gate_inputs[1]->get_value();
	for(int i = 2 ; i < gate_inputs.size() ; i++){
		result = result ^ gate_inputs[i]->get_value();
	}
	gate_output->set_value(result);
}