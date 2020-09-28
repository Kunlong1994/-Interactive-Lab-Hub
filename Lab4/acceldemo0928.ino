// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
// include the library code:
#include <LiquidCrystal.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int redPin = 8; 
int greenPin = 9;
int bluePin = 10;

int r;
int g;
int b;


void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  /*
  lcd.print("X:  "); lcd.print(lis.x); 
  lcd.print("Y:  "); lcd.print(lis.y); 
  lcd.print("Z:  "); lcd.print(lis.z); 
  */
  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  accX = event.acceleration.x
  accY = event.acceleration.y
  accZ = event.acceleration.z
  if (accZ > accY && accZ > accX) {
    setColor(0, 255, 0); 
  }
  else if (accY > accZ && accY > accX) {
    setColor(255, 0, 0);  
  }
  else if (accX > accZ && accX > accY) {
    setColor(0, 0, 255);  
  }
  else {
    setColor(255, 255, 255); 
  }
  /* Display the results (acceleration is measured in m/s^2) */
  lcd.print("X: "); lcd.print(accX);
  lcd.setCursor(8,0);   //set cursor position
  lcd.print("Y: "); lcd.print(accY);
  lcd.setCursor(0,1) ; //set cursor position
  lcd.print("Z: "); lcd.print(accZ); 
  lcd.setCursor(0,0);  //set cursor position
  lcd.println(" m/s^2 ");

 
  delay(2000); 
  lcd.clear();
}


void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
