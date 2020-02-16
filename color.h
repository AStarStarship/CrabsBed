/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /color.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= KABUKI_FEATURES_LIGHTS_1
#ifndef KABUKI_FEATURES_LIGHTS_COLOR_C
#define KABUKI_FEATURES_LIGHTS_COLOR_C 1

// A ABGR Color where A is brightness.
typedef IUC CRGBA;

namespace _ {


// A list of colors that work well with RGB LEDs.
typedef enum {
    kRGBAUI4White       = 0xFFFFFF,
    kRGBAUI4Orchid      = 0xDA70D6,
    kRGBAUI4Purple      = 0x800080,
    kRGBAUI4Violet      = 0xEE82EE,
    kRGBAUI4Indigo      = 0x4B0082,
    kRGBAUISkyBlue     = 0x87CEFF,
    NavyBlue    = 0x000080,
    Blue        = 0xFF0000,
    Turquoise   = 0x00F5FF,
    Green       = 0x00FF00,
    Yellow      = 0xFFC0CB,
    Gold        = 0xFFD700,
    Oragne      = 0xFFA500,
    Pink        = 0xFFC0CB,
    Red         = 0x0000FF,
    Maroon      = 0x800000,
    Brown       = 0xA52A2A,
    Black       = 0x000000      //< Black at the end as nil-term CHA.
} PresetColor;

enum {
    kNumPresetColors   = 18,    //< Number of preset colors.
    kNumRainbowColors  = 96,    //< Number of rainbow colors.
    kMaxBrightness     = 255,   //< Max LED brightness 0 - 255.
    kRedMixRatio       = 255,   //< Red LED mix ratio (0-255)/256.
    kGreenMixRatio     = 255,   //< Green LED mix ratio (0-255)/256.
    kBlueMixRatio      = 255,   //< Blue LED mix ratio (0-255)/256.
    kDefaultBrightness = 255,   //< Default LED brightness.
};

/* Returns a pointer to an array of the rainbow colors. */
const CRGBA* RainbowColors ();

/* Returns a pointer to an array of the present colors. */
const CRGBA* PresetColors ();

/* Gets one of the rainbow colors. */
CRGBA ColorRainbow (ISC index);

/* Gets one of the preset colors. */
CRGBA ColorPreset (ISC index);

/* Gets a random preset colors. */
CRGBA RandomPresetColor ();

/* Gets a random color. */
CRGBA RandomColor (ISC index);
    
/* Mixes the color with the  */
CRGBA ColorMix (CRGBA a, CRGBA b);

/* Increases the alpha value of the given color by the given delta. */
CRGBA ChangeBrightness (CRGBA color, ISC delta);

/* Increases the alpha value of the given color by the given delta. */
CRGBA DecreaseBrightness (CRGBA color, ISC delta);

/* Creates a Color from the given RGB values. */
CRGBA ColorMake (IUA red, IUA green, IUA blue);

/* Creates a Color from the given RGBA values. */
CRGBA ColorMake (IUA red, IUA green, IUA blue, IUA alpha);

/* Gets the red value. */
IUA ColorGetRed (CRGBA color);

/* Sets the red value. */
void ColorSetRed (CRGBA color, IUA value);

/* Gets the green value. */
IUA ColorGetGreen (CRGBA color);

/* Sets the green value. */
void ColorSetGreen (CRGBA color, IUA value);

/* Gets the blue value. */
IUA ColorGetBlue (CRGBA color);

/* Sets the blue value. */
void ColorSetBlue (CRGBA color, IUA value);

/* Gets the alpha value. */
IUA ColorGetAlpha (CRGBA color);

/* Sets the alpha value. */
void ColorSetAlpha (CRGBA color, IUA value);

/* Converts this color to HSV. */
void ColorToHSV (CRGBA color, FPC& fR, FPC& fG, FPC fB,
                 FPC& fH, FPC& fS, FPC& fV);

/* Sets this color to the HSV values. */
void ColorSetHSV (CRGBA color, FPC& fR, FPC& fG, FPC& fB,
                  FPC& fH, FPC& fS, FPC& fV);

} //< namespace _
#endif
#endif
