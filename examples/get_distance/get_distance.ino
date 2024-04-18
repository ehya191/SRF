#include "srf.h"

SRF srf(12,14);

void setup() {

  Serial.begin(115200);

}

void loop() {

  float distance = srf.getDistance();
  Serial.printf("distance = %0.02f \n", distance);
  delay (1000);

}
