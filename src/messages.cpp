#include "messages.h"


Message::Message(char len, char* bytes)
{
  this->len = len;
  memcpy(this->bytes, bytes, len);
}


Message::~Message()
{
  delete this->bytes;
}


char Message:fullType()
{
	return this->bytes[0];
}


char Message::readBit()
{
  return READBIT(this->bytes[0]);
}


char Message::hsvBit()
{
  return HSVBIT(this->bytes[0]);
}


char Message::type()
{
  return MSGBITS(this->bytes[0]);
}


char Message::getLen()
{
  return this->len;
}


char* Message::getBytes()
{
  return this->bytes;
}


char* Message::getData()
{
	if (this->len > 1) {
		return this->bytes + 1;
	}
	return 0;
}
