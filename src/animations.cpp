#include "animations.h"


static struct CRGB* leds = 0;


void initializeAnimations(MessageServer* messageServer, unsigned int numLEDs)
{
  if (leds) delete(leds);
  leds = new struct CRGB[numLEDs];
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLEDs);
  FastLED.setBrightness(10);

  messageServer.subscribe(new BrightenssParser());
  messageServer.subscribe(new SolidParser());
  messageServer.subscribe(new FlashSequenceParser());
}



msgHandled_t BrightnessParser::checkMessage(Message *message)
{
  // Check message byte. Can return early if its not our type
  if (message->type() != BRIGHTNESS_MSG) {
    return MSG_NOTHANDLED;
  }

  // Brightness should have one extra byte
  if (message->len == 1) {
    return MSG_HANDLED;
  }
  return MSG_MALFORMED;
}

msgHandled_t BrightenssParser::handleMessage(Message* message)
{
  // Verify that this is a message we should handle
  msgHandled_t handled = this->handleMessage();
  if (handled != MSG_HANDLED) {
    return handled;
  }

  if (message->readBit()) {
    // Read current state

  } else {
    // Set new state
    FastLED.setBrightenss(message->getData()[0]);
  }

  return MSG_HANDLED;
}



msgHandled_t SolidParser::checkMessage(Message *message)
{
  // Check message byte. Can return early if its not our type
  if (message->type() != FULL_STRING_MSG) {
    return MSG_NOTHANDLED;
  }

  // full string message should have 3 extra bytes
  if (message->len == 3) {
    return MSG_HANDLED;
  }
  return MSG_MALFORMED;
}

msgHandled_t SolidParser::handleMessage(Message* message)
{
  // Verify that this is a message we should handle
  msgHandled_t handled = this->handleMessage();
  if (handled != MSG_HANDLED) {
    return handled;
  }

  if (message->readBit()) {
    // Read current state

  } else {
    // Set new state

  }

  return MSG_HANDLED;
}



msgHandled_t FlashSequenceParser::checkMessage(Message *message)
{
  // Check message byte. Can return early if its not our type
  if (message->type() != FULL_CYCLE_N_MSG) {
    return MSG_NOTHANDLED;
  }

  // full string message should have 1 + 3n extra bytes
  char n = message.getData()[0];
  if (message->len == 1 + 3*n) {
    return MSG_HANDLED;
  }
  return MSG_MALFORMED;

}

msgHandled_t FlashSequenceParser::handleMessage(Message* message)
{
  // Verify that this is a message we should handle
  msgHandled_t handled = this->handleMessage();
  if (handled != MSG_HANDLED) {
    return handled;
  }

  if (message->readBit()) {
    // Read current state

  } else {
    // Set new state

  }

  return MSG_HANDLED;
}

