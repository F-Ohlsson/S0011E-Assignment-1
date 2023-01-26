#pragma once
#include "../State.h"
#include "State_Shop.h"
#include "State_Eat.h"
#include "../../GameEntity/GameEntitySubClasses/ConsumableSubClasses/Drink.h"

class State_Drink : public State {
private:
	State_Drink();
public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_Drink* Instance();

	Drink* FetchDrink(Agent* agent);
	bool HasDrink(Agent* agent);
};