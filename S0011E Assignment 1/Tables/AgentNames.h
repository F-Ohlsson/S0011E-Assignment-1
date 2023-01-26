#pragma once
#include <map>
#include<string>

class AgentNames {
private:
	AgentNames();
	std::map<int, std::string> nameMap;

public:
	static AgentNames* Instance();
	std::string FetchName(int);

};