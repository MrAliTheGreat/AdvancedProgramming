#include <iostream>
#include <fstream>

using namespace std;

#include "Ground.hpp"
#include "src/rsdl.hpp"

int main(int argc , char* argv[]){
	Ground game_ground(argv[1]);
	game_ground.make_ground();
	game_ground.spawn_tanks();
	game_ground.game_engine();
	game_ground.ending();
	return 0;
}