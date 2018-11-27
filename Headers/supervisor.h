#ifndef SUPERVISOR_HPP
#define SUPERVISOR_HPP 

#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>

/*
	* Observer is the Boss therefore it decides in which manner the ones he observes address him
	* which is the reasoning behind remarks
	*
*/

class Supervisor {
private:
	std::map<std::string, std::function<void(void*)>> remarks;
	std::map<std::string, bool> flags;


public:
	std::vector<std::string>* listRemarks();
	std::vector<std::string>* listFlags();
	bool getFlagValue(std::string flag);
	virtual void recieveRemark(std::string remark, void* subject);
	virtual void changeFlag(std::string flag, bool value);

protected:
	virtual void declareRemark(std::string remark, std::function<void(void*)> intent);
	virtual void declareFlag(std::string flag, bool defFlag = false);
//
//
//public:  // To be implemented in derived classes
//	virtual void update(std::string msg, void* obj) = 0;
};


#endif