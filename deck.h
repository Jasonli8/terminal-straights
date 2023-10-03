#ifndef _DECK_H_
#define _DECK_H_

// the games deck, main container for cards in play

#include <vector>
#include <memory>
#include "card.h"

class Deck {
	std::vector<std::unique_ptr<Card>> cards;
	int seed;

	public:
		Deck(std::vector<char> * ranks, std::vector<char> * suites, int seed);
		~Deck();
		
		//////////////////////////////////////////////////////////////
		
		// randomizes deck order
		void shuffle();

		// prints deck on lines of 13 (FOR DEBUGGING AND MARKING)
		void printDeck();

		////////////////////////////////////////////////////////////

		// returns card at index in current deck state
		Card * cardAt(int index);
};

#endif
