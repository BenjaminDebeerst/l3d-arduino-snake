# L3D Arduino Snake

Work In Progress to implement a 3D Snake game on an Arduino Uno with a 8x8x8 Neopixel LEDs.

Working:
- Display of a moving Snake, with slightly different color of the head
- Changing direction based on user input

Todo:
- Any kind of collision detection
- Placement of gems/thigs to pick up
- Any kind of scoring or end-of-game implementation

Known issues
* Sometimes, some (not-really random) pixels are turned on.
* The slowdown is not always working, sometimes the Snake takse two steps at once.

# Installing Dependncies

This project is built using [platformio-core](http://platformio.org/get-started/cli) and uses the [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) library.

After having installed platformio, e.g. [via pip](http://docs.platformio.org/en/latest/installation.html#python-package-manager) install the Adafruit Neopixel dependency
using `pio lib install "Adafruit NeoPixel"`.

# Building

To build the project, run `pio run`

To build and flash run `pio run --target upload`
The platformio project is setup for the Arduino Uno platform and will automatically detect a connected device to perform the flashing.
