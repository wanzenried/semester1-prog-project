#ifndef TETRIS_H
#define TETRIS_H

#include <Arduino.h>
#include <lcdController.h>

typedef struct vec2D
{
  float x;
  float y;
} vec2D;

typedef struct tetrisPiece
{
  vec2D shape[4];     //  array to store the shape of the piece. Centered around 0,0 for easy rotation
  vec2D offset;       //  offset vector is added to each part of the shape, to get correct location
} tPiece;

bool movePiece(tPiece *p, vec2D dir);
bool rotatePiece(tPiece *p ,vec2D rot);
bool newPiece(tPiece *p);
void drawShape(tPiece *p);
void removeShape(tPiece *p);
uint8_t lineClear();

#endif