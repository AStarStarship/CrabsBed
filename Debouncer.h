// Copyright AStarship <https://astarship.net>.
//
// Dr Marty's switch debounce algorithm for shift registers and GPIO pins.
// In order to use this class, simply feed the constructor the address of the
// memory you want to store the debounced data in. This allows the debounced
// General Purpose Inputs (GPI) and shift register inputs to be packed into
// a single array of bytes so they can be quickly polled.
//
// Be sure to memory align your variables: 5 bytes of state on a 32-bit MCU
// needs a 32-bit-aligned base.
//
// @code
// // 100Hz polling example with one 74HC165 shift register and a GPI port.
//
// TStack<IUA> SpiOut;           // SPI shift register output bytes.
// TStack<IUA> SpiIn;            // SPI shift register input bytes.
// IUA gpi_port;                 // GPI port latched by the poll loop.
//
// IUA input_states[5];
// Debouncer<ISC> gpi_port_debouncer ((ISC*)&input_states[0]);
// Debouncer<IUA> shift_debouncer    (&input_states[4]);
//
// void PollInputsHandler () {
//   IUA cs = 1;
//   IUA shift = shift_debouncer.Debounce (SpiIn.count);
//   ISC port  = gpi_port_debouncer.Debounce (gpi_port);
//   cs = 0;
// }
// @endcode
//
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_DEBOUNCER
#ifndef CRABS_BED_SENSORS_DEBOUNCER
#define CRABS_BED_SENSORS_DEBOUNCER

namespace _ {

template <typename T>
class Debouncer {
 public:
  /* Constructor.
  @param state_address Memory to store the debounced state in. */
  Debouncer(T* state_address)
      : one_(0), two_(0), three_(0), state_(state_address) {}

  /* Debounces the input and returns an XOR of changes.
  Using an XOR of the previous state shows you which button states
  have changed. */
  inline T Debounce(T sample) {
    T one = one_, two = two_, three = three_;
    T* state = state_;
    T previous_state = *state,
      current_state =
          previous_state & (one | two | three) | (one & two & three);
    *state = current_state;
    three_ = two;
    two_ = one;
    one_ = sample;
    return previous_state ^ current_state;
  }

 private:
  T one_,      //< Sample t - 1.
      two_,    //< Sample t - 2.
      three_;  //< Sample t - 3.
  T* state_;   //< Pointer to the state.
};
}  //< namespace _
#endif
#endif
