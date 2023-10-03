#include <string>
#include <vector>
#include <algorithm>
#include "card.h"

// Big 5 ////////////////////////////////////////////////////

Card::Card(char r, char s, std::vector<char> * ranks, std::vector<char> * suites) : rank{0}, suite{s}, possibleRanks{ranks}, possibleSuites{suites} {
	rank = std::find(possibleRanks->begin(), possibleRanks->end(), r) - possibleRanks->begin();
}

Card::Card(int rank, char suite, std::vector<char> * ranks, std::vector<char> * suites) : rank{rank}, suite{suite}, possibleRanks{ranks}, possibleSuites{suites} {}

Card::~Card() {}

// Getters ///////////////////////////////////////////////

int Card::getRank() const {
	return rank;
}

char Card::getSuite() const {
	return suite;
}


// Operations /////////////////////////////////////////
std::ostream& operator<<(std::ostream& out, const Card &c) {
	out<<c.getCard();
	return out;
}

// Transator /////////////////////////////////////////

char Card::getTranslatedRank() const {
	return possibleRanks->at(rank);
}

std::string Card::getCard() const {
	std::string s = {possibleRanks->at(rank), suite};
	return s;
}
