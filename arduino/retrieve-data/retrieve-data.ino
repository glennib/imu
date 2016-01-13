#include <Wire.h>
#include <stdint.h>

#include "Adxl.h"




void initialize() {
  Serial.begin(9600);
  Wire.begin();
  adxl_setup();
}


void setup() { // treat this as a main()
  initialize();


}



void loop() {
  // keeping this empty...
}
