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

bool movepiece(piece *p, vec2D dir, uint16_t *pixels);
bool rotatePiece(piece *p, vec2D rot, uint16_t *pixels);
bool newPiece(piece *p, uint16_t *pixels);
void drawShape(piece *p, uint16_t *pixels);
void removeShape(piece *p, uint16_t *pixels);
uint8_t lineClear(uint16_t *pixels);

#endif