#include "Tool.h"

//Create Tool item based on variant specified
Tool::Tool(ToolVariant tool) {
	this->type = cons_tool;
	this->variant = tool;
	ToolVariables toolVariables = ToolTypes::Instance()->FetchTool(tool);
	this->name = toolVariables.name;
	this->durability = toolVariables.uses;
}

//Returns int based on successful use
int Tool::Use() {
	if (this->durability > 0) {
		this->durability -= 1;
		if (this->durability <= 0) {
			this->active = false;
		}
		return 1;
	}
	else {
		if (this->active)
			this->active = false;
	}
	return 0;
}

ToolVariant Tool::GetVariant() {
	return this->variant;
}

void Tool::Update() {

}

void Tool::HandleMessage(Message) {

}