#import "MessageHandler.h"


MessageServer::MessageServer(char* host, unsigned int port, char queueLength)
{
  unsigned int hostLen = strlen(host);
  this->host = new char[hostLen+1];
  strcpy(this->host, host);
  this->port = port;

  this->fifo = new FIFO(queueLength);

  this->server = new WiFiServer(port);

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
    Serial.print("Station connected, IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("Starting server");

    this->server.begin();
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
  delete this->server;
}


void MessageServer::subscribe(MessageParser* parser)
{
  this->fifo.push(parser);
}


void MessageServer::service()
{
  Message* message = receiveMessage();

  if (message) {
    // Iterate over MessageParsers until we find which one handles it
    // Then have that one handle it

    delete message;
  }
}


Message* MessageServer::receiveMessage()
{
  WiFiClient client;
  char byte, len; bool success;
  if (client = this->server.available()) {
    // First byte should be 0
    success = readByte(client, &byte, 100);
    if (byte != 0 || success == false) {
      client.flush();
      client.stop();
      return nullptr;
    }

    // Second byte is length of transmission excluding start, stop, and length bytes.
    success = readByte(client, &len, 100);
    if (!success) {
      client.flush();
      client.stop();
      return nullptr;
    }

    // Read all the data
    char* data = new char[len];
    success = readBytes(client, data, len, 100);
    if (!success) {
      delete data;
      client.flush();
      client.stop();
      return nullptr;
    }

    // Final byte should be 0
    success = readByte(client, &byte, 100);
    if (byte != 0 || success == false) {
      delete data;
      client.flush();
      client.stop();
      return nullptr;
    }

    client.flush();
    client.stop();
    
    Message* message = new Message(len, data);
    return message;
  }
  return nullptr;
}

