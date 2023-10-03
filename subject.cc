#include <string>
#include "subject.h"

//////////////////////////////////////////////////////

Subject::Subject() {}
Subject::~Subject() {}

/////////////////////////////////////////////////////////

void Subject::attach(Observer *o) {
	observers.emplace_back(o);
}

void Subject::detach(Observer *o) {
	for (auto it = observers.begin(); it != observers.end(); ++it) {
		if (*it == o) {
			observers.erase(it);
			break;
		}
	}
}

///////////////////////////////////////////////////////

void Subject::notify() {
	for (auto ob : observers) ob->notify();
}

void Subject::notify(std::string s) {
	for (auto ob : observers) ob->notify(s);
}
