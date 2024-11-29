//  Libraries
#include <Arduino.h>

//  my Libraries
#include <debounce.h>

//  other files
#include <lcdController.h>
#include <tetris.h>

//  function prototypes
void gameSetup();
void getInput();
void doGameLoop();

//  Global variables
debounceBtn lBtn(7);
debounceBtn mBtn(9);
debounceBtn rBtn(11);

const unsigned long dropDelay = 400;
unsigned long lastTimer = 0;

uint16_t score;

piece p;

void setup() {
  // put your setup code here, to run once:
  lcdSetup();
  randomSeed(analogRead(0));
  gameSetup();
}

void loop() {
  getInput();

  if (millis() - lastTimer > dropDelay)
  {
    lastTimer = millis();
    doGameLoop();
  }
  delay(1);
}

//  Initialize the pixelarray, with pixels "set" in the buffer areas
//  reset score and timer, and create a new falling piece
void gameSetup()
{
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

void getInput()
{
  if(lBtn.pressed())
  {
    movePiece(&p, {-1,0});
  }

  if(mBtn.pressed())
  {
    rotatePiece(&p, {-1,1});
  }

  if(rBtn.pressed())
  {
    movePiece(&p, {1,0});
  }
}

void doGameLoop()
{
  //  move the dropping piece down 1 pixel
  if(movePiece(&p, {0,1}))
  {
    return;
  }

  //  if dropping piece could not be moved down, check if any lines were cleared
  //  and try to create a new piece
  score += lineClear();
  if(newPiece(&p))
  {
    return;
  }

  //  if it was not possible to create a new piece, end the game
  showScore(score);
  while (!mBtn.pressed()){}
  gameSetup();
}