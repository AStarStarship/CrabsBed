// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_LEDVUMETERARAY
#define KABUKI_TEK_LEDVUMETERARAY 1

namespace _ {

/* An array of LEDs used for a VU Meter like on a stereo. */
template <ISC kNumSegments>
class LedVuMeterArray {
 public:
  /* Simple default constructor. */
  LedVuMeterArray() {}

  /* Gets the number of segments. */
  static ISC GetNumSegments() { return kNumSegments; }

  /* Prints this object to a console. */
  void Print() {}
};
}  //< namespace _
#endif
