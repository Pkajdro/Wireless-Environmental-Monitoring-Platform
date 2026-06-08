#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <DHT11.h>
#include "sensor.h"
#include "config.h"

Adafruit_BMP280 bmp;
DHT11 dht11(DHT11_PIN);

bool setup_bmp280() {
  if (!bmp.begin(0x76)) {   
    Serial.println("Nie znaleziono czujnika BMP280!");
    return false;
  }
  Serial.println("BMP280 działa poprawnie");
  return true;
}

void output_bmp280(float temperature, float pressure) { 
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C  Cisnienie: ");
  Serial.print(pressure);
  Serial.println(" hPa");
}

void read_bmp280(float &temperature, float &pressure) {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0; // hPa
}

void output_dht11(float humidity) {  
  Serial.print("Wilgotnosc (%): ");             
  Serial.print(humidity);
} 

void read_dht11(float &humidity) {
  humidity = (float)dht11.readHumidity();
}

