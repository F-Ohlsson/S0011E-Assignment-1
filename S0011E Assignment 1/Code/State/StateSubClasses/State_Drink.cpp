#include "State_Drink.h"

State_Drink::State_Drink() {

}

State_Drink* State_Drink::Instance() {
	static State_Drink instance;

	return &instance;
}

void State_Drink::Execute(Agent* agent) {
	if (this->HasDrink(agent)) {
		Drink* drink = this->FetchDrink(agent);
		agent->hydration = agent->AddValue(agent->hydration, drink->Use());
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") is drinking some " << drink->name << "\n";
	}
	else {
		//No drinks, must go buy some
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") doesn't have any drinks. They need to buy more.\n";

		agent->ChangeState(State_Shop::Instance());
		return;
	}

	//If more hungry than thirsty, drink
	if (agent->hydration > agent->fullness) {
		agent->ChangeState(State_Eat::Instance());
		return;
	}

	if (agent->hydration > agent->maxValue * 0.8) {
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") has quenched their thirst. Resuming previous activity.\n";
		agent->ChangeState(agent->previousState);
		return;
	}
}

void State_Drink::Enter(Agent* agent) {
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") is thirsty and is going to drink something.\n";

	this->AddVisitor(agent);
}

void State_Drink::Exit(Agent* agent) {
	this->RemoveVisitor(agent);

}

//Simply checks whether specified agent has a drink in their inventory
bool State_Drink::HasDrink(Agent* agent) {
	for (int i = 0; i < agent->inventory.size(); i++) {
		if (((*agent->inventory[i].get())->type == cons_drink) && (*agent->inventory[i].get())->active) {
			return true;
		}
	}
	return false;
}

//Fetches the most thirst quenching drink (that doesn't exceed agent's maximum allowed value) currently in the agent's inventory
Drink* State_Drink::FetchDrink(Agent* agent) {
	Drink* bestDrink = NULL;
	for (int i = 0; i < agent->inventory.size(); i++) {
		if (((*agent->inventory[i].get())->type == cons_drink) && ((*agent->inventory[i].get())->active)) {
			Drink** currentDrinkDblPntr = (Drink**)agent->inventory[i].get();
			Drink* currentDrink = *currentDrinkDblPntr;
			if (bestDrink == NULL)
				bestDrink = currentDrink;
			else if ((currentDrink->GetHydrationValue() > bestDrink->GetHydrationValue()) && (currentDrink->GetHydrationValue() + agent->hydration <= agent->maxValue)) { //Ensure that AI doesn't drink something that will unneccesarily put their hydration above the max value
				bestDrink = currentDrink;
			}
		}
	}
	return bestDrink;
}