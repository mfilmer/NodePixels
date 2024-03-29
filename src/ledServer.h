#ifndef __LEDSERVER_H__
#define __LEDSERVER_H__

#include <ESP8266WiFi.h>
#include <Ticker.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#include "FastAnimations.h"
#include "ledProtocol.h"
#include "messages.h"


void initLEDServer(int numLEDs);
unsigned int readline(WiFiClient &client, char* buffer, unsigned long timeout);
void parseCommand(WiFiClient &client, Message* message);
bool ProcessServerMessages(WiFiServer &server);

#endif
