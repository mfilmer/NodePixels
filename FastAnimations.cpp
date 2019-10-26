#include "FastAnimations.h"

extern CRGB leds[];


/***** Private function prototypes *****/
void printHSV(struct HSV* hsv);
void printRGB(struct RGB* rgb);
void animationTick(struct LEDStripColors ledStripColors);
void testStepFcn();


/***** Private variables  ****/
static Ticker ticker;
static char printBuff[128];
static bool sequenceUpdateReady = false;

static unsigned short start = 0;
static unsigned short stop = 40;
static unsigned short stepInd = 0;

void (*animStepFcn) () = testStepFcn;


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

// Callback to notify us of when we need to do an update
void ICACHE_RAM_ATTR cycle_ISR()
{
  sequenceUpdateReady = true;
}


/***** Public functions *****/
// Turn all the LEDs off
void AnimaitonOff()
{
  // TODO: Also need to turn the lights off
  Serial.println("Lights off");
  ticker.detach();
}

inline const struct CHSV chsvHelper(struct HSV* hsv)
{
  return CHSV(hsv->H, hsv->S, hsv->V);
}

inline const struct CRGB crgbHelper(struct RGB* rgb)
{
  return CRGB(rgb->R, rgb->G, rgb->B);
}



// Set the LED strip to be all a single color
void SetSingleColor(struct HSV* hsv)
{
  printHSV(hsv);
  fill_solid(leds, NUM_LEDS, chsvHelper(hsv));
  FastLED.show();
}

void SetSingleColor(struct RGB* rgb)
{
  printRGB(rgb);
  fill_solid(leds, NUM_LEDS, crgbHelper(rgb));
  FastLED.show();
}


void SetBrightness(short int brightness)
{
  FastLED.setBrightness(brightness);
  FastLED.show();
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



// Called by the user to advance the sequence to the next step
void ServiceAnimation()
{
  // Verify an update is needed, return if its not
  if (!sequenceUpdateReady) {
    return;
  }

  // Do the update
  if (testStepFcn) {
    testStepFcn();
  }
  //seq->index = (seq->index + 1) % seq->len;
  //printHSV(&seq->seq[seq->index]); 

  // Indicate that update is no longer ready
  sequenceUpdateReady = false;
}

/***** Private Functions *****/
// Print the given HSV to the serial port
// Serial must already be initialized for this to work
void printHSV(struct HSV* hsv)
{
  sprintf(printBuff, "H: %d, S: %d, V: %d\n", hsv->H, hsv->S, hsv->V);
  Serial.print(printBuff);
}

void printRGB(struct RGB* rgb)
{
  sprintf(printBuff, "R: %d, G: %d, B: %d\n", rgb->R, rgb->G, rgb->B);
  Serial.print(printBuff);
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

