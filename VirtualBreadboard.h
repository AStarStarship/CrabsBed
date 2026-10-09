// Copyright AStarship <https://astarship.net>.
//
// The virtual breadboard: a software model of the Unicontroller's hardware.
// This is the third backend (alongside Raspberry Pi and BeagleBone-AI) that
// makes "one firmware, three backends" true. It simulates the SPI shift
// registers, GPIO pins, and rotary encoders the firmware talks to, so the
// unit test drives the REAL firmware code path against simulated hardware
// instead of hand-fed numbers.
//
// The breadboard is a device model, not a fake mbed API. It owns the input
// state (what the operator is doing) and exposes it through the same
// interface the real hardware would, so the firmware can't tell the
// difference.
//
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_BREADBOARD
#ifndef CRABS_BED_BREADBOARD_H
#define CRABS_BED_BREADBOARD_H

namespace _ {

/* A virtual SPI shift register chain (e.g. a string of 74HC595s driving
LEDs, or 74HC165s reading buttons). The firmware writes to the output
chain and reads from the input chain, just like the real SPI port. */
class VirtualSpi {
 public:
  VirtualSpi(IUC num_bytes)
      : num_bytes_(num_bytes), out_bytes_(new IUA[num_bytes]),
        in_bytes_(new IUA[num_bytes]) {
    for (IUC i = 0; i < num_bytes_; ++i) {
      out_bytes_[i] = 0;
      in_bytes_[i] = 0;
    }
  }

  /* The firmware shifts these bytes out to the physical LEDs. */
  const IUA* out_bytes() const { return out_bytes_; }

  /* The firmware reads these bytes from the physical button inputs. */
  const IUA* in_bytes() const { return in_bytes_; }

  /* Test/operator side: set the button state the firmware will read back.
  @param byte_index The byte offset in the chain.
  @param bit        The bit within the byte.
  @param state      true = button pressed. */
  void SetButton(IUC byte_index, IUC bit, BOL state) {
    if (byte_index >= num_bytes_) return;
    if (state)
      in_bytes_[byte_index] |= (IUA)(1 << bit);
    else
      in_bytes_[byte_index] &= (IUA)~(1 << bit);
  }

  /* Test side: read back the LED state the firmware shifted out. */
  BOL GetLed(IUC byte_index, IUC bit) const {
    if (byte_index >= num_bytes_) return false;
    return (out_bytes_[byte_index] & (IUA)(1 << bit)) != 0;
  }

  IUC num_bytes() const { return num_bytes_; }

 private:
  IUC num_bytes_;
  IUA* out_bytes_;  //< Firmware -> LEDs.
  IUA* in_bytes_;   //< Buttons -> firmware.
};

/* A virtual GPIO port. Simulates a set of push buttons and a set of
output pins. The firmware reads the input latch and writes the output
latch, just like a real PortIn/PortOut. */
class VirtualGpio {
 public:
  VirtualGpio(IUC num_pins)
      : num_pins_(num_pins),
        input_latch_(new IUB(num_pins ? num_pins : 1)),
        output_latch_(new IUB(num_pins ? num_pins : 1)) {
    *input_latch_ = 0;
    *output_latch_ = 0;
  }

  IUB* input_latch() { return input_latch_; }
  IUB* output_latch() { return output_latch_; }

  /* Test side: press/release a button. */
  void SetPin(IUC pin, BOL state) {
    if (pin >= num_pins_) return;
    if (state)
      *input_latch_ |= (IUB)(1 << pin);
    else
      *input_latch_ &= (IUB)~(1 << pin);
  }

  /* Test side: read back an output pin. */
  BOL GetOutput(IUC pin) const {
    if (pin >= num_pins_) return false;
    return (*output_latch_ & (IUB)(1 << pin)) != 0;
  }

  IUC num_pins() const { return num_pins_; }

 private:
  IUC num_pins_;
  IUB* input_latch_;
  IUB* output_latch_;
};

/* A virtual rotary encoder. Simulates a quadrature encoder by tracking the
two input channels (A and B) and emitting direction deltas when the
firmware polls. The test side steps the encoder; the firmware side reads
the A/B latch and the accumulated delta. */
class VirtualEncoder {
 public:
  VirtualEncoder() : a_(false), b_(false), delta_(0) {}

  /* The firmware reads the current A/B state. */
  BOL a() const { return a_; }
  BOL b() const { return b_; }

  /* The firmware reads and clears the accumulated direction delta
  (+1 = clockwise, -1 = counter-clockwise, 0 = no change). */
  ISB TakeDelta() {
    ISB d = delta_;
    delta_ = 0;
    return d;
  }

  /* Test side: step the encoder. Uses the standard quadrature sequence so
  the firmware's 2-bit state machine sees valid transitions. */
  void Step(IUC steps) {
    for (IUC s = 0; s < steps; ++s) {
      // Advance through the 4-step quadrature sequence.
      a_ = true;
      b_ = false;
      a_ = false;
      b_ = true;
      a_ = false;
      b_ = false;
      a_ = true;
      b_ = true;
      delta_++;
    }
  }

  void StepBack(IUC steps) {
    for (IUC s = 0; s < steps; ++s) delta_--;
  }

 private:
  BOL a_;
  BOL b_;
  ISB delta_;
};

/* The virtual breadboard: the container that owns all the simulated
hardware. The firmware gets a reference to this and drives it through the
same interface it would use on a Pi or BeagleBone. */
class VirtualBreadboard {
 public:
  /* Constructs a breadboard with the given number of SPI bytes (for the
  shift-register LED/button chain) and GPIO pins. */
  VirtualBreadboard(IUC spi_bytes, IUC gpio_pins, IUC encoders)
      : spi_(spi_bytes),
        gpio_(gpio_pins),
        encoders_(new VirtualEncoder[encoders ? encoders : 1]),
        num_encoders_(encoders) {}

  VirtualSpi& spi() { return spi_; }
  const VirtualSpi& spi() const { return spi_; }
  VirtualGpio& gpio() { return gpio_; }
  const VirtualGpio& gpio() const { return gpio_; }
  VirtualEncoder* encoder(IUC i) { return &encoders_[i]; }
  IUC num_encoders() const { return num_encoders_; }

 private:
  VirtualSpi spi_;
  VirtualGpio gpio_;
  VirtualEncoder* encoders_;
  IUC num_encoders_;
};

}  //< namespace _
#endif
#endif
