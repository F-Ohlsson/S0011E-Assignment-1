#include "MessageManager.h"

//Incomplete
//Will require rework depending on implementation of time

MessageManager::MessageManager() {

}

 MessageManager* MessageManager::Instance() {
	static MessageManager instance;

	return &instance;
}

 void MessageManager::QueueMessage(int senderID, int receiverID, MsgType msgType, int delay, void* extraInfo) {
	 Message message;
	 message.senderID = senderID;
	 message.receiverID = receiverID;
	 message.msgType = msgType;
	 message.delay = delay;
	 message.extraData = extraInfo;
	 if (delay <= 0) {
		 this->DispatchMessage(message);
	 }
	 else {
		this->messages.push_back(message);
	 }
 }
 
 void MessageManager::QueueMessage(Message message) {
	 if (message.delay <= 0) {
		 this->DispatchMessage(message);
	 }
	 else {
		 this->messages.push_back(message);
	 }
 }
 

 void MessageManager::DispatchMessage(Message message) {
	 EntityManager* entityMngr = EntityManager::Instance();
	 GameEntity* receiver = entityMngr->FetchEntityByID(message.receiverID);
	 receiver->HandleMessage(message);
 }

 void MessageManager::DispatchQueuedMessages() {
	 for (int i = 0; i < this->messages.size(); i++) {
		 if (messages[i].delay == 0) {
			 this->DispatchMessage(messages[i]);
			 this->messages.erase(this->messages.begin() + i);
		 }
		 else {
			 messages[i].delay -= 1;
		 }
	 }
 }