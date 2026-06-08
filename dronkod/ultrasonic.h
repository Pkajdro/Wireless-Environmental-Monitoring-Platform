#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;


void triggerSensor();         
void checkEcho();    
void updateLEDs(float distance); 
float getLastDistance();  
void echoISR();       

#endif // ULTRASONIC_H
