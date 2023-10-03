#include <algorithm>
#include <string>
#include "card.h"
#include "gamestate.h"

// Big 5 ////////////////////////////////////////////////////////////

GameState::GameState(std::vector<char> * ranks, std::vector<char> * suites, int players) : players{players}, playerTurn{0}, currentGame{}, availablePlays{}, ranks{ranks}, suites{suites} {
	for (auto s : *suites) {
		currentGame[s].clear();
	}
	availablePlays.emplace_back(std::make_shared<Card>(6, 'S', ranks, suites)); // first play must be 7S
}

GameState::~GameState() {}

// Getters and Setters //////////////////////////////////////////////

int GameState::getTurn() {return playerTurn;}

void GameState::setTurn(int turnInd) {
	playerTurn = turnInd % players;
}

std::map<char, std::vector<int>> GameState::getCurrentGame() {return currentGame;}

std::vector<std::shared_ptr<Card>> GameState::getAvailablePlays() {return availablePlays;}

// Public State Manipulators ///////////////////////////////////////

void GameState::nextTurn() {
	playerTurn++;
	if (playerTurn == players) playerTurn = 0;
}

void GameState::playCard(Card * c) {
	int rank = c->getRank();

	// placing card on vield
	currentGame[c->getSuite()].emplace_back(c->getRank());
	std::sort(currentGame[c->getSuite()].begin(), currentGame[c->getSuite()].end());
	
	// updating available plays
	int i = 0;
	for (auto ap : availablePlays) {
		if (ap->getCard() == c->getCard()) {
			availablePlays.erase(availablePlays.begin() + i);
			break;
		} else {
			i++;
		}
	}

	// open cards away from 7 on appropriate suite
	if (rank != 0 && rank != 12) {
		if (rank <= 6) {
			availablePlays.emplace_back(std::make_shared<Card>(rank - 1, c->getSuite(), ranks, suites));
		}
		if (rank >= 6) {
			availablePlays.emplace_back(std::make_shared<Card>(rank + 1, c->getSuite(), ranks, suites));
		}
	}

	// first play must be 7S
	if (c->getCard() == "7S") {
		for (int i = 0; i < suites->size(); i++) {
			if (suites->at(i) != 'S') availablePlays.emplace_back(std::make_shared<Card>(6, suites->at(i), ranks, suites));
		}
	}
}

void GameState::reset() {
	availablePlays.clear();
	for (auto s : *suites) {
		currentGame[s].clear();
	}
	availablePlays.emplace_back(std::make_shared<Card>(6, 'S', ranks, suites));
	playerTurn = 0;
}
