#include "ledProtocol.h"

void initLedComm(unsigned short nLEDs)
{

}

void SetAllLEDs(struct CRGB &rgb)
{
	//fill_solid(leds, NUM_LEDS, rgb);
}



// Definition of a full strip color cycle with constant delay
cycleDef::cycleDef(unsigned short newCount)
{
colors = new CHSV[newCount];
count = newCount;
}

cycleDef::~cycleDef()
{
free(colors);
}

