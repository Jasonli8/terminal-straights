#include <string>
#include "computer.h"
#include "concretestrategyA.h"
#include "concretestrategyB.h"

// Big 5 ///////////////////////////////////////////////

Computer::Computer(GameState * game) : Player{}, strat{std::make_unique<ConcreteStrategyA>()}, game{game} {
	setPlayer(false);
}

Computer::~Computer() {}

// Getter /////////////////////////////////////////////////

GameState * Computer::getGame() {
	return game;
}

// Movement /////////////////////////////////////////////

std::string Computer::move(char turn, Card *s) {
	std::string action = strat->plan(this);
	return action;
}

void Computer::changeStrategy() {
	strat = std::make_unique<ConcreteStrategyB>();
}
