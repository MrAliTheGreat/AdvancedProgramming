CA4_Ali.out : main.o Circuit.o Gate.o Output.o Input.o And_gate.o Or_gate.o Not_gate.o Xor_gate.o Nand_gate.o Nor_gate.o
	      g++ -std=c++11 main.o Circuit.o Gate.o Output.o Input.o And_gate.o Or_gate.o Not_gate.o Xor_gate.o Nand_gate.o Nor_gate.o

main.o: main.cpp circuit.hpp
	g++ -c main.cpp

tree.o: Circuit.cpp circuit.hpp Gate.hpp Input.hpp Output.hpp
	g++ -c Circuit.cpp

Gate.o: Gate.cpp Gate.hpp Input.hpp Output.hpp
	g++ -c Gate.cpp

Output.o: Output.cpp
	g++ -c Output.cpp

Input.o: Input.cpp
	g++ -c Input.cpp

And_gate.o: And_gate.cpp And_gate.hpp Gate.hpp
	g++ -c And_gate.cpp

Or_gate.o: Or_gate.cpp Or_gate.hpp Gate.hpp
	g++ -c Or_gate.cpp

Not_gate.o: Not_gate.cpp Not_gate.hpp Gate.hpp
	g++ -c Not_gate.cpp

Xor_gate.o: Xor_gate.cpp Xor_gate.hpp Gate.hpp
	g++ -c Xor_gate.cpp

Nand_gate.o: Nand_gate.cpp Nand_gate.hpp Gate.hpp
	g++ -c Nand_gate.cpp

Nor_gate.o: Nor_gate.cpp Nor_gate.hpp Gate.hpp
	g++ -c Nor_gate.cpp

clean: 
	rm *.o
