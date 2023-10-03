#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

// container for the state of the playing field of current round

#include <vector>
#include <map>
#include <memory>

class Card;

class GameState {
	const int players; // how many players are in the game
	int playerTurn; // turn refers to the index of a player in a vector of players (player number - 1)
	std::map<char, std::vector<int>> currentGame;
	std::vector<std::shared_ptr<Card>> availablePlays;
	std::vector<char> * ranks;
	std::vector<char> * suites;

	public:
		GameState(std::vector<char> * ranks, std::vector<char> * suites, int players = 4);
		~GameState();

		///////////////////////////////////////////////////////////
		
		// getters and setters
		int getTurn();
		void setTurn(int playerInd);
		std::map<char, std::vector<int>> getCurrentGame();
		std::vector<std::shared_ptr<Card>> getAvailablePlays();
		
		//////////////////////////////////////////////////////////

		// updates the playerTurn counter to the next player
		void nextTurn();

		// adjusts the currentGame and availablePlays to after a card has been played
		void playCard(Card * c);

		// restart the GameState to its original state at the beginning of the round
		void reset();
};

#endif
