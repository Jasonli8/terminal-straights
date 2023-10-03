#ifndef _VIEW_H_
#define _VIEW_H_

// concrete observer, text-based output to stdout

#include "game.h"
#include "observer.h"

class View : public Observer {
	Game * game;

	public:
		View(Game * game);
		~View();

		///////////////////////////////////////////////////////

		void notify() override;
		void notify(std::string s) override;
};

#endif
