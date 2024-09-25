#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  /* OLED DISPLAY WIDTH, IN PIXELS */ 
#define SCREEN_HEIGHT 64  /* OLED DISPLAY HEIGHT, IN PIXELS */ 

#define OLED_RESET -1     /* RESET PIN NOT USED */ 
#define SCREEN_ADDRESS 0x3C /* I2C ADDRESS FOR 128x64 OLED */ 

#define LIGHT_SENSOR_PIN 35 // ESP32 pin GIOP35 (ADC0)

/* CREATE AN INSTANCE OF THE SSD1306 DISPLAY */ 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  /* INITIALIZE THE DISPLAY */
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); /* INFINITE LOOP */
  }

  display.clearDisplay(); /* CLEAR THE DISPLAY BUFFER */
  display.setTextSize(1); /* SET TEXT SIZE TO 1 */
  display.setTextColor(SSD1306_WHITE); /* SET TEXT COLOR TO WHITE */
  display.setCursor(0, 10); /* SET CURSOR POSITION (X, Y) */
  
  display.println(F("Light Sensor Reading"));
  display.display(); /* DISPLAY THE INITIAL TEXT ON THE SCREEN */
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  /* DISPLAY THE RAW ANALOG VALUE ON SERIAL MONITOR */
  Serial.print("Analog Value: ");
  display.println(F("Analog Value:"));

  /* DETERMINE AND DISPLAY THE LIGHT LEVEL */
  display.clearDisplay(); /* CLEAR THE DISPLAY BUFFER */
  display.setCursor(0, 10); /* RESET CURSOR POSITION */
  
  if (analogValue < 1400) {
    Serial.println(" => DARK");
    display.print(F(analogValue));
    display.println(F(" DARK"));
    
  } else if (analogValue < 1900) {
    Serial.println(" => DIM");
    display.println(F(" DIM"));
  } else if (analogValue < 3000) {
    Serial.println(" => LIGHT");
    display.println(F(" LIGHT"));
  } else if (analogValue < 3700) {
    Serial.println(" => BRIGHT");
    display.println(F(" BRIGHT"));
  } else {
    Serial.println(" => VERY BRIGHT");
    display.println(F(" VERY BRIGHT"));
  }

  display.display(); /* UPDATE THE DISPLAY WITH THE NEW LIGHT LEVEL */
  delay(500);
}
