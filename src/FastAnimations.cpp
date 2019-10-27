#include "FastAnimations.h"

#define DATA_PIN 3

/***** Private function prototypes *****/
static void printHSV(struct CHSV &hsv);
static void printRGB(struct CRGB &rgb);
static void stopAnimation();

/***** Animation functions *****/
static void cycleAnimation();

/***** Private variables  ****/
static struct CRGB* leds = 0;
static unsigned int numLEDs;
static Ticker ticker;
static bool sequenceUpdateReady = false;
static char buff[32];


static void (*animStepFcn) () = 0;
static CycleDef cycleDef;



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
  stopAnimation();
  FastLED.clear();
  FastLED.show();
  ticker.detach();
}


// Set the overall brightness scaling factor
void SetBrightness(unsigned int brightness)
{
  char str[32];
  sprintf(str, "Bright: %d", brightness);
  Serial.println(str);
  FastLED.setBrightness(brightness);
  FastLED.show();
}


// Set the whole strip to one color
void SetSingleColor(struct CRGB &rgb)
{
  stopAnimation();
  printRGB(rgb);
  fill_solid(leds, numLEDs, rgb);
  FastLED.show();
}
void SetSingleColor(struct CHSV &hsv)
{
  stopAnimation();
  printHSV(hsv);
  fill_solid(leds, numLEDs, hsv);
  FastLED.show();
}


// Cycle through whole strip colors
void SetCycle(CycleDef *newCycleDef)
{
  // Stop whatever is currently running
  stopAnimation();

  // Store this cycle def
  cycleDef = *newCycleDef;

  // Fill in first sequence and show it
  fill_solid(leds, numLEDs, cycleDef.next());
  FastLED.show();

  // Start the animation
  animStepFcn = cycleAnimation;
  ticker.attach_ms(cycleDef.delay, cycle_ISR);

  // Fill in next step. I think this should improve timing a bit
  fill_solid(leds, numLEDs, cycleDef.next());
}


// Called by the user to advance the sequence to the next step
void ServiceAnimation()
{
  Serial.println("Service Animation Start");

  // Verify an update is needed, return if its not
  if (!sequenceUpdateReady) {
    Serial.println("Animation not serviced");
    return;
  }

  // Do the update
  if (animStepFcn) {
    animStepFcn();
  }

  // Indicate that update is no longer ready
  sequenceUpdateReady = false;

  Serial.println("Animation successfully serviced");
}


/***** Private Functions *****/
// Print the given HSV to the serial port
// Serial must already be initialized for this to work
static void printHSV(struct CHSV &hsv)
{
  sprintf(buff, "H: %d, S: %d, V: %d\n", hsv.h, hsv.s, hsv.v);
  Serial.print(buff);
}

static void printRGB(struct CRGB &rgb)
{
  sprintf(buff, "R: %d, G: %d, B: %d\n", rgb.r, rgb.g, rgb.b);
  Serial.print(buff);
}

// Disable the animation callback and ticker
static void stopAnimation()
{
  ticker.detach();
  animStepFcn = 0;
}

/***** Animation functions *****/
static void cycleAnimation()
{
  // Show the already populated leds
  FastLED.show();

  // Populate the next set
  //fill_solid(leds, numLEDs, cycleDef.next());
}