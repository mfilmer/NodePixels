#ifndef __SEQUENCES_H__
#define __SEQUENCES_H__

#include <ESP8266WiFi.h>
#include <Ticker.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

// Function like macros
#define modAdd(a,b,max) {(a + b) % max}

void initAnimations(unsigned int newNumLEDs);
void ServiceAnimation();

void LEDsOff();
void SetBrightness(unsigned int brightness);

void SetSingleColor(struct CRGB &rgb);
void SetSingleColor(struct CHSV &hsv);


#endif
