// Copyright AStarship <https://astarship.net>.

#pragma once
#ifndef KABUKI_TEK_POT
#define KABUKI_TEK_POT 1

namespace _ {

/* A potentiometer.
  

@code
Pot<ISB> pot
@endcode
*/
class KABUKI Pot {
 public:
  /* Constructs a pot from the given ADC pin and assigned channel number. */
  Pot(ch_t channel, PinName adc_pin);

  /* Polls the pot. */
  inline void Poll(IUB new_value, _::Crabs* crabs, IUB value, IUB min_value,
                   IUB max_channel);

  /* Script operations. */
  const _::Op* Star(ISW index, _::Crabs* crabs);

  /* Prints this object to a terminal. */
  void Print(_::Log& log);

 private:
  ch_t channel_;  //< Mixer channel number.
  AnalogIn ain_;  //< Pot ADC input.
};                //< class Pot

class PotOp : public _::Operand {
 public:
  /* Constructs a Pot Operation. */
  PotOp(Pot* object);

  /* Script operations. */
  virtual const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  Pot* object_;  //< The Pot.
};               //< class PotOp
}  //< namespace _
#endif
