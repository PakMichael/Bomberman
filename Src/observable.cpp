#include "observable.h"



void Observable::addObserver(Observer* ob) {
	observers.push_back(ob);
}

void Observable::notify(std::string msg, void* obj) {
	for (Observer* observer : observers)
		observer->update(msg, obj);
}