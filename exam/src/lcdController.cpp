#include <lcdController.h>

#include <customChars.h>

uint16_t pixelArr[lcdCols + 2];

LiquidCrystal_I2C lcd(lcdAddr, lcdCols, lcdRows);

void lcdSetup()
{
    lcd.init();
    lcd.backlight();

    //  Load in custom characters from customChars.h
    for (uint8_t i = 0; i < 8; i++)
    {
        lcd.createChar(i, customChars[i]);
    }
}

void drawPixel(uint8_t x, uint8_t y)
{
    y++;    // skipping buffer row
    pixelArr[y] = pixelArr[y] | (1<<(x+1));
    updatePixelGroup(x,y);
}

void clearPixel(uint8_t x, uint8_t y)
{
    y++;    // skipping buffer row
    pixelArr[y] = pixelArr[y] & ~(1<<(x+1));
    updatePixelGroup(x,y);
}

bool checkPixel(uint8_t x, uint8_t y)
{
    y++;    // skipping buffer row
    x++;    // skipping buffer column
    return (pixelArr[y]>>x) &1;
}

void updatePixelGroup(uint8_t x, uint8_t y)
{
    uint8_t lcdX = x/3;
    uint8_t lcdY = lcdCols-y;
    lcd.setCursor(lcdY, lcdX);

    uint8_t val = (pixelArr[y] >> ((lcdX *3)+1)) & 0b111;   //  Indexing into the pixel array (see visualization in lcdController.h), and using a bitmask to get 3 bit value corresponding to the correct custom character 
    lcd.write(val);
}

void drawAllPixels()
{
    lcd.clear();
    for (uint8_t x = 0; x < lcdRows; x++)
    {
        lcd.setCursor(0, x);
        //  counting "backwards", because lcd 0,0 is different to pixel array 0,0
        for (int8_t y = lcdCols; y > 0; y--)
        {
            uint8_t val = (pixelArr[y] >> ((x*3)+1)) & 0b111;
            lcd.write(val);
        }
    }
}

void showScore(uint16_t score)
{
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("Game over");
    lcd.setCursor(6,2);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.setCursor(6,3);
    lcd.print("Press blue");
}