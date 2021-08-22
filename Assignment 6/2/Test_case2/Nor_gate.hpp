#ifndef __NOR_H__
#define __NOR_H__

#include "Gate.hpp"

class Nor_gate : public Gate
{
public:
	Nor_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif