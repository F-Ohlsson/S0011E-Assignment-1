#include "Agent.h"
#include "../../../Tables/AgentStates.h"


//Initialize agent on creation
Agent::Agent(int ID) {
	this->currentState = State_Sleep::Instance();
	this->globalState = State_ReceiveMessage::Instance();
	this->ID = ID;
	this->active = true;
	this->maxValue = 100;
	this->health = this->maxValue;
	this->energy = this->maxValue;
	this->fullness = this->maxValue;
	this->hydration = this->maxValue;
	this->socialNeeds = this->maxValue;



	this->money = 5;
	this->location = loc_home;
	this->name = AgentNames::Instance()->FetchName(this->ID);
	EntityManager::Instance()->AddEntity(this);
}

void Agent::Update() {
	this->energy = this->SubtractValue(this->energy, 1);
	this->fullness = this->SubtractValue(this->fullness, 1);
	this->hydration = this->SubtractValue(this->hydration, 1);
	this->socialNeeds = this->SubtractValue(this->socialNeeds, 1);
	this->currentState->Execute(this);
	this->CheckHealth();
	this->CleanInventory();
	if (this->health <= 0) {
		this->Die();
	}
}

void Agent::ChangeState(State* newState) {
	this->currentState->Exit(this);
	this->previousState = this->currentState;
	this->currentState = newState;
	this->currentState->Enter(this);
}

void Agent::HandleMessage(const Message message) {
	std::cout << "(" << this->name << ") is handling a message.\n";
	if (this->globalState == State_ReceiveMessage::Instance()) {
		this->globalState->OnMessage(this, message);
	}
}

//Returns a bool whether a meeting is already scheduled between this agent and specified agent
bool Agent::HasMeeting(Agent* meeting) {
	if (this->meetings.size() <= this->maxMeetings) {
		for (int i = 0; i < this->meetings.size(); i++) {
			if (this->meetings[i].meeterID == meeting->ID) {
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}

//Schedules meeting between this agent and specified agent
//Currently not in use due to lack of implementation
void Agent::ScheduleMeeting(Agent* meeting) {
	//std::cout << "You're not me! Let's hang out. DEBUG: Sending message to " << meeting->name << "\n";

	//Preparing meeting message
	MessageManager* msgMngr = MessageManager::Instance();
	MeetingData data;
	data.meetingLocation = loc_park;
	data.meetingDelay = 3;
	MeetingData* messageData = &data;
	msgMngr->QueueMessage(this->ID, meeting->ID, msg_meetingCreate, 0, (void*)messageData);

	//Schedule meeting themselves
	Meeting newMeeting;
	newMeeting.meeterID = meeting->ID;
	newMeeting.location = data.meetingLocation;
	newMeeting.meetingTime = data.meetingDelay;
	this->meetings.push_back(newMeeting);
}

//Simple function for increasing agent parameters without exceeding maximum allowed amount
int Agent::AddValue(int currentValue, int valueToAdd) {
	int result = currentValue + valueToAdd;
	if (result > this->maxValue) {
		return this->maxValue;
	}
	else {
		return result;
	}
}

//Simple function for decreasing agent parameters without exceeding minimum allowed amount
int Agent::SubtractValue(int currentValue, int valueToSub) {
	int result = currentValue - valueToSub;
	if (result < this->minValue) {
		return this->minValue;
	}
	else {
		return result;
	}
}

//If any of agents vitals are at minimum allowed value, decrease health
void Agent::CheckHealth() {
	bool damage = false;
	int parameterArray[4] = { fullness,hydration,energy,socialNeeds };
	for (int i = 0; i < 3; i++) { //Change to i < 4 when socialNeeds are implemented ###
		if (parameterArray[i] <= minValue)
			damage = true;
	}

	if (damage) {
		std::cout << "Agent " << this->ID << " (" << this->name << ") Is suffering and is likely to die if this continues.\n";
		this->health = this->SubtractValue(this->health,this->maxValue*0.1f);
	}
}

//Remove any spent items from the inventory
void Agent::CleanInventory() {
	int i = 0;
	if (this->inventory.size() > 0) {
		for (int i = (int)this->inventory.size() - 1; i >= 0; i--) {
			Consumable* currentItem = *this->inventory[i].get();
			if (!currentItem->active) {
				this->inventory.erase(this->inventory.begin() + i);
			}
		}
	}
}


void Agent::Die() {
	std::cout << "Agent " << this->ID << " (" << this->name << ") has died. RIP\n";
	this->active = false;

	std::cout << "Their stats were, at time of death:\n";
	std::cout << "Fullness: " << this->fullness << ".\n";
	std::cout << "Hydration: " << this->hydration << ".\n";
	std::cout << "Social Needs: " << this->socialNeeds << ".\n";
	std::cout << "Energy: " << this->energy << ".\n";
	std::cout << "Money: " << this->money << ".\n";

}