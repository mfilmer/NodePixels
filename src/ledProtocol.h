#ifndef __LEDPROTOCOL_H__
#define __LEDPROTOCOL_H__

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>


// Definition of a full strip color cycle with constant delay
class CycleDef
{
  public:
  unsigned short count;   // Number of colors to cycle though     
  unsigned int delay;     // Delay in ms between colors
  unsigned int index;     // Current index in the animation
  struct CRGB* colors;    // Definition of the colors at each step

  CycleDef();
  CycleDef(unsigned short newCount);

  CycleDef(const CycleDef &oldDef);

  ~CycleDef();

  CRGB next();
};


#endif
