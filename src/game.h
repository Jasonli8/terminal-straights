#ifndef _GAME_H_
#define _GAME_H_

// this is the main interface for the game

#include <vector>
#include <memory>
#include "gamestate.h"
#include "deck.h"
#include "player.h"
#include "subject.h"

class Game : public Subject {
	std::unique_ptr<GameState> state;
	std::vector<std::unique_ptr<Player>> playerList;
	bool advanced; // whether advanced AI computers should replace ragequitters
	std::unique_ptr<Deck> deck;
	std::vector<char> * possibleRanks;
	std::vector<char> * possibleSuites;
	int cardCount; // max number of cards in a hand across all players
	int startingPlayer; // index of which player moved first
	bool ended; // end bit
	
	/////////////////////////////////////////////////
	
	// check if game has ended
	bool checkGameEnd();

	// check if s is in possibleSuites
	bool valid_suite(char s);
	// check if r is in possibleRanks
	bool valid_rank(char r);

	// updates cardCount to reflex current max, and starts a new round if all players have 0 cards left
	bool updateCardCount();

	// has current player perform turn with target
	void performAction(char turn, Card * target);

	// preset notify(message)
	void notifyInvalid();
	void notifyAllDiscards();

	public:
		Game(std::vector<char> * ranks, std::vector<char> * suites, int seed, std::vector<bool> computerPlayers, bool advanced);
		~Game();

		//////////////////////////////////////////////////////

		// starts a new round
		void startGame();

		// replaces current player with a bot
		void ragePlayer();

		// ends the game
		void endgame();

		// verifies move, then adjust player and game states accordingly
		void turn(char turn = 'c', char rank = 0, char suite = 0);

		///////////////////////////////////////////////////////

		// standard getters
		bool getEnded();
		// prints deck in lines of 13 (FOR DEBUGGING AND MARKING)
		void getDeck();
		std::vector<char> * getPossibleRanks();
		std::vector<char> * getPossibleSuites();

		
		// get index of player whose turn it is
		int getTurn();
		
		// get state of current playing field
		std::map<char, std::vector<int>> getGame();

		// gets list of plays current player can play
		std::vector<Card *> getLegalPlays();

		// get hand of current player
		std::vector<Card *> getHand();

		// get whether or not current player is human or not
		bool isPlayer();
};

#endif
