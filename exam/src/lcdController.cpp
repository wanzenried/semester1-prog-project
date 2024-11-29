#include <lcdController.h>

#include <customChars.h>

uint16_t pixelArr[lcdCols + 2];

//const uint8_t lcdAddr = 0x27;
LiquidCrystal_I2C lcd(lcdAddr, lcdCols, lcdRows);

void lcdSetup()
{
    lcd.init();
    lcd.backlight();
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
    x++;    // skipping buffer row
    return (pixelArr[y]>>x) &1;
}

void updatePixelGroup(uint8_t x, uint8_t y)
{
    uint8_t lcdX = x/3;
    uint8_t lcdY = lcdCols-y;
    lcd.setCursor(lcdY, lcdX);

    uint8_t val = (pixelArr[y] >> ((lcdX *3)+1)) & 0b111;
    lcd.write(val);
}

void drawAllPixels()
{
    lcd.clear();
    for (uint8_t x = 0; x < 4; x++)
    {
        lcd.setCursor(0, x);
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