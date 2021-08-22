RSDLFLAG += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

CA4_Ali.out : main.o Ground.o Tank.o Bullet.o Powerup.o rsdl.o
	      g++ main.o rsdl.o $(RSDLFLAG) Ground.o Tank.o Bullet.o Powerup.o

main.o: main.cpp Ground.hpp src/rsdl.hpp
	g++ -c main.cpp

Ground.o: Ground.cpp src/rsdl.hpp Tank.hpp Bullet.hpp Powerup.hpp
	g++ -c Ground.cpp

Tank.o: Tank.cpp src/rsdl.hpp Bullet.hpp Powerup.hpp
	g++ -c Tank.cpp

Bullet.o: Bullet.cpp src/rsdl.hpp
	g++ -c Bullet.cpp

Powerup.o: Powerup.cpp src/rsdl.hpp
	g++ -c Powerup.cpp

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	g++ -c src/rsdl.cpp

clean: 
	rm *.o 
