#ifndef OBSERVER_HPP
#define OBSERVER_HPP 

#include <iostream>
#include <string>

class Observer {

public:
	virtual void update(std::string msg, void* obj) = 0;


};


#endif