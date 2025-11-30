# Smart Alarm Clock - ENSC 351 Final Project

This is a smart alarm clock that can gather weather updates, calendar events, message notifications.


## Hardware:

The following components are required for the project:
- BeagleBoard BeagleY-AI
- SSD1780 OLED Display
- Rotary Encoder


## Necessary dependencies:

- Node.js (npm install)
- openmeteo
- googleapis
- @google-cloud/local-auth
- libjson-c-dev
- CMake: `sudo apt update` and `sudo apt install cmake`
- git clone https://github.com/armlabs/ssd1306_linux.git

## Running CMake

To manually run CMake from the command line use:

```shell
  # Regenerate build/ folder and makefiles:
  rm -rf build/         # Wipes temporary build folder
  cmake -S . -B build   # Generate makefiles in build\

  # Build (compile & link) the project
  cmake --build build
```
