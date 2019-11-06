#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include <ESP8266WiFi.h>
#include "fifo.h"
#include "WiFiUtil.h"


#define MSG_HANDLED 0
#define MSG_NOTHANDLED 1
#define MSG_MALFORMED 2

typedef char msgHandled_t



class MessageServer()
{
public:
  MessageServer(char* host, unsigned int port, char maxParsers);
  ~MessageServer();

  void subscribe(MessageParser* parser);

  void service();

private:
  char* host;
  unsigned int port;
  WifiServer* server;

  vector<MessageParser*>* parsers;

  Message* receiveMessage(WiFiClient &client);
};



class MessageParser()
{
public:
  virtual mesHandled_t checkMessage(Message *message);
  virtual msgHandled_t handleMessage(Message* message);
};

#endif
