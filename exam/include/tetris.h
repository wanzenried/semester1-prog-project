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
  vec2D shape[4];
  vec2D offset;
} piece;

bool movePiece(piece *p, vec2D dir);
bool rotatePiece(piece *p ,vec2D rot);
bool newPiece(piece *p);
void drawShape(piece *p);
void removeShape(piece *p);
uint8_t lineClear();

#endif