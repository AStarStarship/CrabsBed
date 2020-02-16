/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /dmx_animation.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "dmxanimation.h"

namespace _ {

DmxAnimation::DmxAnimation(IUC kChannelCount, IUC NumChases, IUC NumVariants)
    : param1_(0),
      param2_(0),
      param3_(0),
      param4_(0),
      current_chase_(0),
      current_chase_length_(0),
      current_variant_(0),
      channel_count_(kChannelCount),
      num_chases_(NumChases),
      num_variants_(NumVariants),
      data_(0) {
  // Nothing to do here.
}

void DmxAnimation::ResetAnimation() {}

void DmxAnimation::SetChaseNumber(IUC Index) {
  if (Index > num_chases_) return;

  current_chase_ = Index;
}

void DmxAnimation::SetChannelData(IUB channel, IUA data) {}

void DmxAnimation::SendScene() {
  // put  (scene, );
}

void DmxAnimation::SetChase(IUA chaseNumber) {}

void DmxAnimation::RandomizeSceneVariant() {}

void DmxAnimation::SetRGBColor(IUB channel, CRGBA color) {
  const IUB rGBChannelCutoff = 512 - 9;
  //< We need 9 bytes in our cue for this operation.

  if (channel > rGBChannelCutoff) {
    // There are not 9 channels to shoot this data out too!
    return;
  }

  // if  (sceneIndex >= sceneLength - 9) {
  // This should never happen in your animation code.
  // Emptyscene (); //< This pauses the animation to flush out the buffer.

  // The DMX protocol consist of a 9-bit channel, and an 8-bit data value.

  // Decode the channel into LSB and MSB.
  IUA channelLSB = (IUA)channel, channelMSb = (IUA)(channel & 0x100) >> 8;

  // The cue is a FIFO, so cue up the data, followed by the channel LSB, then
  // MSB.

  // The following is an unrolled loop for greater efficiency at runtime.

  IUA* tempByte = 0;  // scene[sceneIndex++];
  // Cue red value
  *tempByte = (IUA)color & 0xFF;
  *(++tempByte) = channelLSB;
  *(++tempByte) = channelMSb;

  if (channelLSB == 0xFF) {
    // If the LSB is about to max out to 255, then we need to increment the MSB.
    ++channelMSb;
    channelLSB = 0;
  } else
    ++channelLSB;

  // Cue green value
  *(++tempByte) = (IUA)(color & 0xFF00) >> 8;
  *(++tempByte) = channelLSB;
  *(++tempByte) = channelMSb;

  if (channelLSB == 0xFF) {
    // If the LSB is about to max out to 255, then we need to increment the MSB.
    ++channelMSb;
    channelLSB = 0;
  } else
    ++channelLSB;

  // Cue blue value
  *(++tempByte) = (IUA)(color & 0xFF0000) >> 16;
  *(++tempByte) = channelLSB;
  *(++tempByte) = channelMSb;
}

void DmxAnimation::SetColor(IUB channel, IUA Red, IUA Green, IUA Blue) {
  if (channel > 511 - 3) {
    // We need 3 channels for an RGB color.
    printf("Error in SetColor  (IUB, CRGBA): channel out of range!\r\n");
    return;
  }

  data_[channel] = Red;
  data_[channel + 1] = Green;
  data_[channel + 2] = Blue;
}

void DmxAnimation::SetColor(IUB channel, CRGBA color) {
  if (channel > 511 - 3) {
    // We need 3 channels for an RGB color.
    printf("Error in SetColor  (IUB, CRGBA): channel out of range!\r\n");
    return;
  }

  data_[channel] = (IUA)(color & 0xFF0000) >> 16;   //< Red
  data_[channel + 1] = (IUA)(color & 0xFF00) >> 8;  //< Green
  data_[channel + 2] = (IUA)(color & 0xFF);         //< Blue
}

/*
void DmxAnimation::SetColor  (IUB channel, CRGBA color)
{
    if  (channel > 511 - 3)             //< We need 3 channels for an RGB color.
    {
        printf ("Error in SetColor  (IUB, CRGBA): channel out of range!\r\n");
        return;
    }
    FPC alphaValue =  (FPC) ((color & 0xFF000000) >> 24),
    Red     =  (FPC) ((color & 0xFF0000) >> 16),
    Green   =  (FPC) ((color & 0xFF00) >> 8),
    Blue    =  (FPC)  (color & 0xFF);

    data[channel    ] =  (IUA)  (Red   * alphaValue);    //< Red
    data[channel + 1] =  (IUA)  (Green * alphaValue);    //< Green
    data[channel + 2] =  (IUA)  (Blue  * alphaValue);    //< Blue
}

void DmxAnimation::SetAllColors  (CRGBA color)
{
    for  (ISC i = 0; i < numBasePairs; ++i)
    {
        SetColor  (nucleobaseB[i], color);
        SetColor  (nucleobaseT[i], color);
    }

    for  (ISC i = 0; i < numBasePairs; ++i)
    {
        SetColor  (backboneB[i], color);
        SetColor  (backboneT[i], color);
    }
}
*/

void DmxAnimation::SetAllColors(CRGBA color) {
  /*
  for  (ISC i = 0; i < numChannels; ++i)
  {
  SetColor  (nucleobaseB[i], color);
  SetColor  (nucleobaseT[i], color);
  }

  for  (ISC i = 0; i < numBasePairs; ++i)
  {
  SetColor  (backboneB[i], color);
  SetColor  (backboneT[i], color);
  }
  */
}

CRGBA DmxAnimation::IncreaseBrightness(CRGBA color, IUA brightness_change) {
  IUC brightness = (color & 0xFF000000) >> 24;
  //< Mask off MSB and shift into LSB.
  color = (color & 0x00FFFFFF);
  //< Clear out the alpha Channel
  brightness = (brightness + brightness_change) << 24;
  //< Add the brightness_change and shift back  (overflow ignored).
  // printf ("Increasing brightness to %hhu.\n", brightness);
  cout << "\n| Increasing brightness to " << brightness << '.';
  return color & brightness;
}

CRGBA DmxAnimation::DecreaseBrightness(CRGBA color, IUA brightness_change) {
  IUC brightness = (color & 0xFF000000) >> 24;
  //< Mask off MSB and shift into LSB.
  color = (color & 0x00FFFFFF);
  //< Clear out the alpha Channel
  brightness = (brightness - brightness_change) >> 24;
  //< Subtract the brightness_change and shift back  (underflow ignored).
  cout << "\n| Decreasing brightness to " << brightness << '.';
  return color & brightness;
}

void DmxAnimation::RandomizeVariant() {
  srand(time(0));
  current_variant_ = (IUA)rand() % 256;
}

}  // namespace _
