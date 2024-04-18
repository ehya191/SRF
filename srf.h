
#ifndef SRF_H
#define SRF_H

#include <Arduino.h>

class SRF {
  public:
    SRF(uint8_t triggerPin, uint8_t echoPin);                   
    float getDistance () ;                                      
    float getDistance (char *unit) ;                                  
    bool  detect(int range) ;
    float getDistanceStable () ;
    float getDistanceStable (char *unit) ;
    
  private:
    void init (uint8_t triggerPin, uint8_t echoPin);
    int triggerPin ;
    int echoPin ;

};



#endif