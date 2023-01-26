#pragma once
#include "../Consumable.h"
#include "../../../../Tables/ToolTypes.h"

class Tool : public Consumable {
private:
	ToolVariant variant;
public:
	Tool(ToolVariant);
	int Use();
	ToolVariant GetVariant();
	void Update();
	void HandleMessage(Message);
};