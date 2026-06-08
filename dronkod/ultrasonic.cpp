#include "ultrasonic.h"
#include <Arduino.h>
#include "config.h"

volatile unsigned long echoStart = 0;
volatile unsigned long echoEnd = 0;
volatile bool echoReceived = false;

static float lastDistance = 0;


void triggerSensor() {
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10); 
    digitalWrite(TRIG, LOW);
}


void echoISR() {
    if (digitalRead(ECHO) == HIGH) {
        echoStart = micros();   
    } else {
        echoEnd = micros();     
        echoReceived = true;
    }
}


float getLastDistance() {
    noInterrupts();
    float distance = lastDistance;
    interrupts();
    return distance;
}


void updateLEDs(float distance) {
    int n = constrain(NUMPIXELS - int(distance / 2 - 4), 0, NUMPIXELS);

    pixels.clear();
    for (int i = 0; i < n; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    pixels.show();
}


void checkEcho() {
    if (echoReceived) {
        noInterrupts();
        unsigned long duration = echoEnd - echoStart;
        echoReceived = false;
        interrupts();

        lastDistance = duration / 58.0;
        updateLEDs(lastDistance);
    }
}

