# Raspberry Pi Zero Voice Assistant with PWM Audio Output

This project implements a voice assistant using a Raspberry Pi Zero W. The assistant outputs audio via a speaker connected to the GPIO pins using Pulse Width Modulation (PWM). The assistant is designed to work in Portuguese, and it uses a microphone to capture voice commands.

## Features

- **Voice Recognition**: Captures and processes voice commands via a USB microphone.
- **Language Support**: The assistant understands and responds in Portuguese.
- **Audio Output**: Audio is played through an 8-ohm speaker connected to the GPIO pins using PWM.
- **Lightweight Setup**: Designed for the Raspberry Pi Zero W for low-cost, portable applications.

## Hardware Requirements

- **Raspberry Pi Zero W**
- **8-ohm Speaker**: Connected via GPIO pins (using PWM).
- **USB Microphone**
- **Capacitor**: 10 µF capacitor (for filtering PWM audio signal).
- **Wires/Breadboard**: For connecting the components.

### GPIO Connections

1. **GPIO 18 (Pin 12)**
2. **Capacitor to Speaker**: Connect the negative lead of the capacitor to the positive terminal of the speaker.
3. **GND (Pin 6)**: Connect to the negative terminal of the speaker.


## Software Requirements

- **Linux OS**: Light weight linux distro.
- **C++ Compiler**: To compile the voice assistant code (e.g., `g++`).
- **WiringPi Library**: For controlling the GPIO pins via C++.
- **Alsa-utils**: To handle audio playback.

