#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "supervisor.h"
#include <string>
#include <vector>




class Subordinate {

	std::vector<Supervisor*> supervisors;

public:
	void addSupervisor(Supervisor* ob);

	//void notify(std::string msg = "", void* obj = nullptr);
	void makeRemark(std::string msg, void* subject);
	void setFlag(std::string msg, bool flag);

};


#endif