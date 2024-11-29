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


const unsigned long dropDelay = 500;
unsigned long lastTimer = 0;

uint16_t score;

piece p;



void setup() {
  // put your setup code here, to run once:
  lcdSetup();
  randomSeed(analogRead(0));

  pixelArr[0] = 0xffff;
  for (int i = 0; i < lcdCols; i++)
  {
    pixelArr[i+1] = 0x2001;
  }
  pixelArr[lcdCols+1] = 0xffff;

  newPiece(&p);
  score = 0;
  lastTimer = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(lBtn.pressed())
  {
    movepiece(&p, {-1,0});
  }

  if(mBtn.pressed())
  {
    rotatePiece(&p, {-1,1});
  }

  if(rBtn.pressed())
  {
    movepiece(&p, {1,0});
  }
  

  if (millis() - lastTimer > dropDelay)
  {
    lastTimer = millis();
  
    if(!movepiece(&p, {0,1}))
    {
      score += lineClear();
      if(!newPiece(&p))
      {
        showScore(score);
        while (!mBtn.pressed()){}
        setup();
      }
    }
  }
  
  delay(1);
}

