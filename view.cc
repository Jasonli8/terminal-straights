#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "card.h"
#include "view.h"

/////////////////////////////////////////////////////////////////

View::View(Game * game) : Observer{}, game{game} {}

View::~View() {}

////////////////////////////////////////////////////////////////
//
void View::notify() {
	int turn = game->getTurn();
	std::cout<<"It's Player "<<turn+1<<"'s turn to play."<<std::endl;
	
	// printing of currentGame
	std::map<char, std::vector<int>> state = game->getGame();
	std::cout<<"Cards on the table:"<<std::endl;
	for (auto p : state) {
		std::cout<<std::setw(10);
		if (p.first == 'C') {
			std::cout<<"Clubs:";
		} else if (p.first == 'D') {
			std::cout<<"Diamonds:";
		} else if (p.first == 'H') {
			std::cout<<"Hearts:";
		} else if (p.first == 'S') {
			std::cout<<"Spades:";
		}

		for (int i = 0; i < p.second.size(); i++) {
			Card c{p.second[i], p.first, game->getPossibleRanks(), game->getPossibleSuites()};
			std::cout<<" "<<c.getTranslatedRank();
		}
		std::cout<<std::endl;
	}

	// printing current player info
	std::cout<<"Your hand:";
	std::vector<Card*> hand = game->getHand();
	for (auto c : hand) {
		std::cout<<" "<<*c;
	}
	std::cout<<std::endl;
	std::cout<<"Legal plays:";
	std::vector<Card *> available = game->getLegalPlays();
	for (auto c : available) {
		std::cout<<" "<<*c;
	}
	std::cout<<std::endl;
	std::cout<<"Move?:"<<std::endl;
}

void View::notify(std::string message) {
	std::cout<<message<<std::endl;
}
