#include <ESP8266WiFi.h>
#include <Ticker.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>
#define NUM_LEDS 300
#define DATA_PIN 3

#include "FastAnimations.h"
#include "ledServer.h"

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define DEBUG(commands) commands
#else
#define DEBUG(commands)
#endif



WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;
WiFiServer server(28924);

const unsigned long timeout = 1000;

bool calledFlag = false;

void connectToWiFi()
{
  const char* ssid = "SpaceCrusher 2.4";
  const char* password = "";
  WiFi.begin(ssid, password);
}

void setup()
{
  Serial.begin(115200);
  DEBUG(Serial.println("\nStarted!");)

  // Uncomment if we need to change the wifi network settings
  //connectToWiFi();

  // Register wifi connect and disconnect handlers
  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
    DEBUG(Serial.print("Station connected, IP: ");)
    DEBUG(Serial.println(WiFi.localIP());)
    DEBUG(Serial.println("Starting server");)

    server.begin();
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
  {;
    DEBUG(Serial.println("Station disconnected");)
    // Clean up any server memory that needs to be freed
  });


  initLEDServer(NUM_LEDS);
}


void loop()
{
  // Process messages from clients
  checkForCommands(server);

  // Update LEDs
  ServiceAnimation();
}
