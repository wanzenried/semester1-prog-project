#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const uint8_t lButton = 7;
const uint8_t mButton = 9;
const uint8_t rButton = 11;

bool debounceButtonl();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hello world");
  pinMode(lButton, INPUT);
  pinMode(mButton, INPUT);
  pinMode(rButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(debounceButtonl())
  {
    Serial.println("button pressed");
  }
  delay(1);
}

bool debounceButtonl()
{
  static uint16_t buttonstate = 0;
  buttonstate = (buttonstate << 1) | (digitalRead(lButton));

  return (buttonstate == 0x00FF);
}