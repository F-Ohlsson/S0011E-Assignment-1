#pragma once
#include "../State.h"

class State_ReceiveMessage : public State{
private:
	State_ReceiveMessage();

public:
	void Execute(Agent*);
	void Enter(Agent*);
	void Exit(Agent*);
	static State_ReceiveMessage* Instance();

	bool OnMessage(Agent*, const Message&);
	void CreateMeeting(Agent*, const Message&);
	void CancelMeeting(Agent*, const Message&);
};