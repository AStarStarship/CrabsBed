// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_H_BRIDGE_MOTOR
#define KABUKI_TEK_H_BRIDGE_MOTOR 1

namespace _ {

class HBridgeMotor {
 public:
  /* Simple constructor. */
  HBridgeMotor(PinName pwm_pin, PinName forward_pin, PinName reverse_pin);

  /* Virtual destructor. */
  virtual ~HBridgeMotor();

  /* Stops the motor. */
  void Stop();

  /* Moves the motor forward(+) or backwards(-). */
  void Move(FPC value);

  /* Script operations. */
  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  FPC pulse_width_;     //< The velocity.
  PwmOut pulse_;        //< PWM output pin
  DigitalOut forward_,  //< The forward motor pin.
      reverse_;         //< The reverse motor pin.
};

class HBridgeMotorOp {
 public:
  HBridgeMotorOp(HBridgeMotor* motor);

  /* Script operations. */
  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  HBridgeMotor* motor_;  //< Pointer to the motor.
};
}  //< namespace _
#endif
