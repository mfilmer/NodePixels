#include "ledProtocol.h"

void initLedComm(unsigned short nLEDs)
{

}

void SetAllLEDs(struct CRGB)
{
	FastLED.fill_solid();
}
