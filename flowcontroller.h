/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /flow_controller.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_FLOW_CONTROLLER
#define KABUKI_TEK_FLOW_CONTROLLER 1

namespace _ {

/* Converts gallows to milliliters. */
IUC ConvertGallonsToMilliiters(FPC value);

/* Converts milliliters to gallons. */
FPC ConvertMilliitersToGallons(IUC value);

class FlowController {
 public:
  /* Constructs a smart waterer. */
  FlowController(PinName sensor_pin, PinName solenoid_pin, PinName pot_pin,
                 IUC max_flow_ml);

  /* StartWaterings to the beginning of the watering cycle. */
  void StartWatering(ISC index);

  /* Increments the flow rate sensor pulse counter. */
  void PulseFlowSensor();

  /* Prints the state of object to the debug stream. */
  void Print(ISC index);

  /* Prints the state of object when done watering to the debug stream. */
  inline void StopWatering(ISC index);

  /* Polls the pot and updates the target flow. */
  void UpdateTargetFlow();

  /* Updates the FPC rate. */
  void Update(ISC index);

  /* Opens the solenoid valve. */
  void OpenValve();

  /* Closes the solenoid valve. */
  void CloseValve();

  /* Script operations. */
  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  InterruptIn sensor_;  //< Flow sensor pin.
  DigitalOut valve_;    //< Solenoid valve pin.
  AnalogIn pot_;        //< Potentiometer pin.
  volatile IUB count_;  //< Flow sensor pulse count_.
  IUB flow_rate_ml_;    //< Flow rate in milliliters.
  IUC total_flow_ml_,   //< Total flow in mL.
      target_flow_ml_,  //< Target flow in mL per cycle.
      max_flow_ml_;     //< Maximum target flow in mL per cycle.
  IUB last_sample_;     //< Last pot value read.
};

class FlowControllerOp : public _::Operand {
 public:
  /* Constructs a smart waterer. */
  FlowControllerOp(FlowController* flow_co);

  /* Script operations. */
  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  FlowController* flow_co_;  //< The FlowController.
};
}  // namespace _
#endif
