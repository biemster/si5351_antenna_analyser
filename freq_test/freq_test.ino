#include "si5351.h"
#include "Wire.h"

// #define LED_BUILTIN 2 // ESP32

Si5351 si5351;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  if(si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0)) {
    si5351.set_freq(1400000000ULL, SI5351_CLK0);
    si5351.set_freq(2800000000ULL, SI5351_CLK1);
    si5351.set_freq(5600000000ULL, SI5351_CLK2);

    si5351.update_status();
    delay(1000);
    print_si5351_status();
  }
  else {
    Serial.println("SI5351 not found");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  si5351.update_status();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  print_si5351_status();
}

void print_si5351_status() {
  Serial.print("SYS_INIT: ");
  Serial.print(si5351.dev_status.SYS_INIT);
  Serial.print("  LOL_A: ");
  Serial.print(si5351.dev_status.LOL_A);
  Serial.print("  LOL_B: ");
  Serial.print(si5351.dev_status.LOL_B);
  Serial.print("  LOS: ");
  Serial.print(si5351.dev_status.LOS);
  Serial.print("  REVID: ");
  Serial.println(si5351.dev_status.REVID);
}
