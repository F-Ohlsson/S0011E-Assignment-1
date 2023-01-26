#include "State.h"

bool State::OnMessage(Agent* agent,const  Message& message) {
	return false;
}

void State::AddVisitor(Agent* agent) {
	this->currentVisitors.push_back(agent);
}

void State::RemoveVisitor(Agent* agent) {
	for (int i = 0; i < this->currentVisitors.size(); i++) {
		if (this->currentVisitors[i] == agent) {
			this->currentVisitors.erase(this->currentVisitors.begin() + i);
		}
	}
}

std::vector<Agent*> State::GetVisitors() {
	return this->currentVisitors;
}

bool State::TryToMeet(Agent* agent, std::vector<Agent*> visitors) {
	if (visitors.size() > 1) {
		//Not alone!
		//std::cout << "I'm not alone!\n";
		if (agent->socialNeeds < agent->maxValue * 0.5f) {
			for (int i = 0; i < visitors.size(); i++) {
				if ((visitors[i]->ID != agent->ID) && (visitors[i]->location == agent->location)) {
					if (!agent->HasMeeting(visitors[i])) {
						agent->ScheduleMeeting(visitors[i]);
						return true;
					}
					break;
				}
			}
		}
	}
	else {
		//Being alone is harsh on the mind
		agent->socialNeeds = agent->SubtractValue(agent->socialNeeds, 1);
	}
	return false;
}