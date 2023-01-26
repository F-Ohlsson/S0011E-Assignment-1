#pragma once
#include "../State.h"
#include "State_Work.h"
#include "State_Eat.h"
#include "State_Drink.h"
#include "../../../Tables/StoreInventory.h"

class State_Shop : public State {
private:
	State_Shop();
public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_Shop* Instance();
};