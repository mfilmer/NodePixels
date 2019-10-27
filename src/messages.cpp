#include "messages.h"



 Message::Message()
 {
 	type = NULL_MSG;
 	len = 0;
 	bytes = 0;
 }


 Message::Message(const Message &oldMsg)
 {
 	len = oldMsg.len;
 	bytes = new char[len];
 	memcpy(bytes, oldMsg.bytes, len);
 }



 Message::~Message()
 {
 	delete bytes;
 }

