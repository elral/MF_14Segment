#pragma once

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

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
    bool               _initialised;
    uint8_t            _addrI2C;
    Adafruit_AlphaNum4 *alpha4;
};