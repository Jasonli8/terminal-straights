#include "player.h"

// Big 5 //////////////////////////////////////////////////

Player::Player() : hand{}, discardGame{0}, discardRound{0}, discardPile{}, player{true} {}

Player::~Player() {}

// Getters and Setters /////////////////////////////////////////////////////////////////

void Player::setHand(std::vector<Card *> new_hand) {
	hand.clear();
	for (auto c : new_hand) {
		hand.push_back(c);
	}
}

std::vector<Card *> Player::getHand() {
	return hand;
}

int Player::getDiscardGame() {
	return discardGame;
}

int Player::getDiscardRound() {
	return discardRound;
}

std::vector<Card *> Player::getDiscardPile() {
	return discardPile;
}	

bool Player::isPlayer() {
	return player;
}

// Private Setter //////////////////////////////////////////

void Player::setPlayer(bool b) {
	player = b;
}

// Player Manipulation //////////////////////////////////////

void Player::play(Card * c) {
	for (int i = 0; i < hand.size(); i++) {
		if (c == hand.at(i)) {
			hand.erase(hand.begin() + i);
			return;
		}
	}
}

void Player::discard(Card * c) {
	discardGame += c->getRank() + 1;
	discardRound += c->getRank() + 1;
	discardPile.push_back(c);
	play(c);
}

std::string Player::move(char turn, Card * c) {
	if (turn == 'p') {
		play(c);
		return " plays card " + c->getCard() + ".";
	} else if (turn == 'd') {
		discard(c);
		return " discards a card.";
	}
	return " made an invalid play.";
}

void Player::reset() {
	discardPile.clear();
	discardRound = 0;
}
