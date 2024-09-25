
#include <Wire.h>  
#include <Adafruit_Sensor.h>  
#include <Adafruit_BMP280.h>  

Adafruit_BMP280 bmp; /* I2C, SDA PIN: 21,  SCL PIN: 22 */  

void setup() {  
  Serial.begin(115200);  
  Serial.println("BMP280 test");  

  // Initialize the BMP280 sensor  
  if (!bmp.begin(0x76)) { /* DEFAULT I2C ADDRESS FOR BMP280 */ 
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));  
    while (1) delay(10);  
  }  
}  

void loop() {  
  /* READING TEMPERATURE AND PRESSURE */ 

  float temperature = bmp.readTemperature();  
  float pressure = bmp.readPressure();  

  /* PRINT THE RESULTS TO THE SERIAL MONITOR */ 

  Serial.print("TEMPERATURE : ");  
  Serial.print(temperature);  
  Serial.print(" *C ");  

  Serial.print("| PRESSURE : ");  
  Serial.print(pressure / 100.0F); /* CONVERT Pa TO hPa */   
  Serial.println(" hPa");  

  delay(200);  
}