#include "messages.h"


Message::Message(char len, char* bytes)
{
  this->fullType = bytes[0];
  this->len = len;
  memcpy(this->bytes, bytes, len);
}


Message::~Message()
{
  delete this->bytes;
}


char Message::readBit()
{
  return READBIT(this->fullType);
}


char Message::hsvBit()
{
  return HSVBIT(this->fullType);
}


char Message::type()
{
  return MSGBITS(this->fullType);
}


char Message::getLen()
{
  return this->len;
}


char* Message::getBytes()
{
  return this->bytes;
}

