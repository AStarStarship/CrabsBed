// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_LED_VU_METER
#define KABUKI_TEK_LED_VU_METER 1

namespace _ {

/* An LED VU Meter
    i.e. volume bar. */
template <IUA kNumSegments>
class LedVuMeter {
 public:
  /* Default constructor initializes LEDs in off state. */
  LedVuMeter();

  /* Prints this object to the console. */
  void Print();

 private:
  IUA value;  //< The value of the VU meter.
};
}  //< namespace _
#endif
