// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_ELECTROLYTICMIC
#define KABUKI_TEK_ELECTROLYTICMIC 1

#include "photosensor.h"

namespace _ {

/* An electrolytic microphone. */
class ElectrolyticMic {
 public:
  /* Constructs . */
  ElectrolyticMic(PinName pin);

  /* Sets the minimum value to the given value. */
  IUB GetMin();

  /* Sets the minimum value to the given value. */
  void SetMin(IUB value);

  /* Gets the max value */
  IUB GetMax();

  /* Attempts to set the max to the new value. */
  void SetMax(IUB value);

  /* Bounds the min and max. */
  void BoundMinMax();

  /* Reads the value of the microphone. */
  IUB Read();

  /* Prints this object to a terminal. */
  void Print();

 private:
  IUB min_,         //< The normal min mic value.
      max_;         //< The normal max mic value.
  AnalogIn input_;  //< The analog input pin.
};
}  //< namespace _
#endif
