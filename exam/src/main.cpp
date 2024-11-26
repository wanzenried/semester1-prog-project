//  Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//  self written Libraries
#include <debounce.h>

//  other files
#include <lcdController.h>


//  Defines

//  Global variables
debounceBtn lBtn(7);
debounceBtn mBtn(9);
debounceBtn rBtn(11);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hello world");
  lcdSetup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(lBtn.pressed())
  {
    Serial.println("button pressed");
  }
  delay(1);
}
