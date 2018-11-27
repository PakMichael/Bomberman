#include "supervisor.h"



void Supervisor::declareRemark(std::string remark, std::function<void(void*)> intent) {
	remarks.insert(std::make_pair(remark, intent));
}

void Supervisor::declareFlag(std::string flag, bool defFlag) {
	flags.insert(std::make_pair(flag, defFlag));
}

std::vector<std::string>* Supervisor::listRemarks() {
	std::vector<std::string>* list = new std::vector<std::string>;
	for (std::pair<std::string, std::function<void(void*)>> touple : remarks) {
		list->push_back(touple.first);
	}
	return list;
}

void Supervisor::recieveRemark(std::string remark, void* subject) {
	for (std::pair<std::string, std::function<void(void*)>> touple : remarks) {
		if (remark == touple.first)touple.second(subject);
	}
}

void Supervisor::changeFlag(std::string flag, bool value) {
	if (flags.find(flag) == flags.end())return;
	(*flags.find(flag)).second = value;
}

std::vector<std::string>*  Supervisor::listFlags() {
	std::vector<std::string>* list = new std::vector<std::string>;
	for (std::pair<std::string, bool> touple : flags) {
		list->push_back(touple.first);
	}
	return list;
}

bool Supervisor::getFlagValue(std::string flag) {
	return flags.find(flag)->second;
}