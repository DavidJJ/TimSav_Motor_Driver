# TimSav Motor Driver - PWM Controller

Simple PWM driver for Arduino that outputs a fixed or potentiometer-selected
frequency on pin 9.

## Built For
- Board: Arduino Nano (ATmega328P)
- Framework: Arduino
- PlatformIO environment: `env:nanoatmega328`

## Behavior
- PWM output: pin 9 via Servo library (~50 Hz refresh)
- Mode input: digital pin 2
  - HIGH: pulse width follows potentiometer on A0
  - LOW: pulse width fixed at 1000 us

## Pulse Width Range
- Potentiometer maps to 1000 us - 2000 us
- Limits can be adjusted in `src/main.cpp`

## Wiring
- Potentiometer wiper to A0, ends to 5V and GND
- Mode input to D2 
  - 10k ohm pull-down resistor from D2 to GND.
- PWM output on D9

## Build/Upload
```sh
pio run
pio run -t upload
```
