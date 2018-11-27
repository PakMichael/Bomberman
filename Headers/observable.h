#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "observer.h"
#include <string>
#include <vector>




class Observable {

	std::vector<Observer*> observers;

public:
	void addObserver(Observer* ob);

	void notify(std::string msg = "", void* obj = nullptr);
 

};


#endif