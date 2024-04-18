#include <Arduino.h>
#include "srf.h"


// Creat class instance

void SRF::init(uint8_t triggerPin, uint8_t echoPin) {
  
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;

  pinMode (triggerPin, OUTPUT);
  pinMode (echoPin , INPUT); 

}

// Initialization class SRF

SRF::SRF(uint8_t triggerPin, uint8_t echoPin) {
  this -> init(triggerPin, echoPin);
}


// Calculate and return distance in CM
// max detectable range is about 2 meter

float SRF::getDistance() {

  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);

  noInterrupts();

  uint32_t duration = pulseIn(this->echoPin, HIGH , 11600);  

  interrupts();
  
  float distance = (duration/2)/29.1; 

  if (distance >= 200 || distance <= 0) {
    Serial.println("Outof Range");
    return -1 ;
  }
  else {
    return distance ;
  }
}


// Calculate and return the distance in CM or IN

float SRF::getDistance (char *unit) {
  if (unit == "cm"){
    return this->getDistance();
  } else if (unit == "in") {
    float distanceCM = this->getDistance();
    return (distanceCM/2.54) ;
  }
}

// Detect if ther is anything in the range that specified 

bool SRF::detect(int range) {
  float detected = this->getDistance();
  if ( detected <= range && detected >= 0) {
    return true;
  } else {
    return false;
  }
}


// calculate the distance for 100 Ms and return the average of them
// return value is in CM

float SRF::getDistanceStable () {
  
  float sumOfDistances = 0 ;
  int i = 0 ;
  long long startMeasure = millis() ;

  while ( i < 15 && ( (millis()-startMeasure) < 100) ) {
    float newMeasure = this->getDistance();
    if ( newMeasure > 0 ) {
      sumOfDistances += newMeasure ;
      i++ ;
    }
  } 
  return (sumOfDistances/i) ;

}

// calculate the distance for 100 Ms and return the average of them
// return value is in CM or IN

float SRF::getDistanceStable (char *unit) {

  float sumOfDistances = 0 ;
  int i = 0 ;
  long long startMeasure = millis() ;

  while ( i < 15 && ( (millis()-startMeasure) < 100) ) {
    float newMeasure = this->getDistance();
    if ( newMeasure > 0 ) {
      sumOfDistances += newMeasure ;
      i++ ;
    }
  } 

  if ( unit == "cm" ) {
    return (sumOfDistances/i) ;
  } else if ( unit == "in" ) {
    return ( (sumOfDistances/i) / 2.54 ) ;
  }
}



