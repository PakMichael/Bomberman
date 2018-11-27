#include "game.h"
#include "engine.h"




int main(){

	Engine engine;
	Game game;
	game.addSupervisor(&engine);
	game.init();
}