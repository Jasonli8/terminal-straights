#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

// input interface for game

#include "game.h"

class Controller {
	Game * game;
	
	public:
		Controller(Game * game);
		~Controller();

		///////////////////////////////////////////////////////////
		
		// nextTurn() anticipates input from standard input, translates it and signals game to do something
		// note: strong guaruntee exception safety
		void nextTurn();
};

#endif
