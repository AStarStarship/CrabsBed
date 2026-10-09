// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_BOUNCYSWITCH
#define KABUKI_TEK_BOUNCYSWITCH 1

#include <mbed.h"

namespace _ {

/* A software debounced switch. */
class Switch : public _::Operation {
 public:
  /* A software debcounced switch. */
  Switch(PinName din_pin);

  /* Script operations. */
  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  DigitalIn input_;  //< The DIN pin.
};

class SwitchOp : public _::Operation {
 public:
  SwitchOp(Switch* sw);

  virtual const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  Switch* object_;  //< The Switch.
};                  //< SwitchOp
}  //< namespace _
#endif
