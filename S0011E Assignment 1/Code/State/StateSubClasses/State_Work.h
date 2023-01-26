#pragma once
#include "State_Sleep.h"
#include "State_Eat.h"
#include "State_Drink.h"
#include "../../GameEntity/GameEntitySubClasses/ConsumableSubClasses/Tool.h"

class State_Work : public State
{
private:
	State_Work();

public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_Work* Instance();

	bool HasTool(Agent*,ToolVariant);
	bool UseTool(Agent*, ToolVariant);
};

