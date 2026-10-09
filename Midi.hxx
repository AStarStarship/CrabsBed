// Copyright AStarship <https://astarship.net>.
#pragma once
#include <_Config.h>
#if SEAM >= CRABS_BED_MIDI
#include "Midi.h"

namespace _ {

MidiByte MidiStatus(MidiMsg msg, MidiChannel channel) {
  // MIDI status is 8 bits: (msg << 4) | (midi_channel & 0x0F). The
  // Unicontroller's 0..31 channel space maps to MIDI channel 0..15 by
  // taking the low 4 bits (the "32..63" in the contract is the mixer
  // channel number, which wraps modulo 16 in the status byte).
  MidiChannel midi_channel = MidiChannelMap(channel) & 0x0F;
  return (MidiByte)(((IUA)msg << 4) | (IUA)midi_channel);
}

MidiByte MidiProgramStatus(MidiChannel channel) {
  return (MidiByte)(((IUA)MsgProgram << 4) | ((MidiChannelMap(channel) & 0x0F) << 0));
}

MidiByte MidiLSB(IUD value) { return (MidiByte)(value & 0x7F); }

MidiByte MidiMSB(IUD value) { return (MidiByte)((value >> 7) & 0x7F); }

IUC MidiNoteOn(IUA* out, IUC* count, MidiChannel channel, IUA note,
              IUA velocity) {
  IUC i = *count;
  out[i++] = MidiStatus(MsgNoteOn, channel);
  out[i++] = note & 0x7F;
  out[i++] = velocity & 0x7F;
  *count = i;
  return i;
}

IUC MidiNoteOff(IUA* out, IUC* count, MidiChannel channel, IUA note,
               IUA velocity) {
  IUC i = *count;
  out[i++] = MidiStatus(MsgNoteOff, channel);
  out[i++] = note & 0x7F;
  out[i++] = velocity & 0x7F;
  *count = i;
  return i;
}

IUC MidiCC(IUA* out, IUC* count, MidiChannel channel, IUA cc, IUA value) {
  IUC i = *count;
  out[i++] = MidiStatus(MsgCC, channel);
  out[i++] = cc & 0x7F;
  out[i++] = value & 0x7F;
  *count = i;
  return i;
}

IUC MidiCC14(IUA* out, IUC* count, MidiChannel channel, IUD value14,
            IUA cc_lsb, IUA cc_msb) {
  IUC i = *count;
  out[i++] = MidiStatus(MsgCC, channel);
  out[i++] = cc_lsb & 0x7F;
  out[i++] = MidiLSB(value14);
  out[i++] = MidiStatus(MsgCC, channel);
  out[i++] = cc_msb & 0x7F;
  out[i++] = MidiMSB(value14);
  *count = i;
  return i;
}

IUC MidiPitchBend(IUA* out, IUC* count, MidiChannel channel, IUD value14) {
  IUC i = *count;
  out[i++] = MidiStatus(MsgPitch, channel);
  out[i++] = MidiLSB(value14);
  out[i++] = MidiMSB(value14);
  *count = i;
  return i;
}

IUC MidiMsgBytes(MidiMsg msg) {
  switch (msg) {
    case MsgProgram:
    case MsgChPress:
      return 2;  //< status + 1 data byte.
    default:
      return 3;  //< status + 2 data bytes.
  }
}

}  //< namespace _
#endif
