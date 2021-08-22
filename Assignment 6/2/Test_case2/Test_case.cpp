#include "circuit.hpp"
#include <stdexcept>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("`Output` test1"){
    Circuit circuit;
    circuit.add_gate_to_circuit(Nand, 2, 2, 1, 0);
    circuit.add_gate_to_circuit(Not, 1, 4, 3);
    circuit.add_gate_to_circuit(Xor, 2, 7, 6, 5);
    circuit.connect(4,6);
    circuit.connect(2,5);
    circuit.put_value_on_gate_input(0, 0);
    circuit.put_value_on_gate_input(1, 1);
    circuit.put_value_on_gate_input(3, 1);
    REQUIRE(circuit.print_gate_output(7) == true);
    REQUIRE(circuit.print_gate_output(4) == true);
    REQUIRE(circuit.print_gate_output(2) == true);
}