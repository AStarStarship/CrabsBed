// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
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
  const _::Op* Star(ISW index, _::Crabs* crabs);

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
  virtual const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  RotaryKnob* object_;  //< The RotaryEncoderBank.
};
}  //< namespace _
#endif
