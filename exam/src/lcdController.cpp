#include <lcdController.h>

#include <customChars.h>

const uint8_t lcdAddr = 0x27;


LiquidCrystal_I2C lcd(lcdAddr,20,4);

void lcdSetup()
{
    lcd.init();
    lcd.backlight();
    for (uint8_t i = 0; i < 8; i++)
    {
        lcd.createChar(i, customChars[i]);
    }

    

    
}

void drawPixel(uint8_t x, uint8_t y, uint16_t *pixelArr)
{
    Serial.println(pixelArr[y],BIN);
    pixelArr[y] = pixelArr[y] | (1<<x);
    Serial.println(pixelArr[y],BIN);

    updatePixelGroup(x,y,pixelArr);
    
}

void clearPixel(uint8_t x, uint8_t y, uint16_t *pixelArr)
{
    pixelArr[y] = pixelArr[y] & ~(1<<x);
    updatePixelGroup(x,y,pixelArr);
}

void updatePixelGroup(uint8_t x, uint8_t y, uint16_t *pixelArr)
{
    uint8_t lcdX = x/3;
    uint8_t lcdY = 19-y;
    lcd.setCursor(lcdY, lcdX);

    uint8_t val = (pixelArr[y] >> (lcdX *3)) & 0b111;
    lcd.write(val);
}

void drawAllPixels(uint16_t *pixels)
{
    for (uint8_t x = 0; x < 4; x++)
    {
        lcd.setCursor(0, x);

        for (int8_t y = 19; y >= 0; y--)
        {
            uint8_t val = (pixels[y] >> x) & 0b111;
            lcd.write(val);
        }
        

    }
    
}