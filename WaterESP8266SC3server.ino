/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-client-server-wi-fi/  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/
 //    variable  test angle
 int mq2c1=0 , pwmmotor2=0 , waterc1 = 0 ;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp() {
   waterc1 = digitalRead(D5) ;
  Serial.print("Detect Water : ") ;
  Serial.print(waterc1) ;
  Serial.print("\n") ;
  return String(waterc1);  
}
 //  String readHumi() {
//  angleyr = random(-90,90) ;
//  return String(angleyr);
//   }
String readPres() {
   mq2c1 = analogRead(A0) ;
  Serial.print("Detect Gas Smoke : ") ;
  Serial.print(mq2c1) ;
  Serial.print("\n") ;
  return String(mq2c1);
}
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  pinMode(D4,OUTPUT) ;
  pinMode(D5,INPUT) ;
  pinMode(A0,INPUT) ;
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);  
  server.on("/waterc1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
    digitalWrite(D4,HIGH) ; 
    delay(100) ;
    digitalWrite(D4,LOW) ;
  });
  server.on("/mq2c1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPres().c_str());
    digitalWrite(D4,HIGH) ; 
    delay(100) ;
    digitalWrite(D4,LOW) ;
  });
  // Start server
  server.begin();
}
 
void loop(){  
}

