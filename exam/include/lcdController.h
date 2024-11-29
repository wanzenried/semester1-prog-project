#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void lcdSetup();
void drawAllPixels(uint16_t *pixels);
void drawPixel(uint8_t x, uint8_t y, uint16_t *pixelArr);
void clearPixel(uint8_t x, uint8_t y, uint16_t *pixelArr);
void updatePixelGroup(uint8_t x, uint8_t y, uint16_t *pixelArr);
void showScore(uint16_t score);

#endif