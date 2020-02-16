/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /dmx_animation.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_DMX_ANIMATION
#define KABUKI_TEK_DMX_ANIMATION 1

namespace _ {

/*< @fn    UpdateHandler  (IUC, IUC, IUA);
@brief C function Update handler for DMXAnimation.
@code
IUC ExampleAnimation1  (num_channels, num_chases, num_variants);
@endcode */
typedef void (*UpdateHandler)(IUC Chase, IUC Frame, IUA Scene);

// inline BOL IsInvalidFrame  (IUC Index);

/* A simple DMX animation with variant.

*/
class DmxAnimation {
 public:
  enum {
    FPS = 30  //< The target frames per second.
  };

  /* Simple default constructor. */
  DmxAnimation(IUC num_channels, IUC num_chases, IUC num_variants);

  /* Resets the animation to the first frame */
  void ResetAnimation();

  /* Sets the currentChase to the given Index. */
  void SetChaseNumber(IUC Index);

  /* Function sends out DMX data for the given channel. */
  void SetChannelData(IUB Channel, IUA value);

  /* Function sets an RGB color starting at the given channel. */
  void SetRGBColor(IUB Channel, CRGBA value);

  /* Randomizes the currentVariant */
  void RandomizeVariant();

  void SendScene();
  void SetChase(IUA chaseNumber);
  void RandomizeSceneVariant();
  void SetColor(IUB channel, IUA red, IUA green, IUA blue);
  void SetColor(IUB channel, CRGBA color);
  void SetAllColors(CRGBA color);
  CRGBA IncreaseBrightness(CRGBA color, IUA brightness_change);
  CRGBA DecreaseBrightness(CRGBA color, IUA brightness_change);

 protected:
  IUA param1_,                //< Animation parameter 1/Red.
      param2_,                //< Animation parameter 2/Green.
      param3_,                //< Animation parameter 3/Blue.
      param4_;                //< Animation parameter 4/White.
  IUC current_chase_,         //< Current chase number.
      current_chase_length_,  //< Length of the current chase.
      current_variant_,       //< Current variant.
      channel_count_,         //< The number of DMX channels.
      num_chases_,            //< The number of DMX chases.
      num_variants_;          //< The number of variations of the animation.
  IUA* data_;                 //< Pointer to the DMX data for the current scene.
};
}  // namespace _
#endif
