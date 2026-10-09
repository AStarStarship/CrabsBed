// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_FLYING_FADER
#define KABUKI_TEK_FLYING_FADER 1

namespace _ {

/* A bank of one or more groups of flying faders.
    Flying faders on most mixers have pages full of controls, and work similar
    to the RotaryEncoder class.
*/
class FlyingFader {
 public:
  /* Constructs a blank flying fader. */
  FlyingFader();

  /* Prints this object to a console. */
  void Print();

  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
};

class FlyingFaderOp {
 public:
  FlyingFaderOp(FlyingFader* ff);

  virtual const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  FlyingFader* ff_;  //< Pointer to the selected FlyingFader object.
};
}  //< namespace _
#endif
