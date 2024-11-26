#include <debounce.h>

debounceBtn::debounceBtn(uint8_t btnPin)
{
    _pin = btnPin;
    pinMode(_pin, INPUT);
}

//only returns true on the 8th consecutive HIGH read
bool debounceBtn::pressed()
{
    _state = (_state << 1) | (digitalRead(_pin));

    return (_state == 0x00FF);
}