

#include <LoRa.h>  
#include "LoRaBoards.h"  
#include "DHT.h"  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  

#define DHTPIN 13  
#define DHTTYPE DHT11  

#define SCREEN_WIDTH 128  /* OLED DISPLAY WIDTH, IN PIXELS */ 
#define SCREEN_HEIGHT 64  /* OLED DISPLAY HEIGHT, IN PIXELS */ 
#define OLED_RESET -1     /* RESET PIN NOT USED */ 
#define SCREEN_ADDRESS 0x3C  /* I2C ADDRESS FOR 128x64 OLED */

DHT dht(DHTPIN, DHTTYPE);  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  
int counter = 0;  

/* STRUCTURE TO HOLD THE DATA */ 

  struct LoRaData {  
      int counter;  
      float temperature;  
      float humidity;  
  };  

void setup() {  
    Serial.begin(115200);  
    dht.begin();  
  
  /* INITIALIZE OLED DISPLAY */
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  
        Serial.println(F("SSD1306 allocation failed"));  
        while(1);  /* STOP IF OLED INITIALIZATION FAILS */
    }  

    display.clearDisplay();  
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE);  
    display.setCursor(0, 10);  
    display.println(F("LoRa DHT11 Tx"));  
    display.display();  
    delay(1500);  

    setupBoards();  
    delay(1500);  

#ifdef RADIO_TCXO_ENABLE  
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);  
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);  
#endif  

    Serial.println("LoRa Sender with DHT11");  
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);  
    if (!LoRa.begin(LORA_FREQ_CONFIG)) {  
        Serial.println("Starting LoRa failed!");  
        display.clearDisplay();  
        display.setCursor(0, 10);  
        display.println(F("LoRa Failed!"));  
        display.display();  
        while (1);  
    }  
}  

void loop() {  
    float h = dht.readHumidity();  
    float t = dht.readTemperature();  
    
    if (isnan(h) || isnan(t)) {  
        Serial.println(F("Failed to read from DHT sensor!"));  
        display.clearDisplay();  
        display.setCursor(0, 10);  
        display.println(F("DHT Fail"));  
        display.display();  
        return;  
    }  

    /* CREATE THE DATA STRUCTURE */ 

      LoRaData dataToSend;  
      dataToSend.counter = counter;  
      dataToSend.temperature = t;  
      dataToSend.humidity = h;  

      Serial.print("Sending packet: ");  
      Serial.print(dataToSend.counter);  
      Serial.print(" | Temp: ");  
      Serial.print(dataToSend.temperature);  
      Serial.print(" °C, Humidity: ");  
      Serial.println(dataToSend.humidity);  

      LoRa.beginPacket();  
      LoRa.write((uint8_t*)&dataToSend, sizeof(dataToSend)); /* SEND STRUCTURE AS BYTE ARRAY */ 
      LoRa.endPacket();  

    /*  DISPLAY ON OLED TX  */ 

      display.clearDisplay();  
      display.setCursor(0, 10);  
      display.print("Sending: ");  
      display.print(dataToSend.counter);  
      display.setCursor(0, 20);  
      display.print("Temp: ");  
      display.print(dataToSend.temperature);  
      display.print(" C");  
      display.setCursor(0, 30);  
      display.print("Humidity: ");  
      display.print(dataToSend.humidity);  
      display.println(" %");  
      display.display();  

      counter++;  
      delay(2000);  
}


