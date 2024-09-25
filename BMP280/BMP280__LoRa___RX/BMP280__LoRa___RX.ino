// Required Libraries
#include <LoRa.h>
#include "LoRaBoards.h"

// Constants
const int LORA_FREQ_CONFIG = 915E6; // Adjust this to your frequency

void setup() {
    // Initialize Serial Communication
    Serial.begin(115200);
    Serial.println("LoRa Receiver");

    // Initialize LoRa
    setupLoRa();
}

void loop() {
    // Check for incoming packets
    if (LoRa.parsePacket()) {
        String data = receiveLoRaPacket();
        // Print received data to Serial Monitor
        Serial.print("Received packet: ");
        Serial.println(data);
        Serial.print("RSSI: ");
        Serial.println(LoRa.packetRssi());
        Serial.print("SNR: ");
        Serial.println(LoRa.packetSnr());
    }
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

String receiveLoRaPacket() {
    String recv = "";
    while (LoRa.available()) {
        recv += (char)LoRa.read();
    }
    return recv;
}
