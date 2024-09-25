
/* LoRa DHT11 Tx */
/* TESS: 21.09.2024 */
/* ONLY SUPPORTS SX1276/SX1278 */  

#include <LoRa.h>
#include "LoRaBoards.h"
#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int counter = 0;

void setup()
{
    Serial.begin(115200);
    dht.begin();

    setupBoards();
    delay(1500);

#ifdef  RADIO_TCXO_ENABLE
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);
#endif

    Serial.println("LoRa Sender with DHT11");
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);
    if (!LoRa.begin(LORA_FREQ_CONFIG)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    Serial.print("Sending packet: ");
    Serial.print(counter);
    Serial.print(" | Temp: ");
    Serial.print(t);
    Serial.print(" °C, Humidity: ");
    Serial.println(h);

    // Send packet
    LoRa.beginPacket();
    LoRa.print("Counter: ");
    LoRa.print(counter);
    LoRa.print(" | Temp: ");
    LoRa.print(t);
    LoRa.print(" °C, Humidity: ");
    LoRa.print(h);
    LoRa.println(" %");
    LoRa.endPacket();

    if (u8g2) {
        char buf[256];
        u8g2->clearBuffer();
        snprintf(buf, sizeof(buf), "Sending: %d", counter);
        u8g2->drawStr(0, 12, "Transmitting: OK!");
        u8g2->drawStr(0, 30, buf);
        u8g2->sendBuffer();
    }

    counter++;
    delay(2000);
}

