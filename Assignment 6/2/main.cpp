#include "circuit.hpp"

int main()
{
    Circuit circuit;
    circuit.add_gate_to_circuit(Nand, 2, 2, 1, 0);
    circuit.add_gate_to_circuit(Not, 1, 4, 3);
    circuit.add_gate_to_circuit(Xor, 2, 7, 6, 5);
    circuit.connect(4,6);
    circuit.connect(2,5);
    circuit.put_value_on_gate_input(0, 0);
    circuit.put_value_on_gate_input(1, 1);
    circuit.put_value_on_gate_input(3,1);
    circuit.print_gate_output(7); //result should be 1
    circuit.print_gate_output(4);
    circuit.print_gate_output(2);
    return 0;
}

//(a nand b) xor (not c)
//value of a with id 0 is 0
//value of b with id 1 is 1
//value of c with id 3 is 1
