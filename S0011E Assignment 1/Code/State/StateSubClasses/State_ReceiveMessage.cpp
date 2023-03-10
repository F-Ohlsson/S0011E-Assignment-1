#include "State_ReceiveMessage.h"

State_ReceiveMessage::State_ReceiveMessage() {
}


void State_ReceiveMessage::Enter(Agent* agent) {

}

void State_ReceiveMessage::Exit(Agent* agent) {

}

void State_ReceiveMessage::Execute(Agent* agent) {
	//std::cout << "In Receive Message state.\n";
}

State_ReceiveMessage* State_ReceiveMessage::Instance() {
	static State_ReceiveMessage instance;

	return &instance;
}

bool State_ReceiveMessage::OnMessage(Agent* agent, const Message& message) {
	if (message.receiverID != agent->ID) {
		std::cout << "DEBUG: Message has been sent to wrong agent.\nIntended Agent: " << message.receiverID << "\nActual Agent: " << agent->ID << "\n";
	}
	else {
		switch (message.msgType) {
		case msg_meetingCreate: {
			MeetingData* data = (MeetingData*)message.extraData;
			Agent* meeter = (Agent*)EntityManager::Instance()->FetchEntityByID(message.senderID);
			if (!agent->HasMeeting(meeter) && (!agent->HasMeeting(data->meetingDelay))) {
				std::cout << "Agent " << agent->ID << " (" << agent->name << ") has accepted Agent " << message.senderID << " (" << meeter->name << ")'s invitation to hang out.\n";
				this->CreateMeeting(agent, message); //If schedule clear
			}
			else { //If schedule full
				std::cout << "Agent " << agent->ID << " (" << agent->name << ") has declined Agent " << message.senderID << " (" << meeter->name << ")'s invitation to hang out.\n";
				Message cancelMsg;
				cancelMsg.msgType = msg_meetingCancel;
				cancelMsg.receiverID = message.senderID;
				cancelMsg.senderID = agent->ID;
				cancelMsg.delay = 0;
				cancelMsg.extraData = message.extraData;

				MessageManager::Instance()->QueueMessage(cancelMsg);
			}
			break;
		}
		case msg_meetingCancel:
			this->CancelMeeting(agent, message);
			break;
		case msg_meetingEvent:
			agent->HadMeeting((bool)&message.extraData);
			break;
		}
	}
	return false;
}

void State_ReceiveMessage::CreateMeeting(Agent* agent, const Message& message) {
	Meeting newMeeting;
	newMeeting.meeterID = message.senderID;
	//newMeeting.meetingTime = message.
	MeetingData* data = (MeetingData*)message.extraData;
	newMeeting.location = data->meetingLocation;
	newMeeting.meetingTime = data->meetingDelay;

	agent->meetings.push_back(newMeeting);
}

void State_ReceiveMessage::CancelMeeting(Agent* agent, const Message& message) {
	if (agent->meetings.size() != 0) {
		for (int i = 0; i < agent->meetings.size(); i++) {
			if ((agent->meetings[i].meeterID == message.senderID)/* &&
				(agent->meetings[i].location == (Location*)message.extraData)*/ ) {
				agent->meetings.erase(agent->meetings.begin() + i);
			}


		}
	}
}