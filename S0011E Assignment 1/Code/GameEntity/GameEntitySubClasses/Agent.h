#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../GameEntity.h"
#include "../../../Tables/Locations.h"
#include "../../../Tables/AgentNames.h"
#include "Consumable.h"


class State;

struct Meeting {
	int meeterID;
	Location location;
	int meetingTime;
};

class Agent : public GameEntity
{
private:
	void Die();
	State* currentState;
	State* globalState;

public:

	Agent(int ID);
	void Update();
	void ChangeState(State* newState);
	void HandleMessage(const Message);
	bool HasMeeting(Agent* meeting);
	void ScheduleMeeting(Agent* meeting);
	void CheckHealth();
	void CleanInventory();

	int AddValue(int currentValue, int valueToAdd);
	int SubtractValue(int currentValue, int valueToSub);

	std::string name;
	int maxValue;
	int minValue = 0;
	int health;
	int energy;
	int fullness;
	int hydration;
	int money;
	int socialNeeds;
	Location location;
	State* previousState;

	int maxMeetings = 3;
	std::vector<Meeting> meetings;

	//int inventoryMaxSize = 10;
	std::vector<std::shared_ptr<Consumable*>> inventory;
};

