# si5351_antenna_analyser
Si5351 based antenna analyser using ESP32 or Arduino.

The Si5351 is a few kHz to 200 MHz clock source controllable over i2c.
A uC (ESP32 or Arduino) will scan the frequency range the connected antenna
is designed for, and determine the swr using the resistive swr bridge.
If an ESP32 is used, it will present a web page with the results, if
an arduino is used the results of the sweep will be send back over serial.
