//  Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//  self written Libraries
#include <debounce.h>

//  other files
#include <lcdController.h>


typedef struct vec2D
{
  float x;
  float y;
} vec2D;

typedef struct piece
{
  vec2D shape[4];
  vec2D offset;
} piece;

void drawShape();
void removeShape();
bool movepiece(piece *p, vec2D dir);
bool rotatePiece(piece *p, vec2D rot);
bool newPiece(piece *p);
uint8_t lineClear();


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
  Serial.begin(9600);
  lcdSetup();
  randomSeed(analogRead(0));

  for (int i = 0; i < 20; i++)
  {
    pixels[i] = 0x2001;
  }
  pixels[20] = 0xffff;

  drawShape();
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
        while (true){}
        
      }
    }
  }
  
  delay(1);
}

bool newPiece(piece *p)
{

  switch (random(0,7))
  {
  case 0:
    p->offset = {6,2};
    p->shape[0] = {-1,0};
    p->shape[1] = {0,0};
    p->shape[2] = {0,1};
    p->shape[3] = {1,1};
    break;
  case 1:
    p->offset = {6,2};
    p->shape[0] = {-1,1};
    p->shape[1] = {0,1};
    p->shape[2] = {0,0};
    p->shape[3] = {1,0};
    break;
  case 2:
    p->offset = {6,2};
    p->shape[0] = {-1,0};
    p->shape[1] = {-1,1};
    p->shape[2] = {0,0};
    p->shape[3] = {1,0};
    break;
  case 3:
    p->offset = {6,2};
    p->shape[0] = {-1,0};
    p->shape[1] = {0,0};
    p->shape[2] = {1,0};
    p->shape[3] = {1,1};
    break;
  case 4:
    p->offset = {6,2};
    p->shape[0] = {-1,0};
    p->shape[1] = {0,0};
    p->shape[2] = {0,1};
    p->shape[3] = {1,0};
    break;
  case 5:
    p->offset = {5.5,2.5};
    p->shape[0] = {-0.5,-0.5};
    p->shape[1] = {-0.5,0.5};
    p->shape[2] = {0.5,-0.5};
    p->shape[3] = {0.5,0.5};
    break;
  case 6:
    p->offset = {4.5,1.5};
    p->shape[0] = {-1.5,0.5};
    p->shape[1] = {-0.5,0.5};
    p->shape[2] = {0.5,0.5};
    p->shape[3] = {1.5,0.5};
    break;
    
  default:
    break;
  }

  for (int i = 0; i < 4; i++)
  {
    int8_t nX = p->shape[i].x + p->offset.x;
    int8_t nY = p->shape[i].y + p->offset.y;

    if((pixels[nY]>>(nX+1)) &1 ){
      return false;
    }
  }

  drawShape();
  return true;
}

void drawShape()
{
  for (int i = 0; i < 4; i++)
  {
    drawPixel(p.shape[i].x + p.offset.x, p.shape[i].y + p.offset.y, pixels);
  }
}

void removeShape()
{
  for (int i = 0; i < 4; i++)
  {
    clearPixel(p.shape[i].x + p.offset.x, p.shape[i].y + p.offset.y, pixels);
  }
}

bool movepiece(piece *p, vec2D dir)
{
  removeShape();
  //  check if there is already pixels in the new location
  for (int i = 0; i < 4; i++)
  {
    int8_t nX = p->shape[i].x + p->offset.x + dir.x;
    int8_t nY = p->shape[i].y + p->offset.y + dir.y;

    if((pixels[nY]>>(nX+1)) &1 ){
      drawShape();
      return false;
    }
  }

  p->offset.x += dir.x;
  p->offset.y += dir.y;

  drawShape();
  return true;
}

bool rotatePiece(piece *p, vec2D rot)
{
  vec2D newPos[4];

  removeShape();
  for (int i = 0; i < 4; i++)
  {
    newPos[i].x = p->shape[i].y * rot.x;
    newPos[i].y = p->shape[i].x * rot.y;

    int8_t nX = newPos[i].x + p->offset.x;
    int8_t nY = newPos[i].y + p->offset.y;

    if((pixels[nY]>>(nX+1)) &1 )
    {
      drawShape();
      return false;
    }
  }

  for (int i = 0; i < 4; i++)
  {
    p->shape[i] = newPos[i];
  }

  drawShape();
  return true;
}

uint8_t lineClear()
{
  uint8_t count = 0;
  for (int i = 19; i > 0; i--)
  {
    if (pixels[i] == 0x2001)
    {
      break;
    }
    
    while (pixels[i] == 0x3FFF)
    {
      count++;
      for (int j = i; j > 0; j--)
      {
        pixels[j] = pixels[j-1];
        if (pixels[j] == 0x2001)
        {
          break;
        }
        
      }
      
    }
  }
  if (count > 0)
  {
    drawAllPixels(pixels);
  }
  

  return count;
  
}