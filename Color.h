// Copyright AStarship <https://astarship.net>.
//
// Color is a 16-bit 5-6-5 RGB value stored in an IUB:
//
//   | 15..10 | 9..4 | 3..0 |
//   |   R(5) | G(6) | B(5) |
//
// A brightness (alpha) value is carried separately by the LED classes,
// not inside the color word. Preset/rainbow tables are stored as 24-bit
// IUD and packed down to 5-6-5 on retrieval.
//
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_COLOR
#ifndef CRABS_BED_COLOR_H
#define CRABS_BED_COLOR_H

namespace _ {

typedef IUB Color;

// A list of colors that work well with RGB LEDs.
enum PresetColor {
  White       = 0xFFFFFF,
  Orchid      = 0xD670DA,
  Purple      = 0x800080,
  Violet      = 0xEE82EE,
  Indigo      = 0x82004B,
  SkyBlue     = 0xFFCE87,
  NavyBlue    = 0x800000,
  Blue        = 0x0000FF,
  Turquoise   = 0xFFF500,
  Green       = 0x00FF00,
  Yellow      = 0xFFC000,
  Gold        = 0x00D7FF,
  Orange      = 0x00A5FF,
  Pink        = 0xFFC0CB,
  Red         = 0xFF0000,
  Maroon      = 0x000080,
  Brown       = 0x2A2AA5,
  Black       = 0x000000  //< Black at the end as nil-term.
};

enum {
  NumPresetColors   = 18,   //< Number of preset colors.
  RainbowColorCount = 96,   //< Number of rainbow colors.
  BrightnessMax     = 255,  //< Max LED brightness 0 - 255.
  DefaultBrightness = 255,  //< Default LED brightness.
};

/* Returns a pointer to an array of the preset colors (24-bit IUD). */
const IUD* PresetColors();

/* Gets one of the preset colors.
@param index Color index 0..NumPresetColors-1. */
Color ColorPreset(IUC index);

/* Gets a random preset color. */
Color RandomPresetColor();

/* Gets a random color. */
Color RandomColor(IUC index);

/* Mixes two colors with equal weight. */
Color ColorMix(Color a, Color b);

/* Increases the brightness of the given color by the given delta. */
Color ChangeBrightness(Color color, IUC delta);

/* Decreases the brightness of the given color by the given delta. */
Color DecreaseBrightness(Color color, IUC delta);

/* Creates a Color from the given RGB values (0..255 each). */
Color ColorMake(IUA red, IUA green, IUA blue);

/* Gets the red value. */
IUA ColorGetRed(Color color);

/* Gets the green value. */
IUA ColorGetGreen(Color color);

/* Gets the blue value. */
IUA ColorGetBlue(Color color);

/* Mixes a channel (0..255) into the red channel using a mix ratio (0..255).
@param channel The source channel value.
@param red     The current red channel.
@param ratio   The mix ratio (0..255); 255 = replace entirely. */
IUA ColorMixRatio(IUA channel, IUA red, IUA ratio);

}  //< namespace _
#endif
#endif
