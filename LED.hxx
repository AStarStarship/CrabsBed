// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
#if SEAM >= CRABS_BED_LEDS
#include "LED.h"

namespace _ {

/* Prints this object to a terminal. */
void Led::Print(const CHA* label) {
  if (label != NILP) StdOut() << label << " ";
  StdOut() << "Led(bit:" << bit_number_ << ", row:" << row_number_ << ")\n";
}

}  //< namespace _
#endif
