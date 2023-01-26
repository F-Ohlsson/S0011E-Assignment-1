#include "State_Sleep.h"

State_Sleep::State_Sleep() {

}

void State_Sleep::Execute(Agent* agent) {
	bool canSleep = true;
	//Can't sleep if too hungry or too thirsty
	if ((agent->fullness < agent->maxValue * 0.1f) || (agent->hydration < agent->maxValue * 0.1f)){
		canSleep = false;
	}

	//Sleep while below 80% of max
	if ((agent->energy < (agent->maxValue*0.8f)) && canSleep) {
		agent->energy = agent->AddValue(agent->energy,agent->maxValue*0.4f);
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "is sleeping.\n";
	}
	else {
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "has woken up.\n";
		agent->ChangeState(State_Work::Instance());
		return;
	}

}

void State_Sleep::Enter(Agent* agent) {
	std::cout << "Agent " << agent->ID << " ("<<agent->name<<") " << "is going home to sleep.\n";
	agent->location = loc_home;
	this->AddVisitor(agent);
}

void State_Sleep::Exit(Agent* agent) {
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "is feeling rested and is leaving home.\n";
	this->RemoveVisitor(agent);
}

State_Sleep* State_Sleep::Instance() {
	static State_Sleep instance;

	return &instance;
}

void State_Sleep::ListVisitors() {
	std::cout << "The current agents at home are: \n";
	for (int i = 0; i < this->currentVisitors.size(); i++) {
		std::cout << "Agent number " << " (" << this->currentVisitors[i]->name << ") " << this->currentVisitors[i]->ID << ".\n";
	}
	std::cout << "That's it.\n";
}