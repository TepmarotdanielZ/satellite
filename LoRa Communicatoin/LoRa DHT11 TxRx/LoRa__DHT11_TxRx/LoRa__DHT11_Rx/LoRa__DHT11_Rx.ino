
/* LoRa DHT11 Rx */
/* TESS: 21.09.2024 */
/* ONLY SUPPORTS SX1276/SX1278 */ 


#include <LoRa.h>
#include "LoRaBoards.h"

void setup()
{
    Serial.begin(115200);
    setupBoards();
    delay(1500);

    Serial.println("LoRa Receiver");

#ifdef  RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(LORA_FREQ_CONFIG)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // Received a packet
        Serial.print("Received packet: ");

        String recv = "";
        while (LoRa.available()) {
            recv += (char)LoRa.read();
        }

        Serial.println(recv);

        // Print RSSI of packet
        Serial.print("RSSI: ");
        Serial.println(LoRa.packetRssi());

        if (u8g2) {
            u8g2->clearBuffer();
            u8g2->drawStr(0, 12, "Received OK!");
            u8g2->drawStr(0, 26, recv.c_str());
            char buf[256];
            snprintf(buf, sizeof(buf), "RSSI:%i", LoRa.packetRssi());
            u8g2->drawStr(0, 40, buf);
            snprintf(buf, sizeof(buf), "SNR:%.1f", LoRa.packetSnr());
            u8g2->drawStr(0, 56, buf);
            u8g2->sendBuffer();
        }
    }
}
