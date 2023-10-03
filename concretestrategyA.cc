#include <vector>
#include <string>
#include "concretestrategyA.h"

// Strategy ///////////////////////////////

std::string ConcreteStrategyA::plan(Computer * bot) {
	// getting states
	std::vector<Card *> hand = bot->getHand();
	std::vector<std::shared_ptr<Card>> availablePlays = bot->getGame()->getAvailablePlays();
	
	// finding a playable card
	for (auto c : hand) {
		for (int i = 0; i < availablePlays.size(); i++) {
			if (c->getCard() == availablePlays[i]->getCard()) {
				std::string action = " plays card " + c->getCard() + ".";
				bot->play(c);
				bot->getGame()->playCard(c);
				return action;
			}
		}
	}

	// forced to discard a card
	std::string action = " discards a card.";
	bot->discard(hand[0]);
	return action;
}
