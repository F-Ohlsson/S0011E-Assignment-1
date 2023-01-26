#include "State_Eat.h"

State_Eat::State_Eat() {

}


void State_Eat::Execute(Agent* agent) {
	if (this->HasFood(agent)) {
		Food* food = this->FetchFood(agent);
		agent->fullness = agent->AddValue(agent->fullness, food->Use());
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") is eating some " << food->name << "\n";
	}
	else {
		//No food, must go buy some
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") doesn't have any food. They need to buy more.\n";
		agent->ChangeState(State_Shop::Instance());
		return;
	}


	//If more thirsty than hungry, drink
	if (agent->fullness > agent->hydration) {
		agent->ChangeState(State_Drink::Instance());
		return;
	}

	//If above 80% of max value, return to previous activity
	if (agent->fullness >= (agent->maxValue * 0.8f)) {
		agent->ChangeState(agent->previousState);
		return;
	}
}

void State_Eat::Enter(Agent* agent) {
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") is hungry and is going to eat.\n";
	this->AddVisitor(agent);
}

void State_Eat::Exit(Agent* agent) {
	//std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "is done eating.\n";
	this->RemoveVisitor(agent);
}

State_Eat* State_Eat::Instance() {
	static State_Eat instance;

	return &instance;
}

//Simply return whether specified agent has any food in their inventory
bool State_Eat::HasFood(Agent* agent) {
	for (int i = 0; i < agent->inventory.size(); i++) {
		if (((*agent->inventory[i].get())->type == cons_food) && (*agent->inventory[i].get())->active) {
			return true;
		}
	}
	return false;
}

//Returns most filling meal (that doesn't exceed Agent maximum) in Agent's inventory
Food* State_Eat::FetchFood(Agent* agent) {
	Food* bestFood = NULL;
	for (int i = 0; i < agent->inventory.size(); i++) {
		if (((*agent->inventory[i].get())->type == cons_food) && ((*agent->inventory[i].get())->active)) {
			Food** currentFoodDblPtr = (Food**)agent->inventory[i].get();
			Food* currentFood = *currentFoodDblPtr;
			if (bestFood == NULL)
				bestFood = currentFood;
			else if ((currentFood->GetFullnessValue() > bestFood->GetFullnessValue()) && (currentFood->GetFullnessValue() + agent->fullness <= agent->maxValue)) { //Ensure that AI doesn't eat a food that will unneccesarily put their fullness above the max value (100)
				bestFood = currentFood;
			}
		}
	}
	return bestFood;
}
