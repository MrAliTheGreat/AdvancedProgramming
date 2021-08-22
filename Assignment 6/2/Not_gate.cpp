#include "Not_gate.hpp"

void Not_gate::calculate_output(){
	gate_output->set_value(!gate_inputs[0]->get_value());
}