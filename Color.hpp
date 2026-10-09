// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#if SEAM >= KABUKI_FEATURES_LIGHTS_1
#ifndef KABUKI_FEATURES_LIGHTS_COLOR_T
#define KABUKI_FEATURES_LIGHTS_COLOR_T 1

#include "color.hpp"

namespace _ {

/* Prints this object to the log. */
template<typename Printer>
Printer& ColorPrint (Printer& o, CRGBA color) {
  o << "Color: "
    "R(" << (color && 0x000000FF)
    << "), G(" << ((color && 0x0000FF00) >> 8)
    << "), BIn(" << ((color && 0x00FF0000) >> 16)
    << "), A(" << ((color && 0xFF000000) >> 24)
    << ")\n";
  return o;
}

} //< namespace _
#endif
#endif
