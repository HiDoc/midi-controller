#include "system.h"

void setup() {
  Serial.begin(9600);
  Serial.flush();

  setupLCD();
  setupButtons();
  setupLeds();
  setupMidi();
}

void loop() { 
  systemLoop(); 
}