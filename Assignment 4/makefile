CA4_Ali.out : main.o utrello_interface.o User.o List.o Task.o
	      g++ main.o utrello_interface.o User.o List.o Task.o

main.o: main.cpp
	g++ -c main.cpp

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
