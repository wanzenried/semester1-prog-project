#include <tetris.h>


bool newPiece(piece *p, uint16_t *pixels)
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

  drawShape(p, pixels);
  return true;
}


void drawShape(piece *p, uint16_t *pixels)
{
  for (int i = 0; i < 4; i++)
  {
    drawPixel(p->shape[i].x + p->offset.x, p->shape[i].y + p->offset.y, pixels);
  }
}

void removeShape(piece *p, uint16_t *pixels)
{
  for (int i = 0; i < 4; i++)
  {
    clearPixel(p->shape[i].x + p->offset.x, p->shape[i].y + p->offset.y, pixels);
  }
}

bool movepiece(piece *p, vec2D dir, uint16_t *pixels)
{
  removeShape(p, pixels);
  //  check if there is already pixels in the new location
  for (int i = 0; i < 4; i++)
  {
    int8_t nX = p->shape[i].x + p->offset.x + dir.x;
    int8_t nY = p->shape[i].y + p->offset.y + dir.y;

    if((pixels[nY]>>(nX+1)) &1 ){
      drawShape(p, pixels);
      return false;
    }
  }

  p->offset.x += dir.x;
  p->offset.y += dir.y;

  drawShape(p, pixels);
  return true;
}

bool rotatePiece(piece *p, vec2D rot, uint16_t *pixels)
{
  vec2D newPos[4];

  removeShape(p, pixels);
  for (int i = 0; i < 4; i++)
  {
    newPos[i].x = p->shape[i].y * rot.x;
    newPos[i].y = p->shape[i].x * rot.y;

    int8_t nX = newPos[i].x + p->offset.x;
    int8_t nY = newPos[i].y + p->offset.y;

    if((pixels[nY]>>(nX+1)) &1 )
    {
      drawShape(p, pixels);
      return false;
    }
  }

  for (int i = 0; i < 4; i++)
  {
    p->shape[i] = newPos[i];
  }

  drawShape(p, pixels);
  return true;
}

uint8_t lineClear(uint16_t *pixels)
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