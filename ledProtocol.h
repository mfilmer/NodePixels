#ifndef __LEDPROTOCOL_H__
#define __LEDPROTOCOL_H__

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

// Write if 8th bit is 0
// Read if 8th bit is 1
#define READ_BIT 7
#define READ_MASK (1 << READ_BIT)

// RGB if 7th bit is 0
// HSV if 7th bit is 1
#define HSV_BIT 6
#define HSV_MASK (1 << HSV_BIT)

#define SET_BRIGHTNESS_MSG  0b000001
#define FULL_STRING_MSG     0b000010
#define FULL_CYCLE_N_MSG    0b000011

/***** Function like macros *****/
#define readBit(byte) (byte & READ_MASK) >> READ_BIT
#define hsvBit(byte) (byte & HSV_MASK) >> HSV_BIT
#define messageBits(byte) byte & ~(READ_MASK | HSV_MASK)


// Definition of a full strip color cycle with constant delay
class CycleDef {
  public:
  unsigned short count;   // Number of colors to cycle though     
  unsigned int delay;     // Delay in ms between colors
  struct CHSV* colors;    // Definition of the colors at each step

  cycleDef(unsigned short newCount);

  ~cycleDef();
};

#endif
