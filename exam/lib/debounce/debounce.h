#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

class debounceBtn
{
private:
    uint16_t _state = 0;
    uint8_t _pin;
public:
    debounceBtn(uint8_t btnPin);
    bool pressed();

};

#endif