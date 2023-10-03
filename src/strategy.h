#ifndef _STRATEGY_H_
#define _STRATEGY_H_

// strategy superclass

#include <vector>
#include <memory>

class Computer;

class Strategy {
	public:
		virtual std::string plan(Computer * bot) = 0;
};

#endif
