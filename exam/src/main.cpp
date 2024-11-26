//  Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//  self written Libraries
#include <debounce.h>


//global variables
debounceBtn lBtn(7);
debounceBtn mBtn(9);
debounceBtn rBtn(11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hello world");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(lBtn.pressed())
  {
    Serial.println("button pressed");
  }
  delay(1);
}
