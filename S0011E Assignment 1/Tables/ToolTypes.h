#pragma once
#include <map>
#include <string>

enum ToolVariant {
	tool_pickaxe,
};

struct ToolVariables {
	int uses;
	std::string name;
};

class ToolTypes {
private:
	ToolTypes();
	std::map<ToolVariant, ToolVariables> toolDB;

public:
	static ToolTypes* Instance();
	ToolVariables FetchTool(ToolVariant);

};