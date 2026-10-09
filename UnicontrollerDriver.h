// Copyright AStarship <https://astarship.net>.
//
// The Unicontroller firmware driver. This is the "one firmware" that runs on
// all three backends (Raspberry Pi, BeagleBone-AI, virtual breadboard). It
// takes a device interface, polls the inputs through the Debouncer, and
// emits a stream of MIDI bytes. The firmware doesn't know whether the device
// is a breadboard or real hardware — that's the seam.
//
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_MIDI
#ifndef CRABS_BED_UNICONTROLLER_DRIVER_H
#define CRABS_BED_UNICONTROLLER_DRIVER_H

#include "Midi.h"
#include "Debouncer.h"
#include "VirtualBreadboard.h"

namespace _ {

/* The Unicontroller firmware: polls a device, debounces, emits MIDI. */
class UnicontrollerDriver {
 public:
  enum {
    kMaxMidiOut = 256,
  };

  /* Constructs a driver for a device with the given number of buttons.
  The buttons live in the device's SPI input chain (the 74HC165 side). */
  UnicontrollerDriver(VirtualBreadboard& device, IUC num_buttons)
      : device_(device),
        num_buttons_(num_buttons),
        midi_out_(new IUA[kMaxMidiOut]),
        midi_count_(0),
        button_state_(new IUA[num_buttons / 8 + 1]),
        button_debouncer_(button_state_) {
    for (IUC i = 0; i < num_buttons_ / 8 + 1; ++i) button_state_[i] = 0;
  }

  /* Polls the device once: reads the button inputs, debounces them, and
  emits any resulting MIDI note-on/off messages into the MIDI out buffer.
  @return The number of MIDI bytes emitted this poll. */
  IUC Poll() {
    midi_count_ = 0;
    // Read the raw button byte from the SPI input chain (byte 0).
    IUA raw = device_.spi().in_bytes()[0];
    // Debounce it. The debouncer returns the XOR of changed bits.
    IUA changed = button_debouncer_.Debounce(raw);
    // For each changed bit, emit a note-on (if now pressed) or note-off
    // (if now released).
    for (IUC bit = 0; bit < num_buttons_; ++bit) {
      IUC byte_index = bit >> 3;
      IUC bit_mask = 1 << (bit & 7);
      BOL now_pressed = (raw & (IUA)bit_mask) != 0;
      if (changed & (IUA)bit_mask) {
        IUC i = midi_count_;
        if (now_pressed) {
          midi_count_ = MidiNoteOn(midi_out_, &i, 0, (IUA)bit, 100);
        } else {
          midi_count_ = MidiNoteOff(midi_out_, &i, 0, (IUA)bit, 0);
        }
      }
    }
    return midi_count_;
  }

  /* Returns a pointer to the MIDI bytes emitted by the last Poll(). */
  const IUA* midi_out() const { return midi_out_; }

  /* How many MIDI bytes were emitted by the last Poll(). */
  IUC midi_count() const { return midi_count_; }

 private:
  VirtualBreadboard& device_;
  IUC num_buttons_;
  IUA* midi_out_;
  IUC midi_count_;
  IUA* button_state_;
  Debouncer<IUA> button_debouncer_;
};

}  //< namespace _
#endif
#endif
