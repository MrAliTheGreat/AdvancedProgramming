#ifndef __NAND_H__
#define __NAND_H__

#include "Gate.hpp"

class Nand_gate : public Gate
{
public:
	Nand_gate(Output* _gate_output , std::vector<Input*> _gate_inputs)
		:Gate(_gate_output , _gate_inputs){};
	virtual void calculate_output();
};


#endif