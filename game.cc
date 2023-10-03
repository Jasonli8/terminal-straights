#include <map>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
#include "game.h"
#include "computer.h"
#include "error.h"


// Big 5 /////////////////////////////////////////////////////////////////////

Game::Game(std::vector<char> * ranks, std::vector<char> * suites, int seed, std::vector<bool> computerPlayers, bool advanced) : Subject{}, state{std::make_unique<GameState>(ranks, suites, computerPlayers.size())}, playerList{}, advanced{advanced}, deck{std::make_unique<Deck>(ranks, suites, seed)}, possibleRanks{ranks}, possibleSuites{suites}, cardCount{0}, startingPlayer{0}, ended{false} {
	for (auto c : computerPlayers) {
		if (c) {
			playerList.emplace_back(std::make_unique<Computer>(state.get()));
		} else {
			playerList.emplace_back(std::make_unique<Player>());
		}
	}
}

Game::~Game() {}

// private functions ////////////////////////////////////////////////////////////////

bool Game::checkGameEnd() {
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i]->getDiscardGame() >= 80) return true;
	}
	return false;
}

bool Game::valid_suite(char s) {
	auto it = std::find(possibleSuites->begin(), possibleSuites->end(), s);
	if (it == possibleSuites->end()) return false;
	return true;
}

bool Game::valid_rank(char r) {
	auto it = std::find(possibleRanks->begin(), possibleRanks->end(), r);
	if (it == possibleRanks->end()) return false;
	return true;
}

bool Game::updateCardCount() {
	if (ended) throw GameEnded{};
	if (getTurn() == startingPlayer) {
		cardCount--;
	}

	// check to end game
	if (cardCount == 0) {
		notify("No more cards to be played.");
		notifyAllDiscards();
		if (checkGameEnd()) {
			endgame();
			return false;
		}
		notify("A new round begins!");
		startGame();
		return false;
	}
	return true;
}

void Game::performAction(char turn, Card * target) {
	std::string action = playerList[getTurn()]->move(turn, target);
	notify("Player " + std::to_string(getTurn() + 1) + action);
}

void Game::notifyInvalid() {
	notify("Play is invalid. Try again.");
}

void Game::notifyAllDiscards() {
	for (int i = 0; i < playerList.size(); i++) {
		std::vector<Card *> discard = playerList[i]->getDiscardPile();
		int discardGame = playerList[i]->getDiscardGame();
		int discardRound = playerList[i]->getDiscardRound();
		std::string discardPile = "Player " + std::to_string(i+1) + "'s discards: ";
		for (auto c : discard) {
			discardPile = discardPile + " " + c->getCard();
		}
	notify(discardPile);
	notify("Player " + std::to_string(i+1) + "'s score: " + std::to_string(discardGame - discardRound) + " + " + std::to_string(discardRound) + " = " + std::to_string(discardGame));
	}
}

// public management ////////////////////////////////////////////////////////////////

void Game::startGame() {
	if (ended) throw GameEnded{};
	deck->shuffle();
	state->reset();

	// redistributing cards
	int hand_size = possibleRanks->size() * possibleSuites->size() / playerList.size();
	for (int i = 0; i < playerList.size(); i++) {
		playerList[i]->reset();
		std::vector<Card *> hand;
		for (int j = 0; j < hand_size; j++) {
			if (deck->cardAt(hand_size * i + j)->getCard() == "7S") { // determining starting player
				startingPlayer = i;
				state->setTurn(i);
			}
			hand.emplace_back(deck->cardAt(hand_size * i + j));	
		}
		playerList[i]->setHand(hand);
	}

	cardCount = hand_size;
	notify("Shuffling deck and re-distributing hands.");
	notify();
}

void Game::ragePlayer() {
	if (ended) throw GameEnded{};
	int turnInd = getTurn();
	auto bot = std::make_unique<Computer>(state.get());
	bot->setHand(playerList[turnInd]->getHand());
	if (advanced) bot->changeStrategy(); // enhanced strategy
	playerList[turnInd] = std::move(bot);
	turn(); // have bot automatically start its turn
}

void Game::endgame() {
	if (ended) throw GameEnded{};
	std::vector<int> winnerInd;
	int winning_points = 100;
	notify("The game has come to an end.");
	notify("Points are as follows");
	for (int i = 0; i < playerList.size(); i++) {
		int points = playerList[i]->getDiscardGame();
		notify(" - Player " + std::to_string(i+1) + ": " + std::to_string(points) + "pts");
		if (points == winning_points) {
			winnerInd.push_back(i);
		} else if (points < winning_points) {
			winnerInd.clear();
			winnerInd.push_back(i);
			winning_points = points;
		}
	}
	notify("And the WINNERS are:");
	for (auto i : winnerInd) {
		notify("Player " + std::to_string(i+1) + " wins!");
	}
	ended = true;

}

void Game::turn(char turn, char rank, char suite) {
	if (ended) throw GameEnded{};
	bool proceed = true; // whether game is still in play
	if (turn == 'i') { // invalid input detected by controller
		notifyInvalid();
	} else if (turn != 'c') { // controller detected a human input
		
		// checking if its a possible card
		if (!valid_suite(suite) || !valid_rank(rank)) {
			notifyInvalid();
			return;
		}

		// checking if it is in the player's hand
		bool in_hand = false;
		std::vector<Card *> hand = getHand();
		Card c{rank, suite, possibleRanks, possibleSuites};
		Card * target;
		for (int i = 0; i < hand.size(); i++){
			if (hand[i]->getCard() == c.getCard()) {
				in_hand = true;
				target = hand[i];
				break;
			}
		}
		
		// checking if it is an available play
		bool in_available = false;
		std::vector<std::shared_ptr<Card>> available = state->getAvailablePlays();
		for (int i = 0; i < available.size(); i++) {
			if (available[i]->getCard() == c.getCard()) {
				in_available = true;
				break;
			}
		}

		// can this player perform their desired action
		if (in_available && in_hand && turn == 'p') {
			performAction(turn, target);
			state->playCard(target);
			state->nextTurn();
			proceed = updateCardCount();
			if (proceed) notify();
		} else if (!in_available && in_hand && turn == 'd') {
			if (getLegalPlays().size() != 0) {
				notifyInvalid();
				return;
			}
			performAction(turn, target);
			state->nextTurn();
			proceed = updateCardCount();
			if (proceed) notify();
		} else {
			notifyInvalid();
		}
	} else { // computer move
		performAction('c', nullptr);
		state->nextTurn();
		proceed = updateCardCount();
		if (proceed) notify();
	}
}

// getters //////////////////////////////////////////////////////////////////////////

bool Game::getEnded() {
	return ended;
}

// FOR DEBUGGING AND MARKING
void Game::getDeck() {
	deck->printDeck();
}

std::vector<char> * Game::getPossibleRanks() {return possibleRanks;}

std::vector<char> * Game::getPossibleSuites() {return possibleSuites;}


int Game::getTurn() {
	return state->getTurn();
}

std::map<char, std::vector<int>> Game::getGame() {
	return state->getCurrentGame();
}

std::vector<Card *> Game::getLegalPlays() {
	std::vector<std::shared_ptr<Card>> available = state->getAvailablePlays();
	std::vector<Card *> hand = getHand();
	std::vector<Card *> legalPlays;

	// match cards in availableList to that in hand
	for (int i = 0; i < available.size(); i++) {
		for (int j = 0; j < hand.size(); j++) {
			if (available[i]->getCard() == hand[j]->getCard()) {
				legalPlays.push_back(hand[j]);
				break;
			}
		}
	}

	return legalPlays;
}

std::vector<Card *> Game::getHand() {
	int turn = getTurn();
	return playerList[turn]->getHand();
}

bool Game::isPlayer() {
	return playerList[getTurn()]->isPlayer();
}
