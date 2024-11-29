//  Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//  self written Libraries
#include <debounce.h>

//  other files
#include <lcdController.h>
#include <tetris.h>

//  Defines

//  Global variables
debounceBtn lBtn(7);
debounceBtn mBtn(9);
debounceBtn rBtn(11);

//  array for storing pixels on the screen
uint16_t pixels[21];

const unsigned long dropDelay = 500;
unsigned long lastTimer = 0;

uint16_t score = 0;


piece p = {{{-1.5,0.5}, {-0.5,0.5}, {0.5,0.5}, {1.5,0.5}}, {2.5,-0.5}};



void setup() {
  // put your setup code here, to run once:
  lcdSetup();
  randomSeed(analogRead(0));

  for (int i = 0; i < 20; i++)
  {
    pixels[i] = 0x2001;
  }
  pixels[20] = 0xffff;

  drawShape(&p, pixels);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(lBtn.pressed())
  {
    movepiece(&p, {-1,0}, pixels);
  }

  if(mBtn.pressed())
  {
    rotatePiece(&p, {-1,1}, pixels);
  }

  if(rBtn.pressed())
  {
    movepiece(&p, {1,0}, pixels);
  }
  

  if (millis() - lastTimer > dropDelay)
  {
    lastTimer = millis();
  
    if(!movepiece(&p, {0,1}, pixels))
    {
      score += lineClear(pixels);
      if(!newPiece(&p, pixels))
      {
        showScore(score);
        while (true){}
        
      }
    }
  }
  
  delay(1);
}

