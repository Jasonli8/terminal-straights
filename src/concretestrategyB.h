#ifndef _CONCRETESTRATEGYB_H_
#define _CONCRETESTRATEGYB_H_

// enhanced implementation of Computer players AI


/*
 * This AI will attempt to prioritize playing the highest ranks and discarding the lowest ranks
 */
#include <memory>
#include "computer.h"
#include "strategy.h"

class ConcreteStrategyB : public Strategy {
	public:
		// make a move
		std::string plan(Computer * bot) override;
};

#endif
