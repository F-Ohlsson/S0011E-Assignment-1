#pragma once
#include "../State.h"
#include "State_Work.h"
#include "../../../Tables/Locations.h"

class State_Sleep : public State {
private:
	State_Sleep();

public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_Sleep* Instance();

};