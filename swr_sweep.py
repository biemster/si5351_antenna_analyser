#!/usr/bin/env python
import serial
from time import sleep

is_ready = False
with serial.Serial('/dev/ttyUSB0', 115200, timeout=1) as ser:
    while not is_ready:
        ser.write(b'?\n')
        response = ser.readline()
        if response.startswith(b'ready'):
            is_ready = True
        sleep(0.1)
    
    freq = 2800000000 # in units of 1/100 Hz, 8100000 is 81kHz
    step = 10000000   # 100kHz
    freq_min = freq - int(1e8) # -1MHz
    freq_max = freq + int(1e8) # +1MHz
    freqs = list(range(freq_min, freq_max, step))
    freqs += list(range(freq_max, freq_min, -step))
    while 1:
        for f in freqs:
            ser.write((str(f) + '\n').encode())
            sleep(0.333)