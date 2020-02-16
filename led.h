/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /led.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK
#define KABUKI_TEK 1

namespace _ {

/* Turns the given LED on. */
inline void TurnLedOn(IUA* spi_out_bytes, offset_t bit_number);

/* Turns the given LED off. */
inline void TurnLedOff(IUA* spi_out_bytes, offset_t bit_number);

/* Gets the state of the LED. */
inline BOL GetLedState(IUA* digial_outs, offset_t bit_number);

/* Sets the state of the LED. */
inline void SetLedState(IUA* digial_outs, offset_t bit_number, BOL state);

/* Toggles the LED on and off. */
inline void ToggleLed(IUA* digial_outs, offset_t bit_number);

/* An LED stored as a bit offset.
Storing only the bit number and calculating the mask and IUA number isn't
much more computationally expensive. Its better to save on RAM for 8 and 16
bit MCUs.
*/
class Led {
 public:
  /* Simple default constructor stores the LED bit number and row number. */
  Led(offset_t bit, offset_t row);

  /* Prints this object to a terminal. */
  inline void Print(_::Expr& slot);

  /* Script Operations. */
  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  offset_t bit_number_,  //< The offset in bits from LEDs[0].
      row_number_;       //< The row number bit.
};

class LedOp : public _::Operand {
 public:
  /* Constructs a Led Operation. */
  LedOp(Led* object);

  /* Script operations. */
  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  Led* object_;  //< The Led.
};               //< class LedOp
}  // namespace _
#endif
