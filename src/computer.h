#ifndef _COMPUTER_H_
#define _COMPUTER_H_

// computerized player

#include <vector>
#include <memory>
#include "card.h"
#include "player.h"
#include "gamestate.h"
#include "strategy.h"

class Computer : public Player {
	std::unique_ptr<Strategy> strat;
	GameState * game;

	public:
		Computer(GameState * game);
		~Computer();
		
		/////////////////////////////////////

		// getter
		GameState * getGame();

		////////////////////////////////////
		
		// makes a move
		std::string move(char turn, Card *c) override;
		// change how to move
		void changeStrategy();
};

#endif
