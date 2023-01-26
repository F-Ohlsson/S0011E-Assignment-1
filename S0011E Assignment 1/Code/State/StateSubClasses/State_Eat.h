#pragma once
#include "../State.h"
#include "State_Drink.h"
#include "State_Shop.h"
#include "../../GameEntity/GameEntitySubClasses/ConsumableSubClasses/Food.h"

class State_Eat : public State {
private:
	State_Eat();
public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_Eat* Instance();

	bool HasFood(Agent* agent);
	Food* FetchFood(Agent* agent);
};