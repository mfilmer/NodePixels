#import "MessageHandler.h"


MessageServer::MessageServer(char* host, unsigned int port, char queueLength)
{
  unsigned int hostLen = strlen(host);
  this->host = new char[hostLen+1];
  strcpy(this->host, host);
  this->port = port;

  this->fifo = new FIFO(queueLength);

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
    Serial.print("Station connected, IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("Starting server");

    server.begin();
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
  {;
    Serial.println("Station disconnected");
  });
}


MessageServer::~MessageServer()
{
  delete this->host;
  delete this->fifo;
}


void MessageServer::subscribe(MessageParser* parser)
{
  this->fifo.push(parser);
}


void MessageServer::service()
{
  Message* message = receivePacket();

  // If no message was read, or the queue is full try to handle a message in the queue
}


class MessageServer()
{
public:
  MessageServer(char* host, unsigned int port, char queueLength);
  ~MessageServer();

  void subscribe(MessageType type, void (*handler) ());
  void unSubscribe(MessageType type);

  void service();

  bool messageReady();
  Message nextMessage();

private:
  char* host;
  unsigned int port;

  FIFO fifo;

  Message* receivePacket(WiFiClient &client);
};


class MessageParser()
{
public:
  MessageParser(bool (*checkFcn) (char* bytes, char length));
  ~MessageParser();

  bool checkMessage(Packet *packet);
  Message parseMessage(Packet *packet);
  bool handleMessage(Message* message);
};

