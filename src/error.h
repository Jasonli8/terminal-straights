#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>

// custom errors


// error is thrown when game has ended, but a function is called that may mutate its underlying states
class GameEnded {
	public:
		std::string message;
		GameEnded() : message{"Game has already ended."} {}
};

#endif
