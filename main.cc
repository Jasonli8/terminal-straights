#include <chrono>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "game.h"
#include "controller.h"
#include "view.h"
#include "error.h"

//////////////////////////////////////////////////////////////////

// operation(path) outputs the proper calling of this program
void operation(std::string path) {
	std::cerr<<"Invalid arguements."<<std::endl;
	std::cerr<<"Program is used as follows: "<<path<<" <options> <seed>"<<std::endl;
	std::cerr<<"Optional parameters:"<<std::endl;
	std::cerr<<"	<options>:"<<std::endl;
	std::cerr<<"		--players=[number (POSITIVE INTEGER) of players]"<<std::endl;
	std::cerr<<"		-a (enables advanced bots to replace ragequitters)"<<std::endl;
	std::cerr<<"	<seed>:"<<std::endl;
	std::cerr<<"		[seed (INTEGER) for pseudo-shuffling of deck]"<<std::endl;
}

// checkInt(target) checks if target can be converted to an integer successfully
bool checkInt(std::string target) {
	for (int i = 0; i < target.length(); i++) {
		if (!std::isdigit(target[i])) return false;
	}
	return true;
}

// checkPlayers(target) checks if target is a valid configuration for the number of players
bool checkPlayers(std::string target) {
	if (target.substr(0, 10) == "--players=" && checkInt(target.substr(10, target.length() - 10))) {
		return true;
	}
	return false;
}

// checkAI(target) checks if target is option to enable advanced AI
bool checkAI(std::string target) {
	if (target == "-a") return true;
	return false;
}



/////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
	// parsing command-line
	int seed = std::chrono::system_clock::now().time_since_epoch().count();
	int players = 4;
	bool advanced = false;
	if (argc != 1) {
		for (int i = 1; i < argc; i++) {
			std::string next = std::string(argv[i]);
			if (checkInt(next)) {
				seed = std::stoi(next);
			} else if (checkPlayers(next)) {
				players = std::stoi(next.substr(10,next.length() - 10));	
				if (players < 1) {
					operation(std::string(argv[0]));
					return 1;
				}
			} else if (checkAI(next)) {
				advanced = true;
			} else {
				operation(std::string(argv[0]));
				return 1;
			}
		}
	}
	
	// ranks and suites found in the deck
	std::vector<char> ranks = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	std::vector<char> suites = {'C', 'D', 'H', 'S'};
	
	// determining who is a bot or not
	std::vector<bool> computerPlayers;
	int playerNum = 1;
	while (playerNum <= players) {
		std::cout<<"Is Player "<<playerNum<<" a human (h) or a computer (c)?"<<std::endl;
		std::string answer;
		std::cin>>answer;
		if (answer == "c") {
			computerPlayers.emplace_back(true);
			playerNum++;
		} else if (answer == "h") {
			computerPlayers.emplace_back(false);
			playerNum++;
		} else {
			std::cout<<"Not a valid answer."<<std::endl;
		}
	}

	// starting the game
	auto g = std::make_unique<Game>(&ranks, &suites, seed, computerPlayers, advanced);
	auto c = std::make_unique<Controller>(g.get());
	auto v = std::make_unique<View>(g.get());
	g->attach(v.get());
	
	// game loop
	try {
		g->startGame();
		while(!g->getEnded()) {
			c->nextTurn();
		}
	} catch (GameEnded ge) {
		std::cout<<ge.message<<std::endl;
	} catch (...) {
		std::cout<<"Something went wrong"<<std::endl;
	}
}
