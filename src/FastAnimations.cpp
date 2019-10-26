#include "FastAnimations.h"

#define DATA_PIN 3

/***** Private function prototypes *****/
void printHSV(struct CHSV &hsv);
void printRGB(struct CRGB &rgb);


/***** Private variables  ****/
static struct CRGB* leds = 0;
static unsigned int numLEDs;
static Ticker ticker;
static bool sequenceUpdateReady = false;
static char buff[128];


void (*animStepFcn) () = 0;


void initAnimations(unsigned int newNumLEDs)
{
  numLEDs = newNumLEDs;
  if (leds) delete(leds);
  leds = new struct CRGB[numLEDs];
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLEDs);
  FastLED.setBrightness(10);
}


// Callback to notify us of when we need to do an update
void ICACHE_RAM_ATTR cycle_ISR()
{
  sequenceUpdateReady = true;
}


/***** Public functions *****/
// Turn all the LEDs off
void LEDsOFf()
{
  ticker.detach();
  FastLED.clear();
  FastLED.show();
  ticker.detach();
}


// Set the overall brightness scaling factor
void SetBrightness(unsigned int brightness)
{
  FastLED.setBrightness(brightness);
  FastLED.show();
}


// Set the whole strip to one color
void SetSingleColor(struct CRGB &rgb)
{
  ticker.detach();
  printRGB(rgb);
  fill_solid(leds, numLEDs, rgb);
  FastLED.show();
}
void SetSingleColor(struct CHSV &hsv)
{
  ticker.detach();
  printHSV(hsv);
  fill_solid(leds, numLEDs, hsv);
  FastLED.show();
}




// Called by the user to advance the sequence to the next step
void ServiceAnimation()
{
  // Verify an update is needed, return if its not
  if (!sequenceUpdateReady) {
    return;
  }

  // Do the update
  if (animStepFcn) {
    animStepFcn();
  }

  // Indicate that update is no longer ready
  sequenceUpdateReady = false;
}

/***** Private Functions *****/
// Print the given HSV to the serial port
// Serial must already be initialized for this to work
void printHSV(struct CHSV &hsv)
{
  sprintf(buff, "H: %d, S: %d, V: %d\n", hsv.h, hsv.s, hsv.v);
  Serial.print(buff);
}

void printRGB(struct CRGB &rgb)
{
  sprintf(buff, "R: %d, G: %d, B: %d\n", rgb.r, rgb.g, rgb.b);
  Serial.print(buff);
}









/*


void testStepFcn()
{
  if(leds[stepInd].r==0 && leds[stepInd].g==0 && leds[stepInd].b==0) {
    leds[stepInd] = CRGB::Red;
  } else {
    leds[stepInd].r = 0;
    leds[stepInd].g = 0;
    leds[stepInd].b = 0;
  }
  FastLED.show();

  stepInd = modAdd(stepInd, (unsigned short) 1, stop);
}



void StartTestAnimation()
{
  ticker.detach();
  ticker.attach_ms(50,testStepFcn);
}


// Set a new animation
void SetAnimation(struct LEDStripColors* ledStripColors)
{

}


// Pause the animation but keep the leds lit as they currently are
void PauseAnimation()
{
  ticker.detach();
}


// Resume the animation
void ResumeAnimation()
{
  // TODO: properly include the delay
  ticker.attach_ms(1000,cycle_ISR);
}

// Advance the entire animation by one step
void animationTick(struct LEDStripColors ledStripColors)
{

}

// Returns true if advancing caused a roll over and the parent
// animation needs to also advance
bool advanceAnimation(enum AnimType animType, void* anim)
{
  switch (animType) {
    case ANIM_SINGLE:
      return true;
    case ANIM_RING:
      break;
  }
}

*/