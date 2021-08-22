CA4_Ali.out : main.o tree.o Operator.o Operand.o Add_Operator.o Multiply_Operator.o Not_Operator.o Median_Operator.o
	      g++ -std=c++11 main.o tree.o Operator.o Operand.o Add_Operator.o Multiply_Operator.o Not_Operator.o Median_Operator.o

main.o: main.cpp tree.hpp
	g++ -c main.cpp

tree.o: tree.cpp tree.hpp Operator.hpp Operand.hpp
	g++ -c tree.cpp

Operator.o: Operator.cpp Operator.hpp Operand.hpp
	g++ -c Operator.cpp

Operand.o: Operand.cpp Operand.hpp
	g++ -c Operand.cpp

Add_Operator.o: Add_Operator.cpp Add_Operator.hpp Operator.hpp Operand.hpp
	g++ -c Add_Operator.cpp

Multiply_Operator.o: Multiply_Operator.cpp Multiply_Operator.hpp Operator.hpp Operand.hpp
	g++ -c Multiply_Operator.cpp

Not_Operator.o: Not_Operator.cpp Not_Operator.hpp Operator.hpp Operand.hpp
	g++ -c Not_Operator.cpp

Median_Operator.o: Median_Operator.cpp Median_Operator.hpp Operator.hpp Operand.hpp
	g++ -c Median_Operator.cpp

clean:
	rm *.o
