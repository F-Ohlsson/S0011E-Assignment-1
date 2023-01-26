#include "State_Work.h"


State_Work::State_Work() {
}


void State_Work::Execute(Agent* agent) {
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "is working.\n";
	if (agent->location == loc_orchard) {
		//Working is strenuous
		agent->money += 1;
		agent->energy = agent->SubtractValue(agent->energy, 10);
		agent->fullness = agent->SubtractValue(agent->fullness, 5); 
		agent->hydration = agent->SubtractValue(agent->hydration, 5); 


	}
		
	else if (agent->location == loc_mine) {
		int i = 0;
		if (this->UseTool(agent, tool_pickaxe)) {
			//Working in the mine is a bit more taxing but pays much better
			std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "used their pickaxe to work in the mine.\n";
			agent->money += 4;
			agent->energy = agent->SubtractValue(agent->energy, 15);
			agent->fullness = agent->SubtractValue(agent->fullness, 10);
			agent->hydration = agent->SubtractValue(agent->hydration, 10);
		}
		else { //If failed to use pickaxe change location
			std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "broke their pickaxe and moved to the orchard instead.\n";
			agent->location = loc_orchard;
		}
	}
	
	if (this->currentVisitors.size() > 1) {
		//Not alone!
		//std::cout << "I'm not alone!\n";
		for (int i = 0; i < this->currentVisitors.size(); i++) {
			if((this->currentVisitors[i]->ID != agent->ID) && (this->currentVisitors[i]->location == agent->location)) {
				if (!agent->HasMeeting(this->currentVisitors[i])) {
					agent->ScheduleMeeting(this->currentVisitors[i]);
				}
				break;
			}
		}
	}
	else {
		//Being alone is harsh on the mind
		agent->socialNeeds = agent->SubtractValue(agent->socialNeeds, 2);
	}

	//Check if time to change states
	if (agent->fullness < (agent->maxValue * 0.3)) {
		agent->ChangeState(State_Eat::Instance());
		return;
	}
	else if (agent->hydration < (agent->maxValue * 0.3)) {
		agent->ChangeState(State_Drink::Instance());
		return;
	}
	else if (agent->energy < (agent->maxValue * 0.2)) {
		agent->ChangeState(State_Sleep::Instance());
		return;
	}
}

void State_Work::Enter(Agent* agent) {
	if (this->HasTool(agent, tool_pickaxe)) {
		agent->location = loc_mine;
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "has started working in the mine.\n";
		
	}
	else {
		agent->location = loc_orchard;
		std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "has started working in the orchard.\n";
		this->AddVisitor(agent);
	}
	
}

void State_Work::Exit(Agent* agent) {
	std::cout << "Agent " << agent->ID << " (" << agent->name << ") " << "has stopped working. They have $" << agent->money<<".\n";
	this->RemoveVisitor(agent);
}


State_Work* State_Work::Instance() {
	static State_Work instance;

	return &instance;
}

//Returns bool whether the specified agent has the specified tool in its possession
bool State_Work::HasTool(Agent* agent, ToolVariant toolVariant) {
	for (int i = 0; i < agent->inventory.size(); i++) {
		Consumable* currentItem = *agent->inventory[i].get();
		if (currentItem->type == cons_tool) { //Tool determined, allows for Tool based operations
			Tool* tool = (Tool*)*agent->inventory[i].get();
			if ((tool->GetVariant() == toolVariant) && (tool->active)) {
				return true;
			}
		}
	}
	return false;
}

//Uses specified tool
bool State_Work::UseTool(Agent* agent, ToolVariant toolVariant) {
	//First make sure that agent has correct tool
	if (this->HasTool(agent, toolVariant)) {
		for (int i = 0; i < agent->inventory.size(); i++) {
			if ((*agent->inventory[i].get())->type == cons_tool) {
				Tool* currentTool = (Tool*)*agent->inventory[i].get();
				if (currentTool->GetVariant() == toolVariant) {
					int success = currentTool->Use();
					if (success) {
						return true;
					}
				}
			}
		}
	}
	return false;
}