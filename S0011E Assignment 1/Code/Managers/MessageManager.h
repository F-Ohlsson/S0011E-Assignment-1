#pragma once
#include <vector>
#include "../Message.h"
#include "EntityManager.h"

class MessageManager
{
private:
	MessageManager();
	std::vector<Message> messages;
	void DispatchMessage(Message);

public:
	static MessageManager* Instance();
	void DispatchQueuedMessages();
	void QueueMessage(int senderID,
		int receiverID,
		MsgType messageType,
		int delay,
		void* extraInfo
	);
	void QueueMessage(Message msg);
	
};

