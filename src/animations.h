#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include "MessageHandler.h"
#include "Messages.h"


void initializeAnimations(MessageServer* messageServer);

// Set led string overall brightness
class BrightnessParser(MessageParser)
{
public:
  msgHandled_t checkMessage(Message *message);
  msgHandled_t handleMessage(Message* message);
};

// Set led string to single solid color
class SolidParser(MessageParser)
{
public:
  msgHandled_t checkMessage(Message *message);
  msgHandled_t handleMessage(Message* message);
};


// Set led string to a flashing sequence of colors
class FlashSequenceParser(MessageParser)
{
public:
  msgHandled_t checkMessage(Message *message);
  msgHandled_t handleMessage(Message* message);
};


#endif
