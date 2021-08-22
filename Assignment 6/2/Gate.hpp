#ifndef __GATE_H__
#define __GATE_H__

#include <vector>

#include "Input.hpp"
#include "Output.hpp"
	
class Gate
{
public:
	Gate(Output* _gate_output , std::vector<Input*> _gate_inputs);
	void add_new_input(int previous_id , int new_input);
	void edit_inputs(int input_id , int value);
	
	int get_output_id(){ return gate_output->get_id(); };
	int get_output_value(){ return gate_output->get_value(); };
	bool input_search(int checking_id);
	bool has_valid_input();

	virtual void calculate_output() = 0;
protected:
	Output* gate_output;
	std::vector<Input*> gate_inputs;
};

#endif