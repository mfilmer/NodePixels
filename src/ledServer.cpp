#include "ledServer.h"

#define NUM_LEDS 300

static const unsigned long timeout = 100;


// Initialize LED server
// Must be called once before anything else
void initLEDServer(int numLEDs)
{
  initAnimations(NUM_LEDS);
}

// Check if the server received client commands
// Returns true if a message was handled
bool ProcessServerMessages(WiFiServer server)
{
  WiFiClient client;
  if (client = server.available()) {
    char buff[BUFFLEN];
    readline(client, buff, timeout);

    parseCommand(client, buff);

    client.stop();
    return true;
  }
  return false;
}

// Read a line from the client
unsigned int readline(WiFiClient client, char* buffer, unsigned long timeout)
{
  unsigned long currentTime = millis();
  unsigned long startTime = currentTime;
  unsigned int i = 0;
  while (client.connected() && currentTime - startTime < timeout && i < BUFFLEN-1) {
    if(client.available()) {
      char c = client.read();
      if (c == '\n') 
        break;
      buffer[i] = c;
      i = i + 1;
    }

    currentTime = millis();
  }

  buffer[i] = 0;
  return i;
}




struct CycleDef* parseCycle(char* buff)
{
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

  CycleDef cycleDef = new CycleDef(nColors);
  cycleDef.delay = delay;

  for (int i = 0;i < nColors;i++) {
    cycleDef.colors[i] = CRGB();
  }

  return cycleDef;
}

// Parse a command and call the related function
void parseCommand(WiFiClient client, char* buff)
{
  // Process new style commands
  switch (buff[0]) {
    case FULL_STRING_HSV_BYTE:
      // Verify that buff is long enough
      if (strlen(buff) == 4) {
        CHSV chsv(buff[1], buff[2], buff[3]);
        SetSingleColor(chsv);
        client.print("ack\n");
        return;
      }
      break;
    case FULL_STRING_RGB_BYTE:
      // Verify that buff is long enough
      if (strlen(buff) == 4) {
        CRGB crgb(buff[1], buff[2], buff[3]);
        SetSingleColor(crgb);
        client.print("ack\n");
        return;
      }
      break;
      case SET_BRIGHTNESS_BYTE:
      // Verify buff is right length
      if (strlen(buff) == 2) {
        SetBrightness(buff[1]);
        client.print("ack\n");
        return;
      }
      case FULL_CYCLE_N_BYTE:
      // next 2 bytes are number of colors
      // 2 bytes after that are delay in ms
      // Then each 3 byte sequence is a color in RGB
      break;
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

