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

//  array for storing pixels on the screen
uint16_t pixels[20];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hello world");
  lcdSetup();

  for (uint8_t i = 0; i < 20; i++)
  {
    for (uint8_t j = 0; j < 12; j++)
    {
      drawPixel(j, i, pixels);
      delay(25);
    }
    
  }

  for (uint8_t i = 0; i < 20; i++)
  {
    for (uint8_t j = 0; j < 12; j++)
    {
      clearPixel(j, i, pixels);
      delay(25);
    }
    
  }


  
}

int counterA = 0;
int counterB = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(lBtn.pressed())
  {
    drawPixel(6, counterA, pixels);
    counterA++;
  }

  if(rBtn.pressed())
  {
    drawPixel(7,counterB, pixels);
    counterB++;
  }
  delay(1);
}
