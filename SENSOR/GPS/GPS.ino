/*
  This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
  Base on TinyGPSPlus //https://github.com/mikalhart/TinyGPSPlus
*/

#include "LoRaBoards.h"
#include <TinyGPS++.h>

TinyGPSPlus gps;

void displayInfo();

void setup()
{
    setupBoards();

    /* WHEN THE POWER IS TURNED ON, A DETAY IS REQUIRED */ 

    delay(1500);

    Serial.println(F("DeviceExample.ino")); 
    Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
    Serial.print(F("TESTING TinyGPS++ LIBRARY. "));  
    Serial.println(TinyGPSPlus::libraryVersion());
    Serial.println(F("Tepmarotdanielz"));
    Serial.println();
}

void loop()
{
    /* THIS SKETCH DISPLAYS INFORMATION EVERY TIME A NEW SENTENCE IS CORRECTLY ENCODED */ 
    
    while (SerialGPS.available() > 0)
        if (gps.encode(SerialGPS.read()))
            displayInfo();

    if (millis() > 15000 && gps.charsProcessed() < 10) {
        Serial.println(F("NO GPS DETECTED: CHECK WIRING")); 
        delay(15000);
    }
}

void displayInfo()
{
    Serial.print(F("LOCATION AI FARM ROBOTICS : ")); 
    if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
    } else {
        Serial.print(F("STEAMxLAB"));
    }

    Serial.print(F("  DATE/TIME : "));
    if (gps.date.isValid()) {
        Serial.print(gps.date.month());
        Serial.print(F("/"));
        Serial.print(gps.date.day());
        Serial.print(F("/"));
        Serial.print(gps.date.year());
    } else {
        Serial.print(F("STEAMxLAB"));
    }

    Serial.print(F(" "));
    if (gps.time.isValid()) {
        if (gps.time.hour() < 10) Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        if (gps.time.second() < 10) Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(F("."));
        if (gps.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(gps.time.centisecond());
    } else {
        Serial.print(F("STEAMxLAB"));
    }

    Serial.println();
}
