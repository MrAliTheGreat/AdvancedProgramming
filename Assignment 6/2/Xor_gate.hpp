#ifndef __XOR_H__
#define __XOR_H__

#include "Gate.hpp"

class Xor_gate : public Gate
{
public:
	Xor_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif