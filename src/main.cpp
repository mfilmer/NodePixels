#include <ESP8266WiFi.h>
#include <Ticker.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>
#define NUM_LEDS 300
#define DATA_PIN 3

#include "FastAnimations.h"
#include "ledServer.h"

/***** Private function prototypes *****/
static void setWiFiEventHandlers();


/***** Global variables *****/
static WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;
static WiFiServer server(28924);


// Main setup function
void setup()
{
  Serial.begin(115200);
  Serial.println("\nStarted!");

  // Uncomment if we need to change the wifi network settings
  //connectToWiFi();

  setWiFiEventHandlers();

  initLEDServer(NUM_LEDS);
}


// Main loop
void loop()
{
  // Process messages from clients
  ProcessServerMessages(server);

  // Update LEDs
  ServiceAnimation();
}


// Set up the wifi connect/disconnect event handlers
// The connct handler needs to restart the server
static void setWiFiEventHandlers()
{
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


// Connect to a wifi network
// Probably going to need an ssid and password
static void connectToWiFi()
{
  const char* ssid = "";
  const char* password = "";
  WiFi.begin(ssid, password);
}
