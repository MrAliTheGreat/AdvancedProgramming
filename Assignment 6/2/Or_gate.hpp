#ifndef __OR_H__
#define __OR_H__

#include "Gate.hpp"

class Or_gate : public Gate
{
public:
	Or_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif