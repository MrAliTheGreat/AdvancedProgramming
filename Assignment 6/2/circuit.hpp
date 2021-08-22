#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

using namespace std;

#include "Gate.hpp"
#include "And_gate.hpp"
#include "Or_gate.hpp"
#include "Not_gate.hpp"
#include "Xor_gate.hpp"
#include "Nand_gate.hpp"
#include "Nor_gate.hpp"
#include "Input.hpp"
#include "Output.hpp"

enum GateType {And, Or, Not, Xor, Nand, Nor};

class Circuit
{
public:
    void add_gate_to_circuit(const GateType gate, const int number_of_gate_inputs, const int output_id, 
                                 const int input1_id, ...);
    void connect(const int first_id, const int second_id);
    void put_value_on_gate_input(const int input_id, const int value);
    void print_gate_output(const int output_id);

private:
	std::vector<Gate*> all_gates;
	std::vector<int> all_primary_input_ids;
};

#endif