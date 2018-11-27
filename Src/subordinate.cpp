#include "subordinate.h"



void Subordinate::addSupervisor(Supervisor* ob) {
	supervisors.push_back(ob);
}

//void Subordinate::notify(std::string msg, void* obj) {
//	for (Supervisor* supervisor : supervisors)
//		supervisor->update(msg, obj);
//}

void Subordinate::makeRemark(std::string msg, void* subject) {
	for (Supervisor* supervisor : supervisors)
		supervisor->recieveRemark(msg, subject);
}


void Subordinate::setFlag(std::string msg, bool flag) {
	for (Supervisor* supervisor : supervisors)
		supervisor->changeFlag(msg, flag);
}