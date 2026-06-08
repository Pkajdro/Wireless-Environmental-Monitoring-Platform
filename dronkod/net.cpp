#include <WiFiS3.h>
#include "net.h"
#include <ArduinoHttpClient.h>

const char* ssid = "tea123";      
const char* password = "murzyn123";    
const char* dataServerName = "192.168.0.209"; 
int dataServerPort = 5000;





WiFiServer server(5000);              
WiFiClient currentClient;              
WiFiClient wifiClientHttp;
HttpClient http(wifiClientHttp, dataServerName, dataServerPort);

bool connectWiFiInternal() {
  
  WiFi.disconnect(); 
  delay(500);
  
  
  
  
  WiFi.begin(ssid, password);          
  
  int maxRetries = 40;                
  while ((WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0,0,0,0)) && maxRetries > 0) { 
    delay(500);
    Serial.print(".");                
    maxRetries--;
  }

  
  
  return (WiFi.status() == WL_CONNECTED && WiFi.localIP() != IPAddress(0,0,0,0)); 
}
void setupSieci() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  bool connected = false;
  
  for (int attempt = 0; attempt < 5 && !connected; attempt++) { 
    delay(2000);
    Serial.print("\nAttempt ");
    Serial.println(attempt + 1);
    connected = connectWiFiInternal(); 
  }

  if (connected) {
    Serial.println("\nWiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();                    
  } else {
    Serial.println("\nFailed to connect to WiFi after multiple attempts."); 
  }
}

void utrzymujPolaczenie() {
 
  if (WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0,0,0,0)) {
    Serial.println("WiFi lost. Reconnecting...");
    
    
    bool reconnected = false;
    for (int attempt = 0; attempt < 5 && !reconnected; attempt++) { 
      delay(2000);
      reconnected = connectWiFiInternal(); 
    }

    if (reconnected) {
      Serial.println("Reconnected.");
      server.begin(); 
    } else {
      Serial.println("Reconnection failed. Waiting 5s before retry."); //
      delay(5000); 
    }
  }
}


String _buforLinii = ""; 

String odbierzKomende() {
 
  if (!currentClient || !currentClient.connected()) {
    currentClient = server.available(); //
    if (currentClient) {
      Serial.println("Client connected");
      _buforLinii = ""; 
    }
  }


  if (currentClient && currentClient.available()) {
    char c = currentClient.read(); //

    
    if (c == '\n') {               
      _buforLinii.trim();          
      
      String gotowaKomenda = _buforLinii;
      _buforLinii = "";           
      
      return gotowaKomenda;        
      
    } else if (c != '\r') {        //
      _buforLinii += c;            //
    }
  }

  return ""; 
}

void sendMeasurement(float temperature, float pressure, float humidity, String localization) {
  // Sprawdź czy mamy WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Brak WiFi - nie wysyłam danych.");
    return;
  }

  // Budowanie JSON-a
  String postData = "{";
  postData += "\"temperature\":" + String(temperature) + ",";
  postData += "\"pressure\":" + String(pressure) + ",";
  postData += "\"humidity\":" + String(humidity) + ",";
  postData += "\"localization\":\"" + localization + "\"";
  postData += "}";

  http.setHttpResponseTimeout(10);
  // Wysyłanie żądania HTTP POST
  // Endpoint ustawiony na "/espdata" zgodnie z Twoim przykładem
  Serial.println("Wysyłanie danych HTTP...");
  
  http.beginRequest();
  http.post("/espdata"); 
  http.sendHeader("Content-Type", "application/json");
  http.sendHeader("Content-Length", postData.length());
  http.beginBody();
  http.print(postData);
  http.endRequest();

  // Sprawdzenie statusu
  int statusCode = http.responseStatusCode();
  String response = http.responseBody(); 
  

  if (statusCode > 0) {
    Serial.print("Wysłano OK. Kod: ");
    Serial.println(statusCode);
  } else {
    Serial.print("Błąd wysyłania HTTP: ");
    Serial.println(statusCode);
  }
  http.stop();
}