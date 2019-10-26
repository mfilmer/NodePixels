#ifndef __SEQUENCES_H__
#define __SEQUENCES_H__

#include <ESP8266WiFi.h>
#include <Ticker.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>
#define NUM_LEDS 300
#define DATA_PIN 3

// Function like macros
#define modAdd(a,b,max) {(a + b) % max}

#define MAX_SEQUENCES 16

// Sequence names
#define SEQ_SLOW 0
#define SEQ_FAST 1

// Some colors
#define RED 0
#define BLUE 64
#define GREEN 128
#define PURPLE 82
#define VIOLET 205
#define ORANGE 2
#define PINK 17

#define MED_SAT 128
#define MED_VAL 128

struct Sequence;
struct HSV;

// An animation is made up of a sequence of animations until at the
// final level an ANIM_CONST, which is a fixed list of colors along
// the strip, repeated, or extended, if necessary
enum AnimType {
  ANIM_SINGLE,        // Single HSV value
  ANIM_CONST,         // Constant colors, or off
  ANIM_SEQUENCE,      // Sequence of animations with fixed delay
  ANIM_SEQUENCE_ADV,  // Sequence of animations with variable delay
  ANIM_RING,          // Constant colors to slide along the strip, circling back to start
  ANIM_BOUNCE         // Bounce a given distance
};

// How to extend the colors to fill the strip
enum FillType {
  FILL_REPEAT,    // Cycle the sequence
  FILL_FINAL      // Uses the last color in the sequence to fill
};

// A single color
struct HSV {
  unsigned short H;
  unsigned short S;
  unsigned short V;
};

struct RGB {
  unsigned short R;
  unsigned short G;
  unsigned short B;
};

// Top level animation container
struct LEDStripColors {
  unsigned short length;    // Number of LEDs in the strip
  enum AnimType animType;   // Type of animation
  void* animation;          // Data for the specified animation type
};

// Struct holding animation information for ANIM_SINGLE
struct AnimSingle {
  struct HSV* hsv;
};

// Struct holding animation information for ANIM_CONST
struct AnimConst {
  unsigned short length;  // Number of colors in the array
  unsigned short offset;  // How many leds into the strip to start the sequence
  enum FillType fillType; // How to fill remaining space
  struct HSV* hsv;        // Array of HSV values to place along the strip.
};

// Struct holding animation information for ANIM_SEQUENCE
struct AnimSequence {
  unsigned long delay;        // Delay between steps in ms
  unsigned short index;       // Current index
  unsigned short length;      // Number of animation steps
  enum AnimType* animTypes;   // Types of each animation step
  void* anims;
};

// Struct holding animation information for ANIM_SEQUENCE_ADV
struct AnimSequenceAdv {
  unsigned long* delay;       // Delay between each step in ms
  unsigned short index;       // Current index
  unsigned short length;      // Number of animation steps
  enum AnimType* animTypes;   // Types of each animation step
  void* anims;
};

// Struct holding animation information for ANIM_RING
struct AnimRing {
  unsigned long delay;      // Delay between steps in ms
  unsigned short step;      // How many leds to advance by each step
  enum AnimType animType;   // Type of animation to slide along the ring
  void* anim;               // Animation to slide along the ring
};

// Struct holding animation information for ANIM_BOUNCE
//struct AnimBounce {
//  unsigned short index;   // How many steps into the animation are we
//  short direction;        // Current step direction
//  short step;             // How far to step each cycle
//  unsigned short nSteps;  // How many steps before reversing
//  unsigned long delay;    // Delay between steps in ms
//  enum AnimType animType; // Type of animation to bounce on the ring
//  void anim*;             // Animation to bounce on the ring
//};



// Exposed functions
void AnimaitonOff();
void SetSingleColor(struct HSV* hsv);
void SetSingleColor(struct RGB* rgb);
void SetBrightness(short int brightness);
void SetAnimation(struct LEDStripColors* ledStripColors);
void PauseAnimation();
void ResumeAnimation();
void ServiceAnimation();

void StartTestAnimation();
void printHSV(struct HSV* hsv);


// Built in animations
static struct HSV hsvBlue = {50,100,100};

static struct AnimSingle animBlue = {.hsv = &hsvBlue};

static struct AnimRing blueRing = {
  .delay = 100,
  .step = 1,
  .animType = ANIM_SINGLE,
  .anim = &animBlue
};


#endif
