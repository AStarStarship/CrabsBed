/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /rotary_knob.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_SENSORS_ROTARYENCODER
#define KABUKI_TEK_SENSORS_ROTARYENCODER 1

namespace _ {

class Controller;  //< Mutual dependency.

/* A 2-bit gray-code rotary encoder. */
class RotaryKnob {
 public:
  /* Constructor a rotary encoder with the given input channels. */
  RotaryKnob(ch_t channel, offset_t a, offset_t b);

  /* Gets the acceleration multiplier. */
  inline ISB GetAccelerationMultiplier(ISC time);

  /* Gets non-zero if there is change in the rotary encoder state.
  @return Gets 0 if there is not change, l if the knob turned right,
  and -1 if the knob turned left. */
  inline void Poll(Controller* controller, offset_t channel, IUA* debounced_xor,
                   ISC microseconds);

  /* Script Operations. */
  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  ch_t channel_;        //< Mixer channel.
  offset_t in_a_,       //< Encoder pin A offset.
      in_b_;            //< Encoder pin B offset.
  IUA curve_number_;    //< Acceleration curve number.
  ISC last_move_time_;  //< Last time the encoder moved.
};

class RotaryEncoderOp : public _::Operand {
 public:
  /* Constructs a RotaryEncoder Operation. */
  RotaryEncoderOp(RotaryKnob* object);

  /* Script operations. */
  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  RotaryKnob* object_;  //< The RotaryEncoderBank.
};
}  // namespace _
#endif
