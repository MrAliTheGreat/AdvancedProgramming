#ifndef __NOT_H__
#define __NOT_H__

#include "Gate.hpp"

class Not_gate : public Gate
{
public:
	Not_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif