#include <lcdController.h>

const uint8_t lcdAddr = 0x27;


//  bitmaps for the 8 custum characters used to show "pixels"
uint8_t customChars[8][8] = 
{
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    {0b01110, 0b01110, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000},
    {0b01110, 0b01110, 0b00000, 0b01110, 0b01110, 0b00000, 0b00000, 0b00000},
    {0b01110, 0b01110, 0b00000, 0b01110, 0b01110, 0b00000, 0b01110, 0b01110},
    {0b00000, 0b00000, 0b00000, 0b01110, 0b01110, 0b00000, 0b00000, 0b00000},
    {0b00000, 0b00000, 0b00000, 0b01110, 0b01110, 0b00000, 0b01110, 0b01110},
    {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b01110},
    {0b01110, 0b01110, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b01110}
};

LiquidCrystal_I2C lcd(lcdAddr,20,4);

void lcdSetup()
{
    lcd.init();
    lcd.backlight();
    for (uint8_t i = 0; i < 8; i++)
    {
        lcd.createChar(i, customChars[i]);
    }

    lcd.setCursor(0,0);
    for (uint8_t i = 0; i < 8; i++)
    {
        lcd.write(i);
    }
    lcd.setCursor(0,1);
    for (uint8_t i = 0; i < 20; i++)
    {
        lcd.write(0);
    }
    lcd.setCursor(0,2);
    for (uint8_t i = 0; i < 20; i++)
    {
        lcd.write(0);
    }
    lcd.setCursor(0,3);
    for (uint8_t i = 0; i < 20; i++)
    {
        lcd.write(0);
    }
    
}