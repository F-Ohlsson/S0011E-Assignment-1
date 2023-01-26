#pragma once
#include "../State.h"
#include "../../../Tables/Locations.h"

class State_HangOut : public State {
private:
	State_HangOut();

public:
	void Execute(Agent* agent);
	void Enter(Agent* agent);
	void Exit(Agent* agent);
	static State_HangOut* Instance();

	void ListVisitors();
};