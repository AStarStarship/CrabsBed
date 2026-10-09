// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
#if SEAM >= CRABS_BED_CORE
namespace CBTest {

// The test harness does NOT set the exit code from A_ASSERT/A_AVOW, so every
// unit tallies failures into a counter and returns a non-nil result on
// failure. SeamResult maps non-nil to a failure exit code.
inline const CHA* Core(const CHA* args) {
  (void)args;
  ISC fails = 0;
  A_TEST_BEGIN;

  // --- Debouncer: stable input settles to that input.
  {
    IUA state = 0;
    Debouncer<IUA> debouncer(&state);
    IUA change = 0;
    for (ISC i = 0; i < 8; ++i) change = debouncer.Debounce(0xA5);
    A_ASSERT(change == 0);
    A_AVOW(state, (IUA)0xA5);
  }

  // --- Debouncer: the first three samples fill the window; the state
  // commits on the 4th (reporting the XOR change), then settles.
  {
    IUA state = 0;
    Debouncer<IUA> debouncer(&state);
    IUA change = 0;
    for (ISC i = 0; i < 4; ++i) change = debouncer.Debounce(0x0F);
    A_ASSERT(change == 0x0F);  //< the commit reports the 0 -> 0x0F transition.
    A_AVOW(state, (IUA)0x0F);
    change = debouncer.Debounce(0x0F);
    A_ASSERT(change == 0);     //< settled: no further change.
  }

  // --- Debouncer: an edge after settle reports the XOR of changed bits.
  {
    IUA state = 0;
    Debouncer<IUA> debouncer(&state);
    IUA change = 0;
    for (ISC i = 0; i < 4; ++i) change = debouncer.Debounce(0x00);
    for (ISC i = 0; i < 4; ++i) change = debouncer.Debounce(0x33);
    A_ASSERT(change == 0x33);
    A_AVOW(state, (IUA)0x33);
  }

  // --- Debouncer: packed multi-byte state (the shift-register use case).
  {
    IUA states[2] = {0, 0};
    Debouncer<IUA> shift_debouncer(&states[0]);
    Debouncer<IUA> port_debouncer(&states[1]);
    IUA change = 0;
    for (ISC i = 0; i < 4; ++i) {
      change = shift_debouncer.Debounce(0x11);
      port_debouncer.Debounce(0x80);
    }
    A_ASSERT(change == 0x11);  //< commit reports the 0 -> 0x11 transition.
    A_AVOW(states[0], (IUA)0x11);
    A_AVOW(states[1], (IUA)0x80);
  }

  // --- Color: 5-6-5 packing (R:G:B = 5:6:5 bits in an IUB).
  // Layout: R=bits15..11, G=bits10..5, B=bits4..0.
  // white=0xFFFF ; red=0xF800 ; blue=0x001F ; half_green G=127>>2=31.
  {
    Color white = ColorMake(255, 255, 255);
    A_AVOW(white, (Color)0xFFFF);
    A_AVOW(ColorGetRed(white), (IUA)31);
    A_AVOW(ColorGetGreen(white), (IUA)63);
    A_AVOW(ColorGetBlue(white), (IUA)31);

    Color red = ColorMake(255, 0, 0);
    A_AVOW(red, (Color)0xF800);
    A_AVOW(ColorGetRed(red), (IUA)31);
    A_AVOW(ColorGetGreen(red), (IUA)0);
    A_AVOW(ColorGetBlue(red), (IUA)0);

    Color blue = ColorMake(0, 0, 255);
    A_AVOW(blue, (Color)0x001F);
    A_AVOW(ColorGetBlue(blue), (IUA)31);
    A_AVOW(ColorGetRed(blue), (IUA)0);

    Color half_green = ColorMake(0, 127, 0);
    A_AVOW(ColorGetGreen(half_green), (IUA)31);
  }

  // --- Color: preset table is 24-bit IUD, presets pack to 16-bit.
  {
    const IUD* presets = PresetColors();
    A_ASSERT_PTR((const void*)presets);
    A_AVOW(presets[0], (IUD)0xFFFFFF);  //< White
    A_AVOW(presets[14], (IUD)0xFF0000); //< Red
    A_AVOW(presets[17], (IUD)0x000000); //< Black
    A_ASSERT(NumPresetColors == 18);
    // ColorPreset converts 24-bit down to 5-6-5.
    A_AVOW(ColorPreset(0), (Color)0xFFFF);  //< White -> full 5-6-5.
    A_AVOW(ColorPreset(14), (Color)0xF800); //< Red -> R=31 only.
  }

  // --- Color: mix is an equal-weight average of the packed channels.
  // ColorMake(0x3C,0,0): red=0x3C>>3=7. ColorMake(0xFF,0,0): red=31. avg=19.
  {
    Color a = ColorMake(0x3C, 0, 0);
    Color b = ColorMake(0xFF, 0, 0);
    Color mixed = ColorMix(a, b);
    A_AVOW(ColorGetRed(mixed), (IUA)19);
    A_AVOW(ColorGetGreen(mixed), (IUA)0);
  }

  // --- Color: mix ratio (255 = replace, 0 = keep).
  {
    A_AVOW(ColorMixRatio(100, 200, 255), (IUA)100);
    A_AVOW(ColorMixRatio(100, 200, 0), (IUA)200);
    A_AVOW(ColorMixRatio(100, 200, 127), (IUA)150);
  }

  // --- LEDs: bit operations on an 8-bit SPI chain (32 LEDs).
  {
    IUA chain[4] = {0, 0, 0, 0};
    A_ASSERT(GetLedState(chain, 0) == false);
    TurnLedOn(chain, 0);
    A_ASSERT(GetLedState(chain, 0) == true);
    A_ASSERT(GetLedState(chain, 1) == false);
    TurnLedOn(chain, 9);  //< byte 1, bit 1.
    A_ASSERT(chain[1] == 0x02);
    ToggleLed(chain, 0);
    A_ASSERT(GetLedState(chain, 0) == false);
    A_ASSERT(chain[0] == 0);
    SetLedState(chain, 8, true);
    A_ASSERT(chain[1] == 0x03);  //< bit1 (LED9) + bit0 (LED8).
    SetLedState(chain, 8, false);
    A_ASSERT(chain[1] == 0x02);  //< only LED9 remains.
  }

  // --- LEDs: the Led record stores its bit and row.
  {
    Led led(17, 2);
    led.Print(NILP);
  }

  // --- MIDI: 14-bit value splits into LSB then MSB (the Unicontroller contract).
  {
    // 16383 (all 14 bits set) -> LSB=0x7F, MSB=0x7F.
    A_AVOW(MidiLSB(16383), (IUA)0x7F);
    A_AVOW(MidiMSB(16383), (IUA)0x7F);
    // 0x7F (127) -> LSB=0x7F, MSB=0x00.
    A_AVOW(MidiLSB(127), (IUA)0x7F);
    A_AVOW(MidiMSB(127), (IUA)0x00);
    // 0x80 (128) -> LSB=0x00, MSB=0x01.
    A_AVOW(MidiLSB(128), (IUA)0x00);
    A_AVOW(MidiMSB(128), (IUA)0x01);
    // 0 -> LSB=0, MSB=0.
    A_AVOW(MidiLSB(0), (IUA)0x00);
    A_AVOW(MidiMSB(0), (IUA)0x00);
  }

  // --- MIDI: channel mapping (0..31 -> 32..63 mixer channel, wraps mod 16
  // in the 4-bit MIDI status channel).
  {
    A_AVOW(MidiChannelMap(0), (IUC)32);
    A_AVOW(MidiChannelMap(15), (IUC)47);
    A_AVOW(MidiChannelMap(31), (IUC)63);
    // In the status byte, channel 0 -> MIDI ch 0, channel 15 -> MIDI ch 15.
    A_AVOW(MidiStatus(MsgNoteOn, 0), (IUA)0x90);
    A_AVOW(MidiStatus(MsgNoteOn, 15), (IUA)0x9F);
  }

  // --- MIDI: note-on encoding (status, note, velocity).
  {
    IUA out[8] = {0};
    IUC count = 0;
    MidiNoteOn(out, &count, 0, 60, 100);  //< C4, velocity 100, unichannel 0.
    A_AVOW(count, (IUC)3);
    A_AVOW(out[0], (IUA)0x90);  //< note-on, MIDI channel 0.
    A_AVOW(out[1], (IUA)60);    //< C4.
    A_AVOW(out[2], (IUA)100);   //< velocity.
  }

  // --- Virtual breadboard: drive the firmware against simulated hardware.
  // This is the "run your tests without the microcontroller" proof: the real
  // UnicontrollerDriver code runs against the VirtualBreadboard.
  {
    VirtualBreadboard bb(/*spi_bytes=*/1, /*gpio_pins=*/8, /*encoders=*/0);
    UnicontrollerDriver driver(bb, /*num_buttons=*/8);

    // Initially no buttons pressed -> no MIDI output after settle.
    IUC n = driver.Poll();
    A_ASSERT(n == 0);

    // Press button 0 (SPI byte 0, bit 0). Feed the debouncer enough samples
    // for it to commit (4 samples for the 3-sample majority window).
    bb.spi().SetButton(0, 0, true);
    n = driver.Poll();  //< sample 1
    n = driver.Poll();  //< sample 2
    n = driver.Poll();  //< sample 3
    n = driver.Poll();  //< sample 4 (commit) — should emit note-on.
    A_ASSERT(n == 3);  //< note-on is 3 bytes.
    A_AVOW(driver.midi_out()[0], (IUA)MidiStatus(MsgNoteOn, 0));
    A_AVOW(driver.midi_out()[1], (IUA)0);  //< note number = button 0.
    A_AVOW(driver.midi_out()[2], (IUA)100);  //< velocity.

    // Release button 0.
    bb.spi().SetButton(0, 0, false);
    for (ISC i = 0; i < 4; ++i) n = driver.Poll();
    A_ASSERT(n == 3);  //< note-off is 3 bytes.
    A_AVOW(driver.midi_out()[0], (IUA)MidiStatus(MsgNoteOff, 0));
    A_AVOW(driver.midi_out()[1], (IUA)0);
    A_AVOW(driver.midi_out()[2], (IUA)0);
  }

  if (fails != 0) {
    D_COUT(" CrabsBed core test failures: " << fails << "\n");
    return "crabs_bed_core_test_failure";
  }
  return NILP;
}

}  //< namespace CBTest
#endif
