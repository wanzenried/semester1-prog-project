#include <tetris.h>


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

    if(checkPixel(nX ,nY)){
      return false;
    }
  }

  drawShape(p);
  return true;
}


void drawShape(piece *p)
{
  for (int i = 0; i < 4; i++)
  {
    drawPixel(p->shape[i].x + p->offset.x, p->shape[i].y + p->offset.y);
  }
}

void removeShape(piece *p)
{
  for (int i = 0; i < 4; i++)
  {
    clearPixel(p->shape[i].x + p->offset.x, p->shape[i].y + p->offset.y);
  }
}

bool movepiece(piece *p, vec2D dir)
{
  removeShape(p);
  //  check if there is already pixels in the new location
  for (int i = 0; i < 4; i++)
  {
    int8_t nX = p->shape[i].x + p->offset.x + dir.x;
    int8_t nY = p->shape[i].y + p->offset.y + dir.y;

    if(checkPixel(nX ,nY)){
      drawShape(p);
      return false;
    }
  }

  p->offset.x += dir.x;
  p->offset.y += dir.y;

  drawShape(p);
  return true;
}

bool rotatePiece(piece *p, vec2D rot)
{
  vec2D newPos[4];

  removeShape(p);
  for (int i = 0; i < 4; i++)
  {
    newPos[i].x = p->shape[i].y * rot.x;
    newPos[i].y = p->shape[i].x * rot.y;

    int8_t nX = newPos[i].x + p->offset.x;
    int8_t nY = newPos[i].y + p->offset.y;

    if(checkPixel(nX, nY))
    {
      drawShape(p);
      return false;
    }
  }

  for (int i = 0; i < 4; i++)
  {
    p->shape[i] = newPos[i];
  }

  drawShape(p);
  return true;
}

uint8_t lineClear()
{
  uint8_t count = 0;
  for (int i = lcdCols; i > 1; i--)
  {
    if (pixelArr[i] == 0x2001)
    {
      break;
    }
    
    while (pixelArr[i] == 0x3FFF)
    {
      count++;
      for (int j = i; j > 0; j--)
      {
        pixelArr[j] = pixelArr[j-1];
        if (pixelArr[j] == 0x2001)
        {
          break;
        }
        
      }
      
    }
  }
  if (count > 0)
  {
    drawAllPixels();
  }
  

  return count;
  
}