#pragma once
#include "../Tables/Locations.h"

//Used for recipient to identify how to handle the message and any extraData packaged into the void*
enum MsgType {
	msg_meetingCreate,
	msg_meetingCancel,
	msg_meetingEvent,
};

struct Message {
	int senderID;
	int receiverID;
	MsgType msgType;
	int delay;

	void* extraData;
};

struct MeetingData {
	Location meetingLocation;
	int meetingDelay;
};