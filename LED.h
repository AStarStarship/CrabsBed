// Copyright AStarship <https://astarship.net>.
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_LEDS
#ifndef CRABS_BED_LEDS_H
#define CRABS_BED_LEDS_H

#include "Color.h"

namespace _ {

enum {
  kBitToByteShift = 3,   //< Shift to turn a bit offset into a byte offset.
  kBitNumberMask  = 0x07,  //< Mask for the in-byte bit number.
};

/* Turns the given LED on.
@param spi_out_bytes The SPI shift register output bytes.
@param bit_number The bit offset of the LED. */
inline void TurnLedOn(IUA* spi_out_bytes, IUC bit_number) {
  spi_out_bytes[bit_number >> kBitToByteShift] |=
      (IUA)(1 << (bit_number & kBitNumberMask));
}

/* Turns the given LED off.
@param spi_out_bytes The SPI shift register output bytes.
@param bit_number The bit offset of the LED. */
inline void TurnLedOff(IUA* spi_out_bytes, IUC bit_number) {
  spi_out_bytes[bit_number >> kBitToByteShift] &=
      ~(IUA)(1 << (bit_number & kBitNumberMask));
}

/* Toggles the LED on and off.
@param spi_out_bytes The SPI shift register output bytes.
@param bit_number The bit offset of the LED. */
inline void ToggleLed(IUA* spi_out_bytes, IUC bit_number) {
  spi_out_bytes[bit_number >> kBitToByteShift] ^=
      (IUA)(1 << (bit_number & kBitNumberMask));
}

/* Gets the state of the LED.
@param spi_out_bytes The SPI shift register output bytes.
@param bit_number The bit offset of the LED. */
inline BOL GetLedState(const IUA* spi_out_bytes, IUC bit_number) {
  return (spi_out_bytes[bit_number >> kBitToByteShift] &
          (IUA)(1 << (bit_number & kBitNumberMask))) != 0;
}

/* Sets the state of the LED.
@param spi_out_bytes The SPI shift register output bytes.
@param bit_number The bit offset of the LED.
@param state The new state. */
inline void SetLedState(IUA* spi_out_bytes, IUC bit_number, BOL state) {
  if (state) {
    TurnLedOn(spi_out_bytes, bit_number);
    return;
  }
  TurnLedOff(spi_out_bytes, bit_number);
}

/* An LED stored as a bit offset.
Storing only the bit number and calculating the mask and byte index on the
fly isn't much more computationally expensive, and it saves RAM on 8 and 16
bit MCUs. */
class Led {
 public:
  /* Simple default constructor stores the LED bit number and row number.
  @param bit The offset in bits from LEDs[0].
  @param row The row number bit. */
  Led(IUC bit, IUC row) : bit_number_(bit), row_number_(row) {}

  /* Prints this object to a terminal. */
  void Print(const CHA* label = NILP);

 private:
  IUC bit_number_,  //< The offset in bits from LEDs[0].
      row_number_;  //< The row number bit.
};

}  //< namespace _
#endif
#endif
