// Copyright AStarship.

#include "led.h"

namespace _ {

inline void TurnLedOn(IUA* spiOutBytes, offset_t bit_number) {
  offset_t bit = bit_number;
  spiOutBytes[bit >> kBitToByteShift] |= (1 << (bit & kBitNumberMask));
}

inline void TurnLedOff(IUA* spiOutBytes, offset_t bit_number) {
  offset_t bit = bit_number;
  spiOutBytes[bit >> kBitToByteShift] &= ~(1 << (bit & kBitNumberMask));
}

inline void ToggleLed(IUA* spiOutBytes, offset_t bit_number_) {
  offset_t bit = bit_number_;
  IUA* pointerToByte = spiOutBytes + (bit >> kBitToByteShift);
  IUA IUA = *pointerToByte, mask = 1 << (bit & (bit & kBitNumberMask));
  if (IUA == 0) {
    *pointerToByte = IUA | mask;
    return;
  }
  *pointerToByte = IUA & ~mask;
}

inline BOL GetLedState(IUA* spiOutBytes, offset_t offset) {
  return spiOutBytes[offset >> kBitToByteShift] &
         (1 << (offset & kBitNumberMask));
}

inline void SetLedState(IUA* spiOutBytes, offset_t bit_number_, BOL state) {
  offset_t temp = bit_number_;
  IUA mask = (IUA)(1 << (temp & kBitNumberMask));
  if (state) {
    spiOutBytes[temp >> kBitToByteShift] |= mask;
    return;
  }
  spiOutBytes[temp >> 3] &= ~mask;
}

Led::Led(offset_t bit, offset_t row) : bit_number_(bit), row_number_(row) {
  /// ???
}

const Operation* Led::Star(ISW index, Crabs* crabs) {
  static const Operation This = {"LED", NumOperations(0), FirstOperation('A'),
                                 "tek", 0};

  switch (index) {
    case '?':
      return &This;
  }

  return nullptr;
}

LedOp::LedOp(Led* object) : object_(object) {
  // Nothing to do here!
}

const Operation* LedOp::Star(ISW index, Crabs* crabs) {
  object_->Star(index, crabs);
}

}  //< namespace _
