#include "And_gate.hpp"

void And_gate::calculate_output(){
	int result = 1 & gate_inputs[0]->get_value();
	for(int i = 1 ; i < gate_inputs.size() ; i++){
		result = result & gate_inputs[i]->get_value();
	}
	gate_output->set_value(result);
}