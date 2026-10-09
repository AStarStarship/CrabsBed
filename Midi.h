// Copyright AStarship <https://astarship.net>.
//
// The MIDI protocol layer for the Unicontroller. Pure logic: it encodes
// controller events (debounced button edges, rotary-knob deltas, pot values)
// into 7-bit MIDI bytes. No hardware, no mbed — headless-testable on a host.
//
// Channel/data encoding follows the Unicontroller contract (see
// Unicontroller.h "14 and 16-bit Values"): 14-bit values are split into two
// 7-bit nibbles (LSB first, then MSB), and channels 0..31 map to MIDI
// channels 32..63 (the upper half of the 64 MIDI channels).
//
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_MIDI
#ifndef CRABS_BED_MIDI_H
#define CRABS_BED_MIDI_H

namespace _ {

// One MIDI byte: a 7-bit value stored in an IUA.
typedef IUA MidiByte;

// MIDI channel is 0..15 (4 bits). The Unicontroller maps its own 0..31
// channel space onto the upper half, 32..63, per the contract.
typedef IUC MidiChannel;

/* Maximum value of a 14-bit mixer sample (2^14 - 1). */
constexpr IUD MidiValueMax = 16383;

/* Number of MIDI channels in the Unicontroller's 0..31 space. */
constexpr IUC MidiChannelCount = 32;

/* The MIDI channel number a Unicontroller channel maps to (0..31 -> 32..63). */
constexpr MidiChannel MidiChannelMap(MidiChannel channel) {
  return (MidiChannel)(channel + 32);
}

/* Channel message types (the low 4 bits of a status byte). */
enum MidiMsg {
  MsgNoteOff = 0x8,  //< 1000
  MsgNoteOn  = 0x9,  //< 1001
  MsgPoly    = 0xA,  //< 1010 (polyphonic key pressure)
  MsgCC      = 0xB,  //< 1011 (control change)
  MsgProgram = 0xC,  //< 1100 (program change, 1 data byte)
  MsgChPress = 0xD,  //< 1101 (channel pressure, 1 data byte)
  MsgPitch   = 0xE,  //< 1110 (pitch bend, 14-bit LSB/MSB)
};

/* Standard control-change numbers used by the Unicontroller. */
enum MidiCC {
  CCModulationX = 0x00,  //< Modulation wheel.
  CCDataSrc     = 0x06,  //< Data source select.
  CCMainVolume  = 0x07,  //< Main volume.
  CCDataInc     = 0x20,  //< Data increment (knob right).
  CCDataDec     = 0x21,  //< Data decrement (knob left).
  CCBankInc     = 0x23,  //< Bank increment (encoder, coarse).
  CCBankDec     = 0x24,  //< Bank decrement (encoder, fine).
};

/* Builds a channel status byte from a message type and a Unicontroller
channel (0..31). The channel is mapped to 32..63 per the contract. */
MidiByte MidiStatus(MidiMsg msg, MidiChannel channel);

/* Builds a program-change status byte (no channel+msg prefix beyond PC). */
MidiByte MidiProgramStatus(MidiChannel channel);

/* Splits a 14-bit value into its low 7 bits (LSB first). */
MidiByte MidiLSB(IUD value);

/* Splits a 14-bit value into its upper 7 bits (MSB second). */
MidiByte MidiMSB(IUD value);

/* Encodes a note-on for the given channel, note (0..127), and velocity.
Appends the 3 bytes (status, note, velocity) to out and advances *count.
@param out     The output byte buffer (capacity >= 3 from *count).
@param count   In: the write cursor. Out: cursor + 3.
@param channel The Unicontroller channel (0..31).
@param note    MIDI note number 0..127.
@param velocity 0..127; 0 is a note-off on many devices. */
IUC MidiNoteOn(IUA* out, IUC* count, MidiChannel channel, IUA note,
              IUA velocity);

/* Encodes a note-off. */
IUC MidiNoteOff(IUA* out, IUC* count, MidiChannel channel, IUA note,
               IUA velocity);

/* Encodes a two-byte control change. */
IUC MidiCC(IUA* out, IUC* count, MidiChannel channel, IUA cc, IUA value);

/* Encodes a 14-bit value as a two-byte CC (LSB then MSB). Used for pots and
the Unicontroller's 14-bit mixer values.
@param cc_lsb The CC number for the low byte.
@param cc_msb The CC number for the high byte (typically cc_lsb + 32). */
IUC MidiCC14(IUA* out, IUC* count, MidiChannel channel, IUD value, IUA cc_lsb,
            IUA cc_msb);

/* Encodes a 14-bit pitch bend (LSB then MSB). */
IUC MidiPitchBend(IUA* out, IUC* count, MidiChannel channel, IUD value14);

/* The number of bytes a MIDI message of the given type occupies. */
IUC MidiMsgBytes(MidiMsg msg);

}  //< namespace _
#endif
#endif
