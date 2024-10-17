# opendmxusb-ftdi-arm-cpp

A C++ app to control an Enttec Open DMX USB interface in C++ for Raspberry Pi 3B, using the FTDI lib.

## Introduction

This is inspired by https://github.com/wberdowski/DMX.NET. I managed to make the C# code work on my Windows computer, but I couldn't make it work.
This project is an effort to control the USB interface using C++ code.

## Objective

Expose an OSC API to control a fixture I have, the `EasyDancing 36x1W RGB Par Light 7CH`:
* Dimmer
* Red
* Green
* Blue
* Strobe
* Zero
* Zero
