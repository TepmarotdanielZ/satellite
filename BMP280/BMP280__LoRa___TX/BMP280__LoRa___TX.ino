// Required Libraries
#include <LoRa.h>
#include "LoRaBoards.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Constants
const int LORA_FREQ_CONFIG = 915E6; // Adjust this to your frequency

// Globals
Adafruit_BMP280 bmp; // BMP280 sensor object
int counter = 0; // Packet counter

void setup() {
    // Initialize Serial Communication
    Serial.begin(115200);
    Serial.println("LoRa Sender");

    // Initialize LoRa
    setupLoRa();

    // Initialize BMP280
    setupBMP280();
}

void loop() {
    // Read BMP280 Data
    String data = readBMP280Data();

    // Send Data via LoRa
    sendLoRaPacket(data);

    // Print data to Serial Monitor
    Serial.println(data);

    // Wait before sending the next packet
    delay(5000); // Adjust delay as needed
}

void setupLoRa() {
    setupBoards();
    delay(1500);

#ifdef RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(LORA_FREQ_CONFIG)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void setupBMP280() {
    if (!bmp.begin(0x76)) {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        while (1) delay(10);
    }
}

String readBMP280Data() {
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100.0F; // Convert Pa to hPa
    return String("TEMP:") + temperature + ", PRESS:" + pressure;
}

void sendLoRaPacket(const String &data) {
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
}
