# Sklite
Firmware, and resources for Sklite.

## What is Sklite?

Sklite is a protocol for IoT lights, and firmware for different chips that implements the protocol.

This repo also has other resources, like
 * software for controlling Sklites
 * the documentation of the Sklite protocol
 * and others

## Building a Sklite
Currently, there are no official pre-made Sklites available for use, so you must build one yourself.

### Requirements

 * One of the supported chips: ESP8266
 * An LED chipset [supported by FastLED](https://github.com/FastLED/FastLED/wiki/Overview#supported-chipsets)
 * A [control method](#control) that you can use

### Notes

Sklite doesn't support individual addressing for LED strips that enable it.

### Setup

 1. Clone this repository. `git clone https://github.com/moriczgergo/sklite`
 3. Open the code for your chip. (e.g. for `esp8266`, the folder would be `Sklite-esp8266`)
 2. Copy `config-example.h` into that folder , rename it to `config.h`, and customize the settings in there.
 4. Change LED settings where a comment shows you to.
 5. Upload the code to the chip.

### Control

You can control the lights via these methods:
 * homebridge-better-http-rgb, [Guide](https://github.com/moriczgergo/sklite/blob/master/guides/homebridge.md)
 * sklite-control, [Website](https://moriczgergo.github.io/sklite-control/)