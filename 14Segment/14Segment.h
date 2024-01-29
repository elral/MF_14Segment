#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "14Segment_driver.h"

class Segment14
{
public:
    Segment14();
    void begin();
    void attach(uint8_t addrI2C);
    void detach();
    void set(int16_t messageID, char *setPoint);
    void update();
    void test();

private:
    bool       _initialised;
    uint8_t    _addrI2C;
    uint8_t    _brightness;
    uint8_t    _dotPos = 0;
    AlphaNum4 *alpha4;
};