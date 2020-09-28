
#define rLedPin 6 
#define gLedPin 5 
#define bLedPin 3 

#define FSRPin A0  
#include <EEPROM.h>
int ledR  = 0; 
int ledG  = 0; 
int ledB  = 0; 
int addr = 0;

int FSRReading; 
 
void setup() {
  
  pinMode(rLedPin, OUTPUT);
  pinMode(gLedPin, OUTPUT);
  pinMode(bLedPin, OUTPUT);

  
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Pressuredetected light.");
}
 
void loop() {
  FSRReading = analogRead(FSRPin); 
  
  if(FSRReading <= 300){ 
    lightOn(1);                                 
  } else {                                      
    lightOn(0);                               
  }

  EEPROM.write(addr, FSRReading);
   
    addr = addr + 1;
    if (addr == EEPROM.length()) {
      addr = 0;
    }
   
    delay(500);
  }
 

void lightOn(bool on){   
  if (on == 1) {
    analogWrite(rLedPin, ledR);
    delay(100);
    analogWrite(gLedPin, ledG);
    delay(100);
    analogWrite(bLedPin, ledB); 
    delay(100); 
  }  else {  
    analogWrite(rLedPin, 255);
    delay(10);
    analogWrite(gLedPin, 255);
    delay(10);
    analogWrite(bLedPin, 255); 
    delay(10);     
  }
}
