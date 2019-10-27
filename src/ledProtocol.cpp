#include "ledProtocol.h"

void initLedComm(unsigned short nLEDs)
{

}

void SetAllLEDs(struct CRGB &rgb)
{
  //fill_solid(leds, NUM_LEDS, rgb);
}


// Definition of a full strip color cycle with constant delay
CycleDef::CycleDef() {}
CycleDef::CycleDef(unsigned short newCount)
{
  colors = new CRGB[newCount];
  count = newCount;
  index = 0;
}

CycleDef::CycleDef(const CycleDef &oldDef)
{
  count = oldDef.count;
  index = oldDef.index;
  colors = new CRGB[count];
  memcpy(colors, oldDef.colors, count * sizeof(struct CRGB));
}

CycleDef::~CycleDef()
{
  delete colors;
}

CRGB CycleDef::next()
{
  CRGB crgb = colors[index];
  index = (index + 1) % count;
  return crgb;
}

