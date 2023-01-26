#include "ToolTypes.h"

ToolTypes::ToolTypes() {
	//Pickaxe
	ToolVariant pickaxe = tool_pickaxe;
	ToolVariables pickaxeVariables;
	pickaxeVariables.name = "pickaxe";
	pickaxeVariables.uses = 10;

	this->toolDB.insert({ pickaxe, pickaxeVariables });
}

ToolVariables ToolTypes::FetchTool(ToolVariant type) {
	return this->toolDB.at(type);
}

ToolTypes* ToolTypes::Instance() {
	static ToolTypes instance;

	return &instance;
}