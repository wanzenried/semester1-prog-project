#ifndef TETRIS_H
#define TETRIS_H

#include <Arduino.h>
#include <lcdController.h>

typedef struct vec2D
{
  float x;
  float y;
} vec2D;

typedef struct piece
{
  vec2D shape[4];     //  array to store the shape of the piece. Centered around 0,0 for easy rotation
  vec2D offset;       //  offset vector is added to each part of the shape, to get correct location
} piece;

bool movePiece(piece *p, vec2D dir);
bool rotatePiece(piece *p ,vec2D rot);
bool newPiece(piece *p);
void drawShape(piece *p);
void removeShape(piece *p);
uint8_t lineClear();

#endif