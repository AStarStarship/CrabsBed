// Copyright AStarship <https://astarship.net>.
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_COLOR
#include "Color.h"

namespace _ {

// The preset table is 24-bit RGB (IUD storage) so the full palette fits;
// Color (IUB) is the 16-bit 5-6-5 packed form used for single-LED output.
static const IUD preset_colors[] = {
    0xFFFFFF, 0xD670DA, 0x800080, 0xEE82EE, 0x82004B, 0xFFCE87,
    0x800000, 0x0000FF, 0xFFF500, 0x00FF00, 0xFFC000, 0x00D7FF,
    0x00A5FF, 0xFFC0CB, 0xFF0000, 0x000080, 0x2A2AA5, 0x000000};

/* Returns a pointer to an array of the preset colors (24-bit). */
const IUD* PresetColors() { return preset_colors; }

/* Gets one of the preset colors, converted from 24-bit to 16-bit 5-6-5.
@param index Color index 0..NumPresetColors-1. */
Color ColorPreset(IUC index) {
  if (index >= NumPresetColors) index = 0;
  IUD c = preset_colors[index];
  IUA r8 = (IUA)((c >> 16) & 0xFF);
  IUA g8 = (IUA)((c >> 8) & 0xFF);
  IUA b8 = (IUA)(c & 0xFF);
  return ColorMake(r8, g8, b8);
}

/* Gets a random preset color. */
Color RandomPresetColor() { return ColorPreset(Random(0, NumPresetColors)); }

/* Gets a random color. */
Color RandomColor(IUC index) {
  (void)index;
  IUC red = Random(0, BrightnessMax);
  IUC green = Random(0, BrightnessMax);
  IUC blue = Random(0, BrightnessMax);
  return ColorMake(red, green, blue);
}

/* Mixes two colors with equal weight. The channel getters return the
already-packed 5/6-bit values, so pack them directly (do NOT route back
through ColorMake, which expects 8-bit inputs). */
Color ColorMix(Color a, Color b) {
  IUA red = (IUA)((ColorGetRed(a) + ColorGetRed(b)) / 2);
  IUA green = (IUA)((ColorGetGreen(a) + ColorGetGreen(b)) / 2);
  IUA blue = (IUA)((ColorGetBlue(a) + ColorGetBlue(b)) / 2);
  return (Color)((red << 11) | (green << 5) | blue);
}

/* Creates a 16-bit 5-6-5 Color from 8-bit RGB values.
Layout: R = bits 15..11 (5), G = bits 10..5 (6), B = bits 4..0 (5).
@param red 0..255, green 0..255, blue 0..255. */
Color ColorMake(IUA red, IUA green, IUA blue) {
  IUA r5 = red >> 3;   //< top 5 bits -> bits 15..11
  IUA g6 = green >> 2; //< top 6 bits -> bits 10..5
  IUA b5 = blue >> 3;  //< top 5 bits -> bits 4..0
  return (Color)((r5 << 11) | (g6 << 5) | b5);
}

/* Gets the red value (5-bit, 0..31). */
IUA ColorGetRed(Color color) { return (IUA)(color >> 11) & 0x1F; }

/* Gets the green value (6-bit, 0..63). */
IUA ColorGetGreen(Color color) { return (IUA)(color >> 5) & 0x3F; }

/* Gets the blue value (5-bit, 0..31). */
IUA ColorGetBlue(Color color) { return (IUA)color & 0x1F; }

/* Mixes a channel into the red channel using a mix ratio.
@param channel The source channel value (5-bit).
@param red     The current red channel (5-bit).
@param ratio   The mix ratio (0..255); 255 = replace entirely. */
IUA ColorMixRatio(IUA channel, IUA red, IUA ratio) {
  return (IUA)((channel * ratio + red * (BrightnessMax - ratio) + 127) /
               BrightnessMax);
}

}  //< namespace _
#endif
