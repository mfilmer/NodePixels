#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include <ESP8266WiFi.h>
#include "fifo.h"
#include "WiFiUtil.h"


class MessageServer()
{
public:
  MessageServer(char* host, unsigned int port, char queueLength);
  ~MessageServer();

  void subscribe(MessageParser* parser);

  void service();

private:
  char* host;
  unsigned int port;
  WifiServer* server;

  vector<MessageParser*>* fifo;

  Message* receiveMessage(WiFiClient &client);
};



class MessageParser()
{
public:
  virtual bool checkMessage(Message *message);
  virtual Message parseMessage(Message *message);
  virtual bool handleMessage(Message* message);
};

#endif
