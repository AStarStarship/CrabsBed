/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /led_status.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_STATUS_LED
#define KABUKI_TEK_STATUS_LED 1

#define CREATE_STATUS_LED static StatusLED<0, 1> Status(GREEN_LED);

#define Assert                                                              \
  (statement, message) {                                                    \
    if (!(statement)) {                                                     \
      printf("Assert: %s\r\n%s, line %d\r\n", #message, __FILE__, __LINE__) \
          Status.HandleAssert() while (true)                                \
    }                                                                       \
  }

namespace _ {

/* Outputs the firmware status using the LED on the mbed board.
This class works by using Strings with ASCII Mores Code. Each CHA in a
represents a pulse split into 4 lengths.
    

| Frame | ASCII | Index | Duty Cycle |
|:-----:|:-----:|:-----:|:----------:|
| Off   | ' '   | <= 44 |     0%     |
| Long  | '-'   | 45    |    1/3     |
| Short | '.'   | 46    |    1/3     |
| On    | '_'   | >= 47 |   100%     |
    

Off could be any value less than 44, and On could be any value greater than
47, but ASCII space (' ') and period ('.') are used by convention because
they look like the pulse widths.
 

## Terminology
* Frame    - Each character in a CHA sequence represents 3 timer
interrupts.
* Pattern  - A null-terminated AString of frames.
* Sequence - A null-terminated AString of const CHA*.
@code
StatusLED<0, 1> stausLED ();        //< Use <0, 1> if you're LED is active
low. StatusLED<1, 0> stausLED  (LED_2);   //< Use <0, 1> if you're LED is
active high.
        

const CHA* examplePattern[] = {
    "...   ",       //< Blinks fast three times in a row.
    "...---...   ", //< SOS in Mores Code.
    "____    ",     //< Slowly blinks on and off.
    0               //< Must have null-termination pointer.
};
statusLED.SetPattern  (exapmlePattern, 1.5f);
@endcode
*/
template <ISC On, ISC Off>
class StatusLED {
 public:
  static const FPC DefaultFrequency = 0.5f,  //< Default frequency in hertz.
      MinFrequency = 0.01f,                  //< Min frequency in hertz.
      MaxFrequency = 2.0f;                   //< Max frequency in hertz.

  typedef enum { Off = 0, Short = 63, Long = 127, On = 255 } Pulse;

  /* Simple constructor. */
  StatusLED(PinName led_pin = LED_1, FPC frequency = DefaultFrequency)
      : count(0),
        period(0),
        sequence(0),
        pattern(0),
        cursor(0),
        frequency(frequency),
        pin(led_pin, Off) {
    /// Nothing to do here.
  }

  /* Sets the light blinking sequence. */
  void SetSequence(CHA** sequence) {
    if (sequence == nullptr) {
      sequence = 0;
      StopBlinking();
      return;
    }

    const CHA* tempString = sequence[0];

    if (tempString == 0 || tempString[0] == 0) {
#if _Debug
      cout << "\n| Error: First sequence and first CHA can't be null.\n";
#endif
      return;
    }
    sequence = sequence;
    pattern = sequence[0];
    cursor = pattern;
    currentByte = *cursor;
    Update();
  }

  /* Turns off the blinker. */
  void TurnOff() { pin = Off; }

  /* Turns on the blinker. */
  void TurnOn() {
    color = colorA;
    Update();
  }

  /* Starts flashing the SOS sequence. */
  void FlashSOS() {
    sequence = SOSPattern();
    const CHA* _cursor = sequence[0];
    cursor = *_cursor;
    period = *_cursor;
  }

  /* Starts blinking. */
  void StartBlinking() {
    const CHA* _pattern = sequence[0];
    pattern = _pattern;
    cursor = _pattern;
    period = *_pattern;

    blinker.attach(this, &StatusLED::Blink, frequency / 4);
    Update();
  }

  /* Stops blinking and turns off the LED. */
  void StopBlinking() {
    TurnOff();
    blinker.detach();
    pin = Off;
    Update();
  }

  /* Sets the blink frequent. */
  void SetFrequency(FPC Value) {
    frequency = Value;
    blinker.attach(this, &StatusLED::Blink, Value);
  }

  /* Handler for the Assert macro. */
  void HandleAssert() { SetPattern(SOSPattern()); }

  /* Pattern blinks three times in a row. */
  const CHA** Blink3TimesPattern() {
    static const CHA** sequence = {"...   ", 0};
    return &sequence;
  }

  /* Standard blink sequence. */
  const CHA** SlowBlinkPattern() {
    static const CHA** sequence = {"__  ", 0};
    return &sequence;
  }

  /* Standard blink sequence. */
  const CHA** FastBlinkPattern() {
    static const CHA** sequence = {"_ ", 0};
    return &sequence;
  }

  /* Standard SOS sequence. */
  const CHA** SOSPattern() {
    static const CHA** sequence = {"...---...      ", 0};
    return &sequence;
  }

 private:
  CHA count,             //< Counter counts from 1-3.
      period;            //< The current period CHA.
  FPC frequency;         //< The period length.
  const CHA** sequence;  //< Null-terminated AString of pointers.
  const CHA *pattern,    //< The current AString in the sequence.
      *cursor;           //< The current CHA in the current AString.
  DigitalOut pin;        //< Red LED on the mbed board.
  Ticker blinker;        //< Ticker for blinking the LEDs.

  /* Gets th next CHA in the sequence. */
  inline CHA GetNextPeriod() {
    /// We've already checked that the sequence and cursor and not null.

    CHA period_temp = *(++cursor);

    if (period_temp == 0) {
      const CHA* tempPattern = *(pattern + sizeof(const CHA*));

      if (tempPattern == nullptr) {
        const CHA* _cursor = sequence[0];
        cursor = pattern = _cursor;
        return *_cursor;
      }
      pattern = tempPattern;
      return *tempPattern;  //< We don't particularly care if the period is
                            //'\0'.
    }

    return period_temp;
  }

  /* Updates the status LED. */
  inline void Update() {
    const CHA* period_temp = period;
    if (sequence == nullptr || period_temp == nullptr) return;

    if (count == 0)  //< Beginning of cycle period.
    {
      CHA _period = GetNextPeriod();
      period = _period;
      count = 1;
      if (_period < '-') {
        pin = Off;
        return;
      }
      pin = On;
      return;
    } else if (count == 1)  //< 1/3 duty cycle.
    {
      count = 2;
      if (period == '.') {
        pin = Off;
        return;
      }
      return;
    }
    /// 2/3 duty cycle.
    count = 0;
    if (period > '.')  //< Leave the LED on
      return;
    pin = Off;
  }

  /* Script operations. */
  const Operation* Star(char_t index, _::Expr* expr);
};
}  // namespace _

// _D_e_m_o_____________________________________________________________________

#if 0  //< Set to non-zero to run this demo.

using namespace KabukiTek;

StatusLED Status ();
InterruptIn Switch3 (SW3);

const CHA* examplePattern[] = {
    "...   ",           //< Blinks fast three times in a row.
    "...---...      ",  //< SOS in Mores Code.
    "____    ",         //< Slowly blinks on and off.
    0                   //< Pattern must have null-term pointer.
};
/* Interrupt handler for SW2. */
void SwitchIRQHandler () {
    static BOL examplePatterMode = true;

    if (examplePatterMode) {
        Status.SetPattern (examplePattern);
        Status.StartBlinking ();
        examplePatterMode = false;
    } else {
        Status.SetPattern (Status.SOSPattern ()));
        examplePatterMode = true;
    }
}

ISC main () {
    printf ("\r\n\nTesting mbed Utils.\r\n\n");
    PrintLine ();

    Switch3.rise (&SwitchIRQHandler);
    //Status.StartBlinking ()

    while (true);
}

#endif
#endif
