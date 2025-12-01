# Smart Alarm Clock - ENSC 351 Final Project

This is a smart alarm clock that can gather weather updates, calendar events, message notifications.


## Hardware:

The following components are required for the project:
- BeagleBoard BeagleY-AI
- SSD1780 OLED Display
- Rotary Encoder


## Necessary dependencies:

- Node.js
- openmeteo API
- googleapis
- @google-cloud/local-auth
- CMake: `sudo apt update` and `sudo apt install cmake`
- SSD1306 Linux Driver: https://github.com/armlabs/ssd1306_linux.git

## Running CMake

To manually run CMake from the command line use:

```shell
  # Regenerate build/ folder and makefiles:
  rm -rf build/         # Wipes temporary build folder
  cmake -S . -B build   # Generate makefiles in build\

  # Build (compile & link) the project
  cmake --build build
```

## Running the server

Run the server using `node index.js` on the **host**. This will start fetching the weather and calendar every 24 hours.
