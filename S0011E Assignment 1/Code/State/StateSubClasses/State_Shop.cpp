#include "State_Shop.h"

State_Shop::State_Shop() {

}

State_Shop* State_Shop::Instance() {
	static State_Shop instance;

	return &instance;
}

void State_Shop::Execute(Agent* agent) {
	StoreInventory* store = StoreInventory::Instance();

	//Prioritize buying tool to facilitate larger economic gains
	if (!State_Work::Instance()->HasTool(agent, tool_pickaxe)) { //Never own more than one pickaxe at a time
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") is looking to buy a pickaxe.\n";
		Item item = store->GetItemFromInventory(cons_tool, tool_pickaxe);

		if ((item.itemType == cons_tool) && (agent->money >= item.cost)) {
			Tool* newTool = new Tool((ToolVariant)item.itemVariant);
			agent->inventory.push_back(std::make_shared<Consumable*>(newTool));
			agent->money -= item.cost;
			std::cout << "Agent " << agent->ID << " (" << agent->name << ") has purchased " << newTool->name << ".\n";
			return;
		}
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") couldn't afford a pickaxe.\n";
	}

	//Only buy food if more hungry than thirsty
	if ((agent->fullness <= agent->hydration)) {
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") is looking to buy some food.\n";
		for (int i = 0; i < store->GetInventorySize(); i++) {
			Item item = store->GetInventoryAtIndex(i);
			if (item.itemType == cons_food) {
				if (agent->money >= item.cost) {
					Food* newFood = new Food((FoodVariant)item.itemVariant);
					agent->inventory.push_back(std::make_shared<Consumable*>(newFood));
					agent->money -= item.cost;
					std::cout << "Agent " << agent->ID << " (" << agent->name << ") has purchased " << newFood->name << ".\n";
					return;
				}
			}

		}
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") couldn't afford anything to eat.\n";
	}

	else {
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") is looking to buy something to drink.\n";
		StoreInventory* store = StoreInventory::Instance();
		for (int i = 0; i < store->GetInventorySize(); i++) {
			Item item = store->GetInventoryAtIndex(i);
			if (item.itemType == cons_drink) {
				if (agent->money >= item.cost) {
					Drink* newDrink = new Drink((DrinkVariant)item.itemVariant);
					agent->inventory.push_back(std::make_shared<Consumable*>(newDrink));
					agent->money -= item.cost;
					std::cout << "Agent " << agent->ID << " (" << agent->name << ") has purchased " << newDrink->name << ".\n";
					return;
				}
			}
		}
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") couldn't afford anything to drink.\n";
	}

	if (agent->energy > (agent->maxValue * 0.3)) { //Go home and sleep if at 20% or less energy
		agent->ChangeState(State_Work::Instance());
	}
	else {
		agent->ChangeState(State_Sleep::Instance());
	}
}

void State_Shop::Enter(Agent* agent) {
	agent->location = loc_store;
	this->AddVisitor(agent);
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") has entered the store.\n";
}

void State_Shop::Exit(Agent* agent) {
	this->RemoveVisitor(agent);
}