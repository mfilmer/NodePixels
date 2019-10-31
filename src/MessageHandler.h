#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include "fifo.h"


class MessageServer()
{
public:
  MessageServer(char* host, unsigned int port, char queueLength);
  ~MessageServer();

  void subscribe(MessageParser* parser);

  void service();

  bool messageReady();
  Message* nextMessage();

private:
  char* host;
  unsigned int port;
  WifiServer server;

  FIFO<MessageParser*>* fifo;

  Packet receivePacket(WiFiClient &client);
};



class MessageParser()
{
public:
  MessageParser(bool (*checkFcn) (char* bytes, char length));
  ~MessageParser();

  virtual bool checkMessage(Message *message);
  virtual Message parseMessage(Message *message);
  virtual bool handleMessage(Message* message);
};

#endif
