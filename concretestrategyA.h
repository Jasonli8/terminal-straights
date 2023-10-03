#ifndef _CONCRETESTRATEGYA_H_
#define _CONCRETESTRATEGYA_H_

// base implementation of Computer players AI

#include <memory>
#include "computer.h"
#include "strategy.h"

class ConcreteStrategyA : public Strategy {
	public:
		// make a move
		std::string plan(Computer * bot) override;
};

#endif
