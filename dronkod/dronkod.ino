#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "ultrasonic.h"
#include "config.h"
#include "sensor.h"
#include "engine.h"
#include "net.h"
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastTrigger = 0;
unsigned long lastSendTime = 0;
const unsigned long triggerInterval = 80;
bool readingSensors = false;
bool manewrCofania = false;           
unsigned long czasStartuCofania = 0; 
const unsigned long czasCofania = 2000; 

void setup() {
    Serial.begin(115200);

    pixels.begin();
    pixels.clear();
    pixels.show();

    pinMode(TRIG, OUTPUT);
    digitalWrite(TRIG, LOW);

    pinMode(ECHO, INPUT);
    attachInterrupt(digitalPinToInterrupt(ECHO), echoISR, CHANGE);
    Wire.begin();
    if (!setup_bmp280()) {
      Serial.println("BMP280 init FAILED");
      //while(1);
    }
    konfigurujSilniki();
    setupSieci();
}

void loop() {
    unsigned long now = millis();
    //silnik
    utrzymujPolaczenie();
  
    if (manewrCofania) {
        if (now - czasStartuCofania >= czasCofania) {
            stopTyl();             
            manewrCofania = false; 
            Serial.println("Koniec manewru cofania.");
        }
    }
    if (!manewrCofania) {
      String komenda = odbierzKomende();
      if (komenda != "") {
        
        if (komenda.equalsIgnoreCase("1")) {
          jedzDoPrzodu();
          Serial.println("Przod");
        } 
        else if (komenda.equalsIgnoreCase("2")) {
          stopPrzod();
          Serial.println("stop");
        } 
        else if (komenda.equalsIgnoreCase("3")) {
          jedzDoTylu();
          Serial.println("tyl");
        } 
        else if (komenda.equalsIgnoreCase("4")) {
          stopTyl();
          Serial.println("stoptyl");
        } 
        else if (komenda.equalsIgnoreCase("5")) {
          skrecWLewo();
          Serial.println("lewo");
        } 
        else if (komenda.equalsIgnoreCase("6")) {
          stopLewo();
          Serial.println("stoplewo");
        } 
        else if (komenda.equalsIgnoreCase("7")) {
          skrecWPrawo();
          Serial.println("prawo");
        } 
        else if (komenda.equalsIgnoreCase("8")) {
          stopPrawo();
          Serial.println("stopprawo");
        }
      }
    }
    //koniec silnik
    
    if (now - lastSendTime >= 5000) {
      lastSendTime = now;
      readingSensors = true;
      float temperature, pressure, humidity;

      read_bmp280(temperature, pressure);
      output_bmp280(temperature, pressure);

      read_dht11(humidity);
      output_dht11(humidity);
      
      //sendMeasurement(temperature, pressure, humidity, "Salon"); //zakomentować jak nie używa się strony
      readingSensors = false;

      
    }
  
    if (!readingSensors && (now - lastTrigger >= triggerInterval)) {
        lastTrigger = now;
        triggerSensor(); // 
    }
    float dystans = getLastDistance();

    // Jeśli wykryto przeszkodę (< 10cm) 
    if (!manewrCofania && dystans > 0.1 && dystans < 10.0) {
        Serial.println("Przeszkoda! Start cofania (NON-BLOCKING)...");
        
        stopWszystko();        
        jedzDoTylu();          
        
        manewrCofania = true;   
        czasStartuCofania = now;
    }
   
    checkEcho();

   
}
