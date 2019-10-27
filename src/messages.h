#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "ledProtocol.h"

class Message
{
  public:
  MessageType type;
  unsigned short len;
  char *bytes;

  Message();
  Message(char* rawMsg);

  Message(const Message &oldMsg);

  ~Message();
};


#endif
