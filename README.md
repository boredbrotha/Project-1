# Project 1

A polyphonic dual oscillator synthesizer plugin built with JUCE framework.

## Features

### Dual Oscillator Architecture
- **8-voice polyphony** with independent dual oscillators per voice
- **4 waveform types** per oscillator: Sine, Saw, Square, Triangle
- **Independent signal chains** for each oscillator (OSC1 and OSC2)
- **UI oscillator switching** - toggle between editing OSC1 and OSC2 parameters

### Sound Shaping
- **ADSR Envelopes**
  - Attack: 0.1s - 1.0s
  - Decay: 0.1s - 1.0s
  - Sustain: 0.1 - 1.0
  - Release: 0.1s - 3.0s

- **Multi-Mode Filters**
  - Filter types: Low-Pass, Band-Pass, High-Pass
  - Cutoff frequency: 20Hz - 20kHz (logarithmic scale)
  - Resonance: 1.0 - 10.0

- **Pitch Control**
  - Octave shift: ±4 octaves
  - Semitone shift: ±12 semitones

- **Master Gain**
  - Range: -100dB to 0dB
  - Per-oscillator gain control

### Preset Management
- **Save presets** to XML files via file browser
- **Load presets** from XML files
- **DAW integration** - plugin state saves/loads with your DAW project
- Presets stored in human-readable XML format

## Plugin Format
- **VST3** (Visual Studio 2022)
- **Standalone** build supported
- **MIDI input** enabled
- **Mono/Stereo** output

## Technical Details

### Architecture
- **Manufacturer**: Asahd Hamilton
- **Framework**: JUCE 7.x+
- **Parameters**: 30 total (15 per oscillator)
- **Signal Flow**: OSC → Gain → Filter → ADSR (parallel dual chains)

### Parameter List
**OSC1/OSC2:**
- Waveform selection
- Attack, Decay, Sustain, Release
- Master Gain
- Octave and Semitone pitch shift
- Filter type, frequency, and resonance

## Building from Source

### Requirements
- Visual Studio 2022 (Windows)
- JUCE Framework 7.x or later
- VST3 SDK (included with JUCE)

### Build Instructions
1. Open `Project 1.jucer` in Projucer
2. Export to Visual Studio 2022
3. Open the generated solution in `Builds/VisualStudio2022/`
4. Build the desired configuration (Debug/Release)
5. VST3 plugin will be output to your system's VST3 directory

## Usage

### UI Layout
```
┌─────────────────┬─────────────────┐
│   Oscillator    │      ADSR       │
│   Controls      │    Envelopes    │
│   + Gain        │                 │
│   + Pitch       │                 │
├─────────────────┼─────────────────┤
│     Filter      │  [1] [2]        │
│    Controls     │  [Save] [Load]  │
│                 │  (Buttons)      │
└─────────────────┴─────────────────┘
```

### Controls
- **[1] / [2] Buttons**: Switch between editing OSC1 or OSC2 parameters
- **[Save] Button**: Export current settings to XML preset file
- **[Load] Button**: Import settings from XML preset file

### Default Settings
- **Waveform**: Sine
- **ADSR**: A=0.1s, D=0.1s, S=1.0, R=0.4s
- **Master Gain**: -18dB
- **Pitch**: 0 octaves, 0 semitones
- **Filter**: Low-Pass, 200Hz cutoff, 1.0 resonance

## Project History
- **Started**: February 2025
- **Status**: Complete
- Development paused April-October 2025 due to internship

## License
All rights reserved.

## Author
Asahd Hamilton

---

*Built with JUCE Framework*
