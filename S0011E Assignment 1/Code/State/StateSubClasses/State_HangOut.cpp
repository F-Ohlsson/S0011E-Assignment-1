#include "State_HangOut.h"

State_HangOut::State_HangOut() {

}

void State_HangOut::Execute(Agent* agent) {
	bool meetingSuccess = false;
	bool meetingFound = false;
	Meeting meeting;

	for (int i = 0; i < agent->meetings.size(); i++) {
		if (agent->meetings[i].meetingTime == 0) { 
			meeting = agent->meetings[i]; 
			meetingFound = true;
		}

	}
	
	if (meetingFound) {
		std::vector<Agent*> visitors = State_HangOut::Instance()->currentVisitors;
	
		for (int i = 0; i < visitors.size(); i++) {
			if (visitors[i]->ID == meeting.meeterID) {
				meetingSuccess = true;
			}
		}

		agent->HadMeeting(meetingSuccess);
		//Preparing meeting message
		MessageManager* msgMngr = MessageManager::Instance();
		bool* messageData = &meetingSuccess;
		msgMngr->QueueMessage(agent->ID, meeting.meeterID, msg_meetingEvent, 0, (void*)messageData);
	
	}
	
	agent->ChangeState(agent->previousState);
	return;
}

void State_HangOut::Enter(Agent* agent) {
	this->AddVisitor(agent);
	for (int i = 0; i < agent->meetings.size(); i++) {
		if (agent->meetings[i].meetingTime == 0) { agent->location = agent->meetings[i].location; }
		break;
	}
}

void State_HangOut::Exit(Agent* agent) {
	this->RemoveVisitor(agent);
}

State_HangOut* State_HangOut::Instance() {
	static State_HangOut instance;

	return &instance;
}