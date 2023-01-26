#pragma once
#include "../Managers/EntityManager.h"
#include "../Message.h"

class GameEntity
{
public:
	int ID;
	bool active = true;

	virtual void Update() = 0;
	virtual void HandleMessage(Message) = 0;
};

