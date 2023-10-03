#ifndef _PLAYER_H_
#define _PLAYER_H_

// player of the game

#include <vector>
#include <string>
#include "card.h"

class Player {
	std::vector<Card *> hand;
	int discardGame;
	int discardRound;
	std::vector<Card *> discardPile;
	bool player; // are they human or not

	protected:
		void setPlayer(bool b);
	public:
		Player();
		~Player();

		//////////////////////////////////////////////
		
		// setters and getters
		void setHand(std::vector<Card *> new_hand);
		std::vector<Card *> getHand();
		int getDiscardGame();
		int getDiscardRound();
		std::vector<Card *> getDiscardPile();
		bool isPlayer();
		
		////////////////////////////////////////////

		// moves
		void play(Card * c);
		void discard(Card * c);
		virtual std::string move(char turn, Card * c);
		
		// prepare for new round
		void reset();
};

#endif
