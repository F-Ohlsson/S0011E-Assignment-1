#include "AgentNames.h"

AgentNames::AgentNames() {
	std::string name0 = "Alicia";
	std::string name1 = "Bond";
	std::string name2 = "Carla";
	std::string name3 = "David";

	this->nameMap.insert({ 0, name0 });
	this->nameMap.insert({ 1, name1 });
	this->nameMap.insert({ 2, name2 });
	this->nameMap.insert({ 3, name3 });
}

std::string AgentNames::FetchName(int ID) {
	return this->nameMap.at(ID);
}

AgentNames* AgentNames::Instance() {
	static AgentNames instance;

	return &instance;
}