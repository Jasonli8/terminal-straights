#ifndef _OBSERVER_H_
#define _OBSERVER_H_

//abstract Observer class for Observer design pattern

#include <string>

class Observer {
	public:
		Observer();
		virtual ~Observer();

		////////////////////////////////////////

		virtual void notify() = 0;
		virtual void notify(std::string s) = 0;
};

#endif
