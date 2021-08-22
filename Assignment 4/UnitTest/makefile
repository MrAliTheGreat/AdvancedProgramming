CA4_Ali.out : Test_case.o utrello_interface.o User.o List.o Task.o
	      g++ Test_case.o utrello_interface.o User.o List.o Task.o

Test_case.o: Test_case.cpp
	g++ -c Test_case.cpp

utrello_interface.o: utrello_interface.cpp
	g++ -c utrello_interface.cpp

User.o: User.cpp
	g++ -c User.cpp

List.o: List.cpp
	g++ -c List.cpp

Task.o: Task.cpp
	g++ -c Task.cpp

clean: 
	rm *.o 
