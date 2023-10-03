#include <vector>
#include <string>
#include "concretestrategyB.h"

// Strategy ////////////////////////////////////////////
std::string ConcreteStrategyB::plan(Computer * bot) {
	std::vector<Card *> hand = bot->getHand();
	std::vector<std::shared_ptr<Card>> availablePlays = bot->getGame()->getAvailablePlays();
	Card * target_high = nullptr;
	Card * target_low = hand.at(0);
	bool playable = false;

	for (auto c : hand) {

		// replacing with lowest card
		if (c->getRank() < target_low->getRank()) {
			target_low = c;
		}

		// finding highest playable card
		for (int i = 0; i < availablePlays.size(); i++) {
			if (c->getCard() == availablePlays[i]->getCard()) {
				if (target_high == nullptr || c->getRank() > target_high->getRank()) {
					target_high = c;
					playable = true;
				}
			}
		}
	}

	// moving
	if (playable) {
		std::string action = " plays card " + target_high->getCard() + ".";
		bot->play(target_high);
		bot->getGame()->playCard(target_high);
		return action;
	} else {
		std::string action = " discards a card.";
		bot->discard(target_low);
		return action;
	}
}
