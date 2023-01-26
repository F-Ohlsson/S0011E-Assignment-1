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