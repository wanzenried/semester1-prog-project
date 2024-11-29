#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define lcdAddr 0x27
#define lcdCols 20
#define lcdRows 4

//  Visualisation of structure in pixel array

//   BBB BBB BBB BBB BBB B
//   BBB PPP PPP PPP PPP B
//   BBB PPP PPP PPP PPP B
//   BBB PPP PPP PPP PPP B
//   BBB PPP PPP PPP PPP B


//  array for storing pixel values                                          
//  display is 20x4 characters and each char can show 3 "pixels"            
//  therefore 12 bits to store pixel values                                 
//  there is one buffer value above and below the actual pixel values       
//  aswell as one buffer bit to the right and 3 buffer bits to the left     
extern uint16_t pixelArr[lcdCols + 2];

void lcdSetup();
void drawAllPixels();
void drawPixel(uint8_t x, uint8_t y);
void clearPixel(uint8_t x, uint8_t y);
bool checkPixel(uint8_t x, uint8_t y);
void updatePixelGroup(uint8_t x, uint8_t y);
void showScore(uint16_t score);

#endif