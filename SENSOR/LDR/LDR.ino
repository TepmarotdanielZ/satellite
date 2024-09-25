#define LIGHT_SENSOR_PIN 35 // ESP32 pin GIOP36 (ADC0)

void setup() {
  /* SERIAL PRINT */ 

  Serial.begin(9600);
}

void loop() {
  
  /* READS THE INPUT ON ANALOG PIN (VALUE BETWEEN 0 TO 4095) */ 

    int analogValue = analogRead(LIGHT_SENSOR_PIN);

    Serial.print("Analog Value : ");
    Serial.print(analogValue);   /* THE RAW ANALOG READING */ 

  /* WE'LL HAVE A FEW THRESHOLDS, QUALITATIVELY DETERMINED */

    if (analogValue < 1400) {
      Serial.println(" => DARK"); 
    } else if (analogValue < 1900) {
      Serial.println(" => DIM");
    } else if (analogValue < 3000) {
      Serial.println(" => LIGHT");
    } else if (analogValue < 3700) {
      Serial.println(" => BRIGHT"); 
    } else {
      Serial.println(" => VERY BRIGHT");
    }

    delay(500);
}
