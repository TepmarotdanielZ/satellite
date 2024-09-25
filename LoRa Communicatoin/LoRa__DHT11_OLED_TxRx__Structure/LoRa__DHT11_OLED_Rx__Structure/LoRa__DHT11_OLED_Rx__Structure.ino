
#include <LoRa.h>  
#include "LoRaBoards.h"  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  

#define SCREEN_WIDTH 128  /* OLED DISPLAY WIDTH, IN PIXELS */  
#define SCREEN_HEIGHT 64  /* OLED DISPLAY HEIGHT, IN PIXELS */  
#define OLED_RESET -1     /* RESET PIN NOT USED */  
#define SCREEN_ADDRESS 0x3C /* I2C ADDRESS FOR 128x64 OLED */  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  

/* STRUCTURE TO HOLD THE DATA */ 

  struct LoRaData {  
      int counter;  
      float temperature;  
      float humidity;  
  };  

void setup() {  
    Serial.begin(115200);  

    /* INITIALIZE OLED DISPLAY */ 
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  
        Serial.println(F("SSD1306 allocation failed"));  
        for (;;);  /* STOP IF OLED INITIALIZATION FAILS */   
    }  
    display.clearDisplay();  
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE);  
    display.setCursor(0, 10);  
    display.println(F("LoRa DHT11 Rx"));  
    display.display();  
    delay(1500);  

    setupBoards();  
    delay(1500);  

#ifdef  RADIO_TCXO_ENABLE  
    pinMode(RADIO_TCXO_ENABLE, OUTPUT);  
    digitalWrite(RADIO_TCXO_ENABLE, HIGH);  
#endif  

    Serial.println("LoRa Receiver");  
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DIO0_PIN);  
    if (!LoRa.begin(LORA_FREQ_CONFIG)) {  
        Serial.println("Starting LoRa failed!");  
        while (1);  
    }  

    /* DISPLAY WAITING MESSAGE */

      display.setCursor(0, 10);  
      display.println(F("Waiting for packets..."));  
      display.display();  
}  

void loop() {  
    int packetSize = LoRa.parsePacket();  
    if (packetSize) {  

        /* RECIEVED A PACKET */ 

           Serial.println("Received packet: ");  

        /* CREATE A BUFFER FOR INCOMING DATA */ 

          LoRaData receivedData;  
          LoRa.readBytes((uint8_t*)&receivedData, sizeof(receivedData)); // Read into struct  

          Serial.print("Counter: ");  
          Serial.println(receivedData.counter);  
          Serial.print("Temperature: ");  
          Serial.print(receivedData.temperature);  
          Serial.println(" °C");  
          Serial.print("Humidity: ");  
          Serial.print(receivedData.humidity);  
          Serial.println(" %");  

        /* DISPLAY RECEIVED PACKET ON OLED */  

          display.clearDisplay();  
          display.setCursor(0, 10);  
          display.println(F("Received packet:"));  
          display.print("Counter: ");  
          display.println(receivedData.counter);  
          display.print("Temp: ");  
          display.println(receivedData.temperature);  
          display.print("°C");  
          display.print("Humidity: ");  
          display.println(receivedData.humidity);  
          display.println("%");  
          display.display();  

         /* PRINT RSSI OF PACKET */  

          Serial.print("RSSI: ");  
          Serial.println(LoRa.packetRssi());  

        /* SHOW RSSI ON OLED */  

          display.setCursor(0, 50);  
          display.print(F("RSSI: "));  
          display.println(LoRa.packetRssi());  
          display.display();  
    }  
}



