#pragma once
#include "../GameEntity/GameEntitySubClasses/Agent.h"
#include "../Managers/MessageManager.h"
#include <vector>
#include <iostream>

//class Agent;

class State
{
public:
	std::vector<Agent*> currentVisitors;

	virtual void Execute(Agent* agent) = 0;
	virtual void Enter(Agent* agent) = 0;
	virtual void Exit(Agent* agent) = 0;
	virtual bool OnMessage(Agent*, const Message&);
	void AddVisitor(Agent*);
	void RemoveVisitor(Agent*);
	std::vector<Agent*> GetVisitors();
	bool TryToMeet(Agent*, std::vector<Agent*>);
};

