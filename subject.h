#ifndef _SUBJECT_H_
#define _SUBJECT_H_

// abstract subject for observer design pattern

#include <vector>
#include "observer.h"

class Subject {
	std::vector<Observer*> observers;

	public:
		Subject();
		virtual ~Subject() = 0;

		//////////////////////////////////////////

		// handle list of observers
		void attach(Observer *o);
		void detach(Observer *o);

		// notify() signals to observers a turn has ended
		void notify();
		// notify(s) pushes the custom message s to observers
		void notify(std::string s);
};

#endif
