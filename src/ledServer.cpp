/** @file */ 

#include "ledServer.h"

#define BUFFLEN 32
#define NUM_LEDS 300
#define TIMEOUT 100

/***** Private functions *****/
CycleDef* parseCycle(char* buff);
static MessageType readMessage(WiFiClient &client, Message *message);
static inline bool readByte(WiFiClient &client, char* bytes, unsigned int timeout);
static bool readBytes(WiFiClient &client, char* bytes, unsigned int nBytes, unsigned int timeout);


// Initialize LED server
// Must be called once before anything else
void initLEDServer(int numLEDs)
{
  initAnimations(NUM_LEDS);
}

/*
 * @brief Checks and processes client commands
 *
 * Returns true if a message was handled
 */
bool ProcessServerMessages(WiFiServer &server)
{
  WiFiClient client;
  if (client = server.available()) {
    Message message;
    MessageType type = readMessage(client, &message);
    if (type)
      parseCommand(client, &message);

    client.stop();
    return true;
  }
  return false;
}




/**
 * @brief Read a message from the client
 */
static MessageType readMessage(WiFiClient &client, Message *message)
{
  unsigned long currentTime = millis();
  unsigned long startTime = currentTime;

  message->type = NULL_MSG;

  // Read first byte (message type)
  readByte(client, &message->type, TIMEOUT);

  // If we didn't get a real message, give up and return
  if (message->type == NULL_MSG) {
    client.flush();
    client.stop();
    return NULL_MSG;
  }


  // Determine expected remaining byte count
  unsigned int nExpBytes = 0;
  switch (message->type) {
    case BRIGHTNESS_MSG:
      nExpBytes = 1;
      break;
    case FULL_STRING_MSG:
      nExpBytes = 3;
      break;
    case FULL_CYCLE_N_MSG:
    {
      char count = 0;
      bool gotCount = readByte(client, &count, TIMEOUT);
      if (gotCount) {
        nExpBytes = 2 + 3*gotCount;
      }
      break;
    }
  }

  char *bytes = new char[nExpBytes];
  bool gotBytes = readBytes(client, bytes, nExpBytes, TIMEOUT);
  if (gotBytes) {
    // Good message. Assemble and return the message type
    message->len = nExpBytes;
    message->bytes = bytes;
    return message->type;
  } else {
    // Corrupt message. Cleanup memory and NULL_MSG
    delete bytes;
    return NULL_MSG;
  }

}



/**
 * @brief Parse a color cycle command
 *
 * Returns a CycleDef object that will need to be manually deleted
 * when it is no longer needed
 */
CycleDef* parseCycle(char* buff)
{
  Serial.println("Parsing cycle...");

  // Minimum size is 10 bytes for a 2 color cycle
  unsigned short nChars = strlen(buff);
  if (nChars <= 10) {
    return 0;
  }

  // Size must be nColors * 3 + 4
  unsigned short nColors = buff[1];
  if (nChars != nColors * 3 + 4) {
    return 0;
  }

  unsigned int delay = buff[2];
  delay = delay << 8;
  delay = delay + buff[3];

  CycleDef *cycleDef = new CycleDef(nColors);
  cycleDef->delay = delay;

  for (int i = 0;i < nColors;i++) {
    unsigned short start = 4 + i*3;
    cycleDef->colors[i] = CRGB(buff[start], buff[start+1], buff[start+2]);
  }

  return cycleDef;
}

// Parse a command and call the related function
void parseCommand(WiFiClient &client, Message* msg)
{
  Serial.println("Parsing command");
  // Process new style commands
  switch (msg->type) {
    case FULL_STRING_MSG:
    {
      Serial.println("Full string message");
      CRGB crgb(msg->bytes[0], msg->bytes[1], msg->bytes[2]);
      SetSingleColor(crgb);
      client.print("ack\n");
      return;
    }
    case BRIGHTNESS_MSG:
      Serial.println("Brightness message");
      SetBrightness(msg->bytes[0]);
      client.print("ack\n");
      return;
    case FULL_CYCLE_N_MSG:
    {
      char buff[32];
      Serial.println("Full cycle message");
      CycleDef *cycleDef = parseCycle(buff);
      if (cycleDef) {
        SetCycle(cycleDef);
        delete cycleDef;
      }
      break;
    }
  }

/*
  // Handle remaining old style commands
  if (strcmp(buff, "start") == 0) {
    Serial.println("Starting");
    StartTestAnimation();
    //setCycleLEDByIndex(SEQ_SLOW);
  } else if (strcmp(buff, "stop") == 0) {
    Serial.println("Stopped");
    //setOffLED();
    FastLED.clear();
    FastLED.show();
  } else if (strcmp(buff, "fast") == 0) {
    Serial.println("Fast mode");
    //setCycleLEDByIndex(SEQ_FAST);
  } else if (strcmp(buff, "red") == 0) {
    fill_solid( leds, 40, CRGB::Red);
    FastLED.show();
  } else if (strcmp(buff, "green") == 0) {
    fill_solid( leds, 40, CRGB::Green);
    FastLED.show();
  } else if (strcmp(buff, "blue") == 0) {
    fill_solid( leds, 40, CRGB::Blue);
    FastLED.show();
  } else if (strcmp(buff, "white") == 0) {
    fill_solid( leds, 40, CRGB::White);
    FastLED.show();
  } else if (strcmp(buff, "fancy") == 0) {
    leds[30] = CRGB::Red;
    FastLED.show();
  } else {
    client.print("message not recognized\n");
    return;
  }
  */

  client.print("ack\n");
}

