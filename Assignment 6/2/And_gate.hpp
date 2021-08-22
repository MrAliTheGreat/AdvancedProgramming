#ifndef __AND_H__
#define __AND_H__

#include "Gate.hpp"

class And_gate : public Gate
{
public:
	And_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif