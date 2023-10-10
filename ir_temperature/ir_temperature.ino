#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobot_MLX90614.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DFRobot_MLX90614_I2C sensor;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  else {
    Serial.println("SSD1306 started...");
  }
  
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for a second

  // Clear the buffer
  display.clearDisplay();
  delay(100);
}

void loop() {
  displayTemp();
  delay(400);
}

void displayTemp(){
  display.clearDisplay();
  display.setTextSize(3);             // Large pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(10,10);
  display.print(String(readTemp(true)));
  display.setTextSize(1);             // Small pixel scale
  display.print(F("F"));
  display.display();
}

float readTemp(bool f){
  float temp=0;
  if (f){
    temp = (sensor.getObjectTempCelsius()*1.8)+32;//convert celcius to fahrenheit
  }
  else {
    temp = sensor.getObjectTempCelsius();
  }
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println(" F");
  return (temp);
}
