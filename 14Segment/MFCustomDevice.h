#pragma once

#include <Arduino.h>
#include "14Segment.h"

// only one entry required if you have only one custom device
enum {
    MY_14SEGMENT = 1
};
class MFCustomDevice
{
public:
    MFCustomDevice();
    void attach(uint16_t adrPin, uint16_t adrType, uint16_t adrConfig);
    void detach();
    void update();
    void set(int16_t messageID, char *setPoint);

private:
    bool getStringFromEEPROM(uint16_t addreeprom, char *buffer);
    bool _initialized = false;
    Segment14 * _my14segment;
    uint8_t _customType = 0;
};
