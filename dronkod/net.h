#ifndef NET_H
#define NET_H

#include <Arduino.h>

bool connectWiFiInternal();
void setupSieci();


void utrzymujPolaczenie();

String odbierzKomende();
void sendMeasurement(float temperature, float pressure, float humidity, String localization);

#endif