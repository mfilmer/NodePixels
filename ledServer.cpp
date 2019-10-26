#include "ledServer.h"

CRGB leds[NUM_LEDS];

// Initialize LED server
// Must be called once before anything else is done
void initLEDServer(int numLEDs)
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLEDs);
  FastLED.setBrightness(10);
}

// Check if the server received commands
void checkForCommands(WiFiServer server)
{

  if (client = server.available()) {
    char buff[BUFFLEN];
    readline(client, buff, timeout);

    parseCommand(client, buff);

    client.stop();
  }
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

// Parse a command and call the related function
void parseCommand(WiFiClient client, char* buff)
{
  switch (buff[0]) {
    case FULL_STRING_HSV_CHAR:
      // Verify that buff is long enough
      if (strlen(buff) == 4) {
        //Serial.println("Setting HSV");
        struct HSV hsv;
        hsv.H = buff[1];
        hsv.S = buff[2];
        hsv.V = buff[3];
        SetSingleColor(&hsv);
        client.print("ack\n");
        return;
      }
      break;
    case FULL_STRING_RGB_CHAR:
      // Verify that buff is long enough
      if (strlen(buff) == 4) {
        //Serial.println("Setting RGB");
        struct RGB rgb;
        rgb.R = buff[1];
        rgb.G = buff[2];
        rgb.B = buff[3];
        SetSingleColor(&rgb);
        client.print("ack\n");
        return;
      }
      break;
      case BRIGHTNESS_CHAR:
      // Verify buff is right length
      if (strlen(buff) == 2) {
        SetBrightness(buff[1]);
        client.print("ack\n");
        return;
      }
      break;
  }
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

  client.print("ack\n");
}

