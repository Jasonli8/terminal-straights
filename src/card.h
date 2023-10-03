#ifndef _CARD_H_
#define _CARD_H_

// base model for a card

#include <iostream>
#include <vector>

class Card {
	int rank;
	char suite;
	std::vector<char> * possibleRanks;
	std::vector<char> * possibleSuites;

	public:
		Card(char rank, char suite, std::vector<char> * ranks, std::vector<char> * suites);
		Card(int rank, char suite, std::vector<char> * ranks, std::vector<char> * suites);
		~Card();

		///////////////////////////////////////////////////////
		
		// getters
		int getRank() const;
		char getSuite() const;
		
		/////////////////////////////////////////////////////
		
		// gets rank as it appears in possibleRanks
		char getTranslatedRank() const;

		// gets a string representation of the card
		std::string getCard() const;
};

std::ostream &operator<<(std::ostream &out, const Card &c);

#endif
