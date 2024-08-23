# Energy-Meter

## Bee Data Logger Arduino

Welcome to the world of Bee Data Logging with Arduino! 🐝 This repository contains everything you need to get started with your Bee Data Logger project.

## Overview

The Bee Data Logger Arduino library enables you to gather and log valuable data from your bee colonies using Arduino. With easy-to-use examples and seamless integration with the Arduino IDE, you'll be up and running in no time.

## Installation

To install the Bee Data Logger library, simply follow these steps:

### Arduino Library Manager

1. Open Arduino IDE.
2. Navigate to **Sketch > Include Library > Manage Libraries...**.
3. Search for "Bee Data Logger" and click **Install**.

### Manual Installation

Alternatively, you can install the library manually from GitHub by following the instructions below.

## Getting Started

Programming your Bee Data Logger is a breeze! Just follow these simple steps:

### Add Espressif ESP32 Arduino Board Library

1. Go to **File > Preferences** in Arduino IDE.
2. Under "Additional Board Manager URLs," paste the following URL: [https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json).
3. Search for and install the ESP32 board library by Espressif (version 2.0.8 or later).

### Select Bee Data Logger Board

1. After installing the ESP32 library, go to **Tools > Board > Boards Manager**.
2. Search for "Bee Data Logger" and install the board library.

### Programming the Bee Data Logger

1. **STEP 1 (Upload)**:
   - Connect the USB-C cable to your Bee Data Logger.
   - Press and hold the *BOOT* button, then press the *RESET* button.
   - Release the *BOOT* button to enter download mode.
   - Select "Bee Data Logger" from the board manager.
2. **STEP 2 (Execute)**:
   - After uploading the code, press the *RESET* button on the board to execute the program.

That's it! You're ready to start logging data from your bee colonies like a pro. 📈 Happy logging!

Additional details can be found on The google docs file
https://docs.google.com/document/d/1kPj3NzwOtEeW1S5HBjY9oWhMNKQ8UEhDg4g_mmPkW0o/edit
