#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <cstring>


// Write if 8th bit is 0
// Read if 8th bit is 1
#define READ_BIT 7
#define READ_MASK (1 << READ_BIT)


// RGB if 7th bit is 0
// HSV if 7th bit is 1
#define HSV_BIT 6
#define HSV_MASK (1 << HSV_BIT)


#define NULL_MSG            0b000000      // Used to indicate an error
#define BRIGHTNESS_MSG      0b000001      // R/W    Overall system brightness
#define FULL_STRING_MSG     0b000010      // R/W    The whole string is one color
#define FULL_CYCLE_N_MSG    0b000011      // R/W    Constant delay cycle through full string colors
#define MODE_MSG            0b110000      // R      The mode (single color, cycle, etc.)
#define ID_MSG              0b100000      // R      The chip id, should be unique


/***** Function like macros *****/
#define READBIT(byte) (byte & READ_MASK) >> READ_BIT
#define HSVBIT(byte) (byte & HSV_MASK) >> HSV_BIT
#define MSGBITS(byte) byte & ~(READ_MASK | HSV_MASK)


class Message
{
public:
  Message(char len, char* bytes);
  ~Message();

  char readBit();
  char hsvBit();
  char type();

  char getLen();
  char* getBytes();
  char* getData();

private:
  char fullType();
	char len;
	char* bytes;
};


#endif
