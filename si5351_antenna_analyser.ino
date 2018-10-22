// Thanks to Robin2 on http://forum.arduino.cc/index.php?topic=396450
#include "si5351.h"
#include "Wire.h"

// #define LED_BUILTIN 2 // ESP32

Si5351 si5351;

const byte numChars = 12;
char receivedChars[numChars] = {0};   // an array to store the received data

boolean newFreq = false;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(115200);
  
  if(si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0)) {
    Serial.println("SI5351 found, enabling clk1");
    si5351.output_enable(SI5351_CLK0, 0);
    si5351.output_enable(SI5351_CLK1, 1);
    si5351.output_enable(SI5351_CLK2, 0);
  }
  else {
    Serial.println("SI5351 not found");
  }
  
  Serial.println("<Arduino is ready, send new frequency with 2 decimals, e.g. 8100000 for 81kHz. (max=4294967295=43MHz)>");
}

void loop() {
  recvWithEndMarker();
  updateFrequency();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  if (Serial.available() > 0) {
    rc = Serial.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newFreq = true;
    }
  }
}

void updateFrequency() {
  if(newFreq == true) {
    if(receivedChars[0] == '?') {
      Serial.println("ready");
    }
    else {
      unsigned long freq = strtoul(receivedChars, NULL, 10);
      si5351.set_freq(freq, SI5351_CLK1);

      // calculate SWR
      delay(50);
      float FWD = (float)analogRead(A0);
      float REV = (float)analogRead(A1);
      float SWR = (FWD+REV) / (FWD-REV);
    
      Serial.print(freq);
      Serial.print(":");
      Serial.println(SWR);
    }
    
    newFreq = false;
    memset(receivedChars, 0, numChars);
  }
}
