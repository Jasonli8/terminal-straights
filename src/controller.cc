#include <iostream>
#include <string>
#include "controller.h"

/////////////////////////////////////////////////////////////////////
//
Controller::Controller(Game * game) : game{game} {}

Controller::~Controller() {}

///////////////////////////////////////////////////////////////////

void Controller::nextTurn() {
	// first distinguish human from bot turn
	if (game->isPlayer()) { // human

		// get command
		std::string move;
		std::cin>>move;
		
		if (std::cin.fail()) {
			game->endgame();
		} else {
			if (move == "play") {
				std::cin>>move;
				if (std::cin.fail()) {
					game->endgame();
				}
				game->turn('p', move[0], move[1]);
			} else if (move == "discard") {
				std::cin>>move;
				if(std::cin.fail()) {
					game->endgame();
				}
				game->turn('d', move[0], move[1]);
			} else if (move == "deck") {
				game->getDeck();
			} else if (move == "quit") {
				game->endgame();
			} else if (move == "ragequit") {
				game->ragePlayer();
			} else {
				game->turn('i');
			}
		}
	} else { // bot
		game->turn();
	}
}
