// Some predefined animations
#import "FastAnimations.h"

struct HSV FlagHSV[] = {
  {RED,MED_SAT,MED_VAL},
  {WHITE,MED_SAT,MED_VAL},
  {BLUE,MED_SAT,MED_VAL}
};

struct AnimConst FlagAnim = {
  .length = 3,
  .offset = 0,
  .fillType = FILL_REPEAT,
  .hsv = FlagHSV;
};

struct LEDStripColors FlagColors = {
  .length = 300,
  .animType = ANIM_CONST,
};
