# CrabsBed

CrabsBed is a Modern Embedded-C++ [Crabs](https://github.com/AStarStarship/Crabs) Firmware Development Kit (FDK). It is the firmware/hardware-control layer for the [Freedom Voting Machine](https://github.com/FreedomGovernment/FreedomVotingMachine) and other Crabs-based devices.

Crabs is based on the [Automaton Standard Code for Information Interchange (ASCII) Data Specification](https://github.com/AStarStarship/Crabs/blob/master/Spec/data), which uses easier to read and write 3-letter acronyms to replace the C++ Plain-Old-Data (POD) types; for instance a `uintptr_t` is `IUW`, Integer Unsigned Word, pronounced eye-you-wuh.

## Name

CrabsBed takes over the name of the **defunct mbed OS**. The old mbed embedded OS is no longer maintained; CrabsBed reclaims that name as the Crabs-native embedded firmware kit. (Renamed from CrabsTek, 2026-09-10.)

The defunct mbed OS source tree lives locally at `~/3P/mbed-os/` (master branch: `hal/`, `drivers/`, `rtos/`, `cmsis/`, `connectivity/`, `platform/`, `targets/`, `storage/`, `events/`). CrabsBed reuses/absorbs the useful HAL + drivers + RTOS pieces from that tree rather than starting from scratch — the name and the code both come with it.

## Devices

### Unicontroller

The Unicontroller, or Universal Controller, is a device for creating MIDI, DMX, and hardware controllers using a combination of GPIO, SPI, UART, interposes, and network connections. The FVM uses the Unicontroller for its ballot input surface (physical + semi-anonymized paper-trail capture).

## The Value Prop: One Firmware, Three Backends

The Unicontroller's firmware is pure logic — it polls a device interface, debounces the inputs, and emits MIDI bytes. It doesn't know or care what the device is. That means the **same firmware** runs on three backends:

- **Raspberry Pi** — real hardware, GPIO + SPI.
- **BeagleBone-AI** — real hardware, GPIO + SPI (the industrial target).
- **Virtual breadboard** — a software device model (`VirtualBreadboard`) that simulates the SPI shift registers, GPIO, and rotary encoders. The unit test drives the *real* firmware against the breadboard.

**That's the pain point it solves: you can run your controller's unit tests without the microcontroller.** No mbed, no virtualization, no "API kept changing." The seam architecture is what makes "one firmware" actually true instead of three codebases. The virtual breadboard is the "virtualized mbed" done right — as a seam, not a fake API.

## Mission and Vision

The mission of CrabsBed is to create a Crabs-native firmware and toolkit that works with **RISC-V** and **LTSpice** in an [Interactive Gym Environment & Educational Kit](https://github.com/AStarStarship/iGeek) environment — reclaiming the mbed name to simulate, test, and refine electronics virtually before ever touching a physical prototype. The Freedom Voting Machine is the first product built on CrabsBed.

## Stack position

- **ASCII Crabs core** — the all-contiguous stack machine (the data + compute layer).
- **CrabsBed** (this repo) — the embedded firmware / hardware-control FDK (the device layer).
- **SubsecondDb** — the full-stack database layer.
- **CrabsTK** — the tooling used to build the core.

## License

Copyright [AStarship™](https://astarship.net).
